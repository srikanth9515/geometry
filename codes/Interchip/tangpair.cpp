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

const char *ssid = "RedmiNote10S";
const char *password = "arunkumar1";

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
  </head>
  <body>
  <h2>Tangents of the Triangle</h2>
  
  <form id="triangleForm" onsubmit="return calculate()">
    Enter the values of Point A: <br>
    <input type="text" name="x1" value = '1' required>
    <input type="text" name="y1" value = '-1' required><br>
    
    Enter the values of Point B: <br>
    <input type="text" name="x2" value = '-4' required>
    <input type="text" name="y2" value = '6' required><br>
    
    Enter the values of Point C: <br>
    <input type="text" name="x3" value = '-3' required>
    <input type="text" name="y3" value = '-5' required><br>
    
    <input type="submit" value="Calculate">
  </form>
    <script>
    function updateResults(response) {
      document.getElementById("results").innerHTML = response;
    }

    function calculate() {
      var form = document.getElementById("triangleForm");
      var formData = new FormData(form);

      fetch('/get', {
        method: 'POST',
        body: formData
      })
      .then(response => response.text())
      .then(data => updateResults(data));
      
      // Prevent form submission and page reload
      return false;
    }
  </script>
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

  server.on("/get", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send_P(200, "text/html", index_html);
  });
  server.on("/get", HTTP_POST, [](AsyncWebServerRequest *request) {
    int Ax = request->arg(PARAM_X1).toInt();
    int Ay = request->arg(PARAM_Y1).toInt();
    int Bx = request->arg(PARAM_X2).toInt();
    int By = request->arg(PARAM_Y2).toInt();
    int Cx = request->arg(PARAM_X3).toInt();
    int Cy = request->arg(PARAM_Y3).toInt();
    
    double **A, **B, **C, **sol,**side_AB,**side_BC,**side_CA,a, b, c, m_val, n_val, p_val;
    int m = 2, n = 1;
    A = createMat(m, n);
    B = createMat(m, n);  
    C = createMat(m, n);
    sol = createMat(2,2);
    A[0][0] = Ax;
    A[1][0] = Ay;
    B[0][0] = Bx;
    B[1][0] = By;
    C[0][0] = Cx;
    C[1][0] = Cy;
    side_AB = Matsub(A,B,m,n);
    side_BC = Matsub(B,C,m,n);
    side_CA = Matsub(C,A,m,n);
    a = Matnorm(side_AB,m);
    b = Matnorm(side_BC,m);
    c = Matnorm(side_CA,m);
    p_val = (a + c - b) / 2;
    m_val = (a + b - c) / 2;
    n_val = (b + c - a) / 2;
    sol[0][0] = (m_val * A[0][0] + p_val * B[0][0]) / (m_val + p_val);
    sol[0][1] = (p_val * C[0][0] + n_val * A[0][0]) / (p_val + n_val);
    sol[1][0] = (m_val * A[1][0] + p_val * B[1][0]) / (m_val + p_val);
    sol[1][1] = (p_val * C[1][0] + n_val * A[1][0]) / (p_val + n_val);
    // Send the results back to the client
    String result = "E: (" + String(sol[0][0], 2) + ", " + String(sol[0][1], 2) + ")<br>F: (" + String(sol[1][0], 2) + ", " + String(sol[1][1], 2) + ")";

    request->send(200, "text/html", result);
    printf("Results sent to client\n");
    freeMat(A, 2);
    freeMat(B, 2);
    freeMat(C, 2);
    freeMat(sol, 2);
    freeMat(side_AB,2);
    freeMat(side_BC,2);
    freeMat(side_CA,2);
  });

  server.onNotFound(notFound);
  server.begin();
}

void loop() {}
