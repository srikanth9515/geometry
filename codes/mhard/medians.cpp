#include <ArduinoOTA.h>
#ifdef ESP32
  #include <WiFi.h>
  #include <AsyncTCP.h>
#else
  #include <ESP8266WiFi.h>
  #include <ESPAsyncTCP.h>
#endif
#include <ESPAsyncWebServer.h>
#include<math.h>
#include"libs/geofun.h"

AsyncWebServer server(80);

const char* ssid = "Redmi";
const char* password = "987654321";

const char* input_parameter00 = "input00";
const char* input_parameter01 = "input01";
const char* input_parameter10 = "input10";
const char* input_parameter11 = "input11";
const char* input_parameter20 = "input20";
const char* input_parameter21 = "input21";

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html><head>
  <title>MEDIAN TRIANGLE </title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <style>
    html {font-family: Times New Roman; display: inline-block; text-align: center;}
    h2 {font-size: 2.0rem; color: blue;}
  </style>
  <script>
    function updateResults(results) {
      document.getElementById("results").innerHTML = results;
    }
  </script>
  </head><body>
  <h2>MEDIAN TRIANGLE </h2>
  <p>Enter the values of Sides A, B, C</p>
  <form id="triangleForm" onsubmit="submitForm(); return false;">
    Enter the values of Side A: <input type="number" name="input00">
    Enter the values of Side B: <input type="number" name="input01">
    Enter the values of Side C: <input type="number" name="input10">
    <input type="submit" value="Submit">
  </form><br>
  <div id="results"></div>
  <br><a href="/">Return to Home Page</a>
  <script>
    function submitForm() {
      var formData = new FormData(document.getElementById("triangleForm"));
      fetch('/get', { method: 'POST', body: formData })
        .then(response => response.text())
        .then(results => updateResults(results));
    }
  </script>
</body></html>)rawliteral";

void notFound(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "Not found");
}




void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connecting...");
    return;
  }
  Serial.println();
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html);
  });

  server.on("/get", HTTP_POST, [] (AsyncWebServerRequest *request) {
    double side_a = request->arg(input_parameter00).toDouble();
    double side_b = request->arg(input_parameter01).toDouble();
    double side_c = request->arg(input_parameter10).toDouble();


    // Calculate midpoints of the triangle vertices
    double median1 =calculateMedian(&side_a, &side_b, &side_c);
    double median2 =calculateMedian(&side_b, &side_c, &side_a);
    double median3 =calculateMedian(&side_c, &side_a, &side_b);

    // Send the results back to the client
    String result = "MEDIAN1: (" + String(median1, 2)+ ")";
         result += "MEDIAN2: (" + String(median2, 2)+ ")";
       result += "MEDIAN3: (" + String(median3, 2)+ ")";
    request->send(200, "text/html", result);
  });

  server.onNotFound(notFound);
  server.begin();
}

void loop() {
  // Nothing to do here
}
