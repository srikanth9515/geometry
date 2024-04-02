#include <WiFi.h>
#include <HTTPClient.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

const char* ssid = "nani";
const char* password = "nani12345";
const char* githubFileURL = "https://raw.githubusercontent.com/srikanth9515/geometry/codes/Interchip/esp32-fpga/Medians/output.txt";
String fileContent;

AsyncWebServer server(80);

// Function declaration
String fetchFileContentFromGitHub();

// Callback function to handle HTTP GET request
void handleRequest(AsyncWebServerRequest *request) {
  request->send(200, "text/plain", fileContent);
}

void setup() {
  Serial.begin(115200);

  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Fetch file content from GitHub
  fileContent = fetchFileContentFromGitHub();

  // Configure web server route
  server.on("/", HTTP_GET, handleRequest);

  // Start web server
  server.begin();
}

void loop() {
  // Handle any additional logic here
}

// Function to fetch the content of a text file from GitHub
String fetchFileContentFromGitHub() {
  HTTPClient http;
  
  // Send HTTP GET request
  http.begin(githubFileURL);
  int httpResponseCode = http.GET();
  
  // Check for successful response
  if (httpResponseCode == HTTP_CODE_OK) {
    String payload = http.getString();
    http.end();
    return payload;
  } else {
    Serial.printf("HTTP GET failed, error code: %d\n", httpResponseCode);
    http.end();
    return "";
  }
}

