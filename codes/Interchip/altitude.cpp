#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "libs/esp32_eoss3_spi.h"
#include "libs/matfun.h" // Assuming you have defined matrix functions in matfun.h
#include "libs/geofun.h" // Assuming you have defined geometric functions in geofun.h

#define GPIO_OUTPUT_VAL_REG 0x40021004
#define GPIO_OUTPUT_DIR_REG 0x40021008
#define PIN_BLUE 18
#define PIN_GREEN 21
#define PIN_RED 22
#define PIN_ALL (1 << PIN_GREEN) | (1 << PIN_BLUE) | (1 << PIN_RED)

AsyncWebServer server(80);

const char *ssid = "Pavankgr";
const char *password = "1234567890";

const char *PARAM_X1 = "x1";
const char *PARAM_Y1 = "y1";
const char *PARAM_X2 = "x2";
const char *PARAM_Y2 = "y2";
const char *PARAM_X3 = "x3";
const char *PARAM_Y3 = "y3";

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html><head>
  <title>Tangents</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <style>
    html {font-family: Times New Roman; display: inline-block;}
    h2 {font-size: 2.0rem; color: red;}
  </style>
  <script>
    function updateResults(response) {
      document.getElementById("results").innerHTML = response;
    }

    function calculate() {
      var form = document.getElementById("triangleForm");
      var formData = new FormData(form);

      fetch('/mid', {
        method: 'POST',
        body: formData
      })
      .then(response => response.text())
      .then(data => updateResults(data));
      
      // Prevent form submission and page reload
      return false;
    }
  </script>
  </head>
  <body>
  <h2>Tangents of the Triangle</h2>
  <form id="triangleForm" onsubmit="return calculate()">
    <label for="x1">Vertex 1 X:</label>
    <input type="text" name="x1" value = '1' required>
    <label for="y1">Y:</label>
    <input type="text" name="y1" value = '-1' required><br>

    <label for="x2">Vertex 2 X:</label>
    <input type="text" name="x2" value = '-4' required>
    <label for="y2">Y:</label>
    <input type="text" name="y2" value = '6' required><br>

    <label for="x3">Vertex 3 X:</label>
    <input type="text" name="x3" value = '-3' required>
    <label for="y3">Y:</label>
    <input type="text" name="y3" value = '-5' required><br>

    <input type="submit" value="Calculate">
  </form>
  <div id="results">%RESULT%</div>
</body></html>)rawliteral";

void notFound(AsyncWebServerRequest *request)
{
  request->send(404, "text/plain", "Not found");
}

void setup()
{
  esp32_eoss3_spi_init();
  uint32_t dirval = (1 << PIN_GREEN) | (1 << PIN_BLUE) | (1 << PIN_RED);
  uint32_t gpioval = 0;
  esp32_eoss3_spi_ahb_write(GPIO_OUTPUT_DIR_REG, (uint8_t *)&dirval, 4);
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(2000);
  }
  Serial.println();
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  server.on("/mid", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send_P(200, "text/html", index_html);
  });
  server.on("/mid", HTTP_POST, [](AsyncWebServerRequest *request) {
    int Ax = request->arg(PARAM_X1).toInt();
    int Ay = request->arg(PARAM_Y1).toInt();
    int Bx = request->arg(PARAM_X2).toInt();
    int By = request->arg(PARAM_Y2).toInt();
    int Cx = request->arg(PARAM_X3).toInt();
    int Cy = request->arg(PARAM_Y3).toInt();
    
    int m=2,n=1,i,j,k=0;
    double **A,**B,**C,**m1,**m2,**m3,**H,**l,**N,**m3_t,**m1_t,**p0,**p1,**p,**P1,**P2;
    A = createMat(m,n);
    B = createMat(m,n);
    C = createMat(m,n);
    p = createMat(2,1);
    l = createMat(m,m);
    H = createMat(2,1);

    A[0][0] = Ax;
    A[1][0] = Ay;
    B[0][0] = Bx;
    B[1][0] = By;
    C[0][0] = Cx;
    C[1][0] = Cy;
    m1=Matsub(A,B,m,n);
    m2=Matsub(B,C,m,n);
    m3=Matsub(C,A,m,n);
   
    N=transposeMat(combineMat(m3,m1,m,n),m,m);
    m3_t=transposeMat(m3,m,n);
    m1_t=transposeMat(m1,m,n);
    p0=Matmul(m3_t,B,n,m,n);
    p1=Matmul(m1_t,C,n,m,n);
    p[0][0]=p0[0][0];
    p[1][0]=p1[0][0];
    // Solving the linear equations
    H[1][0]=(-1)*(p[0][0]*N[1][0]-N[0][0]*p[1][0])/Matdet(N);
    H[0][0]=(p[0][0]*N[1][1]-N[0][1]*p[1][0])/Matdet(N);
    // Send the results back to the client
    String result = "Orthocenter O: (" + String(H[0][0],2) + ", " + String(H[1][0], 2) + ")";
    request->send(200, "text/html", result);
    freeMat(A,2);
    freeMat(B,2);
    freeMat(C,2);
    freeMat(m1,2);
    freeMat(m2,2);
    freeMat(m3,2);
    freeMat(H,2);
  });

  server.onNotFound(notFound);
  server.begin();
}

void loop() {}
