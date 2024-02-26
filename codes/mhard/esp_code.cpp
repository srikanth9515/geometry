#include <ArduinoOTA.h>
#ifdef ESP32
  #include <WiFi.h>
  #include <AsyncTCP.h>
#else
  #include <ESP8266WiFi.h>
  #include <ESPAsyncTCP.h>
#endif
#include <ESPAsyncWebServer.h>
#include"matfun.h"

AsyncWebServer server(80);

const char* ssid = "Iqooneo6";
const char* password = "gps93093";

const char* input_parameter00 = "input00";
const char* input_parameter01 = "input01";
const char* input_parameter10 = "input10";
const char* input_parameter11 = "input11";
const char* input_parameter20 = "input20";
const char* input_parameter21 = "input21";

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html><head>
  <title>Angle Bisector</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <style>
    html {font-family: Times New Roman; display: inline-block;}
    h2 {font-size: 2.0rem; color: blue;}
  </style>
  <script>
    function updateResults(results) {
      document.getElementById("results").innerHTML = results;
    }
  </script>
  </head><body>
  <h2>TO FIND THE Incenter and Inradius</h2>
  <p>Enter the values of points A, B, C</p>
  <form id="triangleForm" onsubmit="submitForm(); return false;">
    Enter the values of Point A: <input type="number" name="input00" value = 1><input type="number" name="input01" value = -1><br>
    Enter the values of Point B: <input type="number" name="input10" value = -4><input type="number" name="input11" value = 6><br>
    Enter the values of Point C: <input type="number" name="input20" value = -3><input type="number" name="input21" value = -5><br>
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
    double Ax = request->arg(input_parameter00).toDouble();
    double Ay = request->arg(input_parameter01).toDouble();
    double Bx = request->arg(input_parameter10).toDouble();
    double By = request->arg(input_parameter11).toDouble();
    double Cx = request->arg(input_parameter20).toDouble();
    double Cy = request->arg(input_parameter21).toDouble();


    double **A, **B, **C,a,b,c,m,n,p;
    int m1 = 2, n1 = 1;
    A = createMat(m1, n1);
    B = createMat(m1, n1);
    C = createMat(m1, n1);
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
            
    printf("Distance between A and B: %lf\n", distance_AB);
    printf("Distance between A and C: %lf\n", distance_AC);
    printf("Distance between B and C: %lf\n", distance_BC);
            
    a = distance_BC;
    b = distance_AC;
    c = distance_AB;

    m = (a + c - b) / 2;
    n = (a + b - c) / 2;
    p = (c + b - a) / 2;

    printf("Sides of the triangle: %lf %lf %lf\n", m, n, p);

    double **D = Matsec(C,B,2,1,m,n);
    double **E = Matsec(A,C,2,1,n,p);
    double **F = Matsec(B,A,2,1,p,m);
    
   
    printf("Point D on BC: (%lf, %lf)\n", D[0][0], D[1][0]);
    printf("Point E on AC: (%lf, %lf)\n", E[0][0], E[1][0]);
    printf("Point F on AB: (%lf, %lf)\n", F[0][0], F[1][0]);

    double **center = calculateCircumcenter(D,E,F);

    double inradius = calculateInradius(distance_AB, distance_AC, distance_BC);

    printf("Incenter coordinates: (%lf, %lf)\n", center[0][0], center[1][0]);
    printf("Inradius: %lf\n", inradius);

    // Send the results back to the client

   String result = "InCenter: (" + String(center[0][0], 2) + ", " + String(center[1][0], 2) + ")<br>" +
                "inradius: " + String(inradius) + "<br>" +
                "D: (" + String(D[0][0], 2) + ", " + String(D[1][0], 2) + ")<br>" +
                "E: (" + String(E[0][0], 2) + ", " + String(E[1][0], 2) + ")<br>" +
                "F: (" + String(F[0][0], 2) + ", " + String(F[1][0], 2) + ")<br>" +
                "Distance Of AB:" +String(c)+ "<br>" +
                "Distance Of BC:" +String(a)+ "<br>" +
                "Distance Of CA:" +String(b)+ "<br>";


    request->send(200, "text/html", result);
  });

  server.onNotFound(notFound);
  server.begin();
}

void loop() {
  // Nothing to do here
}
