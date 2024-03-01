#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "libs/esp32_eoss3_spi.h"
#include "libs/matfun.h"


#define GPIO_OUTPUT_VAL_REG 0x40021004
#define GPIO_OUTPUT_DIR_REG 0x40021008
#define PIN_BLUE 18
#define PIN_GREEN 21
#define PIN_RED 22
#define PIN_ALL (1<<PIN_GREEN) | (1<<PIN_BLUE) | (1<<PIN_RED)

AsyncWebServer server(80);

const char* ssid = "Tinku";
const char* password = "12345678";

const char* PARAM_X1 = "x1";
const char* PARAM_Y1 = "y1";
const char* PARAM_X2 = "x2";
const char* PARAM_Y2 = "y2";
const char* PARAM_X3 = "x3";
const char* PARAM_Y3 = "y3";

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html><head>
  <title>Angular Bisector</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <style>
    html {font-family: Times New Roman; display: inline-block; text-align: center;}
    h2 {font-size: 2.0rem; color: blue;}
  </style> 
  <script>
    function updateResults(response) {
      document.getElementById("results").innerHTML = response;
    }

    function calculate() {
      var form = document.getElementById("AngularForm");
      var formData = new FormData(form);

      fetch('/Angular', {
        method: 'POST',
        body: formData
      })
      .then(response => response.text())
      .then(data => updateResults(data));
    }
  </script>
  </head>
  <body>
  <h2>angular bisector</h2>
  <form id="AngularForm" action="/Angular" method="POST">
    <label for="Ax">Vertex 1 X:</label>
    <input type="text" name="x1" required>
    <label for="Ay">Y:</label>
    <input type="text" name="y1" required><br>

    <label for="Bx">Vertex 2 X:</label>
    <input type="text" name="x2" required>
    <label for="By">Y:</label>
    <input type="text" name="y2" required><br>

    <label for="Cx">Vertex 3 X:</label>
    <input type="text" name="x3" required>
    <label for="Cy">Y:</label>
    <input type="text" name="y3" required><br><br>

    <input type="button" value="Calculate" onclick="calculate()">
  </form><br>
  <div id="results"></div>
</body></html>)rawliteral";

void notFound(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "Not found");
}

void setup() {
  esp32_eoss3_spi_init();
  uint32_t dirval = (1<<PIN_GREEN) | (1<<PIN_BLUE) | (1<<PIN_RED);
  uint32_t gpioval = 0;
  esp32_eoss3_spi_ahb_write(GPIO_OUTPUT_DIR_REG, (uint8_t *)&dirval, 4);
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
      Serial.print(".");
      delay(2000);
  }
  Serial.println();
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  server.on("/Angular", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html);
  });

  server.on("/Angular", HTTP_POST, [&gpioval](AsyncWebServerRequest *request){
      
    double Ax = request->arg(PARAM_X1).toDouble();
    double Ay = request->arg(PARAM_Y1).toDouble();
    double Bx = request->arg(PARAM_X2).toDouble();
    double By = request->arg(PARAM_Y2).toDouble();
    double Cx = request->arg(PARAM_X3).toDouble();
    double Cy = request->arg(PARAM_Y3).toDouble();



    double **A, **B, **C,**eigen,a,b,c, **D, **E, **F;
    int m1 = 2, n1 = 1;
    A = createMat(m1, n1);
    B = createMat(m1, n1);
    C = createMat(m1, n1);
    eigen = createMat(m1, n1);
    
    A[0][0] = Ax;
    A[1][0] = Ay;
    B[0][0] = Bx;
    B[1][0] = By;
    C[0][0] = Cx;
    C[1][0] = Cy;

    double **diff_AB = Matsub(B, A, 2, 1); 
    double distance_AB = Matnorm(diff_AB, 2);  
    
    double **diff_AC = Matsub(C, A, 2, 1);
    double distance_AC = Matnorm(diff_AC, 2);  
    
    double **diff_BC = Matsub(C, B, 2, 1);
    double distance_BC = Matnorm(diff_BC, 2);
    
    a = distance_BC;
    b = distance_AC;
    c = distance_AB;
    
    double l1 = (a + c - b) / 2;
    double l2 = (a + b - c) / 2;
    double l3 = (c+ b - a) / 2;
    
    D = Matscale(Matadd(Matscale(C, 2, 1, l1), Matscale(B, 2, 1, l2), 2, 1), 2, 1, 1.0 / (l1 + l2));
    E = Matscale(Matadd(Matscale(A, 2, 1, l2), Matscale(C, 2, 1, l3), 2, 1), 2, 1, 1.0 / (l2 + l3));
    F = Matscale(Matadd(Matscale(B, 2, 1, l3), Matscale(A, 2, 1, l1), 2, 1), 2, 1, 1.0 / (l3 + l1));


    double **temp1 = Matscale(A, 2, 1, a);
    double **temp2 = Matscale(B, 2, 1, b);
    double **temp3 = Matscale(C, 2, 1, c);

    double **eigenvalues = Matadd(Matadd(temp1, temp2, 2, 1), temp3, 2, 1);
    double eigendenominator = a + b + c;

    eigen[0][0] = eigenvalues[0][0] / eigendenominator;
    eigen[1][0] = eigenvalues[1][0] / eigendenominator;
    
    String response = 
    "D: " + String(D[0][0],2) + ", " + String(D[1][0],2) + "<br>"
    "E: " + String(E[0][0],2) + ", " + String(E[1][0],2) + "<br>"
    "F: " + String(F[0][0],2) + ", " + String(F[1][0],2) + "<br>"
    "distance of AB: " + c + "<br>"
    "distance of BC: " + a + "<br>"
    "distance of CA: " + b + "<br>"
    "InCenter:"  + String(eigen[0][0],2) + ", " + String(eigen[1][0], 2) + "<br>"    
    ".";
    
    request->send(200, "text/html", response);
  });

  server.onNotFound(notFound);
  server.begin();
}

void loop() {
}
