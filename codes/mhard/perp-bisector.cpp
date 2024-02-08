#include <Arduino.h>
#ifdef ESP32
  #include <WiFi.h>
  #include <AsyncTCP.h>
#else
  #include <ESP8266WiFi.h>
  #include <ESPAsyncTCP.h>
#endif
#include <ESPAsyncWebServer.h>
#include <math.h>
#include "libs/matfun.h"

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
  <title>TASK_2 </title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <style>
    html {font-family: Times New Roman; display: inline-block; text-align: center;}
    h2 {font-size: 2.0rem; color: blue;}
  </style> 
  </head><body>
  <h2>Perpendicular_Bisect</h2> 
  <p>Enter the values of points A, B, C
  <form action="/get">
    Enter the values of Point A: <input type="number" name="input00"><br><input type="number" name="input01"><br>
    Enter the values of Point B: <input type="number" name="input10"><br><input type="number" name="input11"><br>
    Enter the values of Point C: <input type="number" name="input20"><br><input type="number" name="input21"><br>
    <input type="submit" value="Submit">
  </form><br>
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

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send_P(200, "text/html", index_html);
  });

  server.on("/get", HTTP_GET, [](AsyncWebServerRequest *request) {
    double Ax, Ay, Bx, By, Cx, Cy;

    // Parse input values
    Ax = request->arg(input_parameter00).toFloat();
    Ay = request->arg(input_parameter01).toFloat();
    Bx = request->arg(input_parameter10).toFloat();
    By = request->arg(input_parameter11).toFloat();
    Cx = request->arg(input_parameter20).toFloat();
    Cy = request->arg(input_parameter21).toFloat();
    
    //Declare variables for Slope and Midpoints
    double bisectorABSlope, bisectorABMidpointX, bisectorABMidpointY;
    double bisectorBCSlope, bisectorBCMidpointX, bisectorBCMidpointY;
    double bisectorCASlope, bisectorCAMidpointX, bisectorCAMidpointY;  
    
    //Calculate Bisectors
    calculatePerpendicularBisector(Ax, Ay, Bx, By, &bisectorABSlope, &bisectorABMidpointX, &bisectorABMidpointY);
    calculatePerpendicularBisector(Bx, By, Cx, Cy, &bisectorBCSlope, &bisectorBCMidpointX, &bisectorBCMidpointY);
    calculatePerpendicularBisector(Cx, Cy, Ax, Ay, &bisectorCASlope, &bisectorCAMidpointX, &bisectorCAMidpointY);
    
    //Display results on the webpage
    String response = "Results: <br>Bisector AB: Slope= " + String(bisectorABSlope, 2) + "Midpoint=" + String(bisectorABMidpointX, 2) + String(bisectorABMidpointY, 2);
    response += "Bisector BC: Slope= " + String(bisectorBCSlope, 2) + "Midpoint=" + String(bisectorBCMidpointX, 2) + String(bisectorBCMidpointY, 2);
    response += "Bisector CA: Slope= " + String(bisectorCASlope, 2) + "Midpoint=" + String(bisectorCAMidpointX, 2) + String(bisectorCAMidpointY, 2);
    response += "<a href=\"/\">RefreshPage</a>";
     request->send(200, "text/html", response);
     });
  server.onNotFound(notFound);
  server.begin();
}

    
void loop() {
Serial.begin(115200);
  Serial.println();
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  // Nothing to do here for now
}
