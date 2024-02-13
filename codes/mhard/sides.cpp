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
#include "libs/geofun.h"
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
  <title>Triangle Properities</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <style>
    html {font-family: Times New Roman; display: inline-block; text-align: center;}
    h2 {font-size: 2.0rem; color: blue;}
  </style> 
  </head><body>
  <h2>Side and Angle</h2> 
  <p>Enter the values of points A, B, C
  <form action="/get">
    Vertex A (x1 y1): <input type="number" name="input00"><br><input type="number" name="input01"><br>
    Vertex B (x2 y2): <input type="number" name="input10"><br><input type="number" name="input11"><br>
    Vertex C (x3 y3): <input type="number" name="input20"><br><input type="number" name="input21"><br>
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
    int x1, y1, x2, y2, x3, y3, m=2, n=1;
    double **A,**B,**C,sideAB, sideBC, sideCA;
    double **s_ab, **s_bc, **s_ca;

    // Parse input values
    x1 = request->arg(input_parameter00).toFloat();
    y1 = request->arg(input_parameter01).toFloat();
    x2 = request->arg(input_parameter10).toFloat();
    y2 = request->arg(input_parameter11).toFloat();
    x3 = request->arg(input_parameter20).toFloat();
    y3 = request->arg(input_parameter21).toFloat();
    A = createMat(m,n);
    B = createMat(m,n);
    C = createMat(m,n);
    A[0][0] = x1;
    A[1][0] = y1;
    B[0][0] = x2;
    B[1][0] = y2;
    C[0][0] = x3;
    C[1][0] = y3;
    s_ab = Matsub(A,B,m,n);//A-B
    s_bc = Matsub(B,C,m,n);//B-C
    s_ca = Matsub(C,A,m,n);//C-A
    sideAB = Matnorm(s_ab,m);
    sideBC = Matnorm(s_bc,m); 
    sideCA = Matnorm(s_ca,m);

    // Calculate the angles
    double angleA = calculateAngle(sideBC, sideCA, sideAB);
    double angleB = calculateAngle(sideCA, sideAB, sideBC);
    double angleC = calculateAngle(sideAB, sideBC, sideCA);

    // Display the results on the webpage
    String response = "Results <br> Side AB: " + String(sideAB, 2) + "<br>";
    response += "Side BC: " + String(sideBC, 2) + "<br>";
    response += "Side CA: " + String(sideCA, 2) + "<br>";
    response += "Angle A: " + String(angleA, 2) + "<br>";
    response += "Angle B: " + String(angleB, 2) + "<br>";
    response += "Angle C: " + String(angleC, 2) + "<br>";
    response += "<a href=\"/\">Return to Home Page</a>";

    request->send(200, "text/html", response);
  });

  server.onNotFound(notFound);
  server.begin();
}

void loop() {
}
