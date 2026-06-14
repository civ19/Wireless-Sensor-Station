#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>  
#include "thermsistor.h"
#include "photoresistor.h"
#include "distSensor.h"

const char* ssid = "1051A";
const char* password = "Secord1051A";

WebServer server(80);  // Create a web server on port 80

//4h time debt

void getData() {
    float temp = readTemperatureC();
    int light = readLightPercent();
    float dist = readDistanceCM();

    String json = "{";
    json += " \"temperature\": ";
    json += String(temp, 2);
    json += ", \"light\": ";
    json += light;
    json += ", \"distance\": ";
    json += String(dist, 2);
    json += "}";
    server.send(200, "application/json", json);
}

void handleRoot() {
    String html = R"rawliteral(
    <!DOCTYPE html>
    <html>
    <head>
        <title>Sensor Dashboard</title>
    </head>
    <body>
        <h1>Wireless Sensor Station</h1>

            <p>Temperature: <span id="temp">Loading...</span> °C</p>
            <p>Light: <span id="light">Loading...</span></p>
            <p>Distance: <span id="distance">Loading...</span></p>

    <script>
        async function updateData() {
            const response = await fetch('/data');
            const data = await response.json();

            document.getElementById('temp').textContent =
                data.temperature;
            document.getElementById('light').textContent = 
                data.light + "%";
            document.getElementById('distance').textContent =
                data.distance;
        }

        updateData();
        setInterval(updateData, 500);
    </script>
    </body>
    </html>
    )rawliteral";

    server.send(200, "text/html", html);
}

void setup() {
    Serial.begin(115200);
    delay(1000); //small 1s delay so it doesnt immediately jump
    analogSetPinAttenuation(THERM_PIN, ADC_11db);
    analogSetPinAttenuation(LDR_PIN, ADC_11db);
    pinMode(TRIG, OUTPUT);
    pinMode(ECHO, INPUT);
   

    digitalWrite(TRIG, LOW);
    
    Serial.print("Connecting to WiFi: "); Serial.print(ssid);
    WiFi.begin(ssid, password);
    int att = 0;
    while(WiFi.status() != WL_CONNECTED && att < 40) {
        delay(100);
        Serial.print(".");
        att++;
    }

    if(WiFi.status() == WL_CONNECTED) { //if it connects we start up the web server and mappings
        Serial.println("\nConnected Sucessfully!");
        Serial.print("Your link: http://"); Serial.print(WiFi.localIP()); Serial.println("/");
        
        //firing up the server
        server.on("/", handleRoot);
        server.on("/data", getData);
        server.begin();

    }
    else {
        Serial.println("\nFailed to connect.");
    }
    

}

void loop() {
    if(WiFi.status() == WL_CONNECTED) {
        server.handleClient();
    }
} 