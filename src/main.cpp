#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "1051A";
const char* password = "Secord1051A";

WebServer server(80);
int ledPin = 2;

String getHTML() {
  String html = "<!DOCTYPE html><html>";
  html += "<head><meta name='viewport' content='width=device-width, initial-scale=1'>";
  html += "<style>body{text-align:center; font-family:sans-serif; background:#f4f4f4; color:#333;}"
          ".btn{display:inline-block; padding:20px 40px; font-size:24px; background:#23c470; "
          "color:white; border:none; border-radius:8px; text-decoration:none; box-shadow:0 4px 6px rgba(0,0,0,0.1);}</style></head>";
  html += "<body><h1>ESP32-S3 Web Control</h1>";
  html += "<p>Press the button below to toggle the LED.</p>";
  html += "<p><a href='/toggle' class='btn'>TOGGLE LED</a></p>";
  html += "</body></html>";
  return html;
}

void handleRoot() {
    server.send(200, "text/html", getHTML());
}

void handleToggle() {
    Serial.println("TOGGLE HIT");
    digitalWrite(ledPin, !digitalRead(ledPin));
    server.send(200, "text/html", getHTML());
}

void setup() {
    Serial.begin(115200);
    while (!Serial) {
        delay(10);
    }
    pinMode(ledPin, OUTPUT);
    digitalWrite(ledPin, LOW);

    Serial.print("Connecting to WiFi: ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);

    int attempts = 0;
    while(WiFi.status() != WL_CONNECTED && attempts < 40) {
        delay(500);
        Serial.print(".");
        attempts++;
    }

    if(WiFi.status() == WL_CONNECTED) {
        Serial.println("\nConnected Successfully!");
        Serial.print("IP: http://");
        Serial.println(WiFi.localIP());
        
        server.on("/", handleRoot);
        server.on("/toggle", handleToggle);
        server.begin();
        Serial.println("Web Server Started!");
    } else {
        Serial.println("\nFailed to connect to WiFi!");
    }
}

void loop() {
    if(WiFi.status() == WL_CONNECTED) {
        server.handleClient();
    }
}
