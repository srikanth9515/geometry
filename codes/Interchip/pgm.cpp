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

const char *ssid = "nikhilsai";
const char *password = "nikhilsai";

const char *PARAM_X1 = "x1";
const char *PARAM_Y1 = "y1";
const char *PARAM_X2 = "x2";
const char *PARAM_Y2 = "y2";
const char *PARAM_X3 = "x3";
const char *PARAM_Y3 = "y3";

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html><head>
  <title>Triangle Midpoints</title>
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
  <h2>Triangle Midpoints</h2>
  <form id="triangleForm" onsubmit="return calculate()">
    <label for="x1">Vertex 1 X:</label>
    <input type="text" name="x1" required>
    <label for="y1">Y:</label>
    <input type="text" name="y1" required><br>

    <label for="x2">Vertex 2 X:</label>
    <input type="text" name="x2" required>
    <label for="y2">Y:</label>
    <input type="text" name="y2" required><br>

    <label for="x3">Vertex 3 X:</label>
    <input type="text" name="x3" required>
    <label for="y3">Y:</label>
    <input type="text" name="y3" required><br>

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
    int x1 = request->arg(PARAM_X1).toInt();
    int y1 = request->arg(PARAM_Y1).toInt();
    int x2 = request->arg(PARAM_X2).toInt();
    int y2 = request->arg(PARAM_Y2).toInt();
    int x3 = request->arg(PARAM_X3).toInt();
    int y3 = request->arg(PARAM_Y3).toInt();

    // Create matrices for the coordinates
    double **a = createMat(3, 2);
    a[0][0] = x1; a[0][1] = y1;
    a[1][0] = x2; a[1][1] = y2;
    a[2][0] = x3; a[2][1] = y3;

    // Create matrix b for scaling
    double **b = createMat(3, 1);
    b[0][0] = b[1][0] = b[2][0] = 1.0;

    // Call the Matsec function to calculate midpoints
    double **midpoints = Matsec(a, b, 3, 1.0);
    
// Extract midpoints
    double midX1 = midpoints[0][0];
    double midY1 = midpoints[0][1];
    double midX2= midpoints[1][0];
    double midY2 = midpoints[1][1];
    double midX3 = midpoints[2][0];
    double midY3 = midpoints[2][1];
    
    // Free memory allocated for matrices
    freeMat(midpoints, 3);
    freeMat(a, 3);
    freeMat(b, 3);
    
    // Create a response
    String response = "Midpoint 1: (" + String(midX1) + "," + String(midY1) + ")" +
                      "<br>Midpoint 2: (" + String(midX2) + "," + String(midY2) + ")" +
                      "<br>Midpoint 3: (" + String(midX3) + "," + String(midY3) + ")";

    // Prepare HTML response with the calculated midpoints
    request->send(200, "text/html", response);
  });

  server.onNotFound(notFound);
  server.begin();
}

void loop() {}
