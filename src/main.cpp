#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>  
#include "thermsistor.h"
#include "photoresistor.h"
#include "distSensor.h"
#include <LittleFS.h>

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
    json += String(temp, 1);
    json += ", \"light\": ";
    json += light;
    json += ", \"distance\": ";
    json += String(dist, 1);
    json += "}";
    server.send(200, "application/json", json);
}

void routeJS() {
    server.on("/app.js", []() {
        File file = LittleFS.open("/app.js", "r");
        server.streamFile(file, "application/javascript");
        file.close();
    });

    server.on("/data", getData);
}

void handleRoot() {
    File file = LittleFS.open("/index.html", "r");

    if (!file) {
        server.send(404, "text/plain", "index.html not found");
        return;
    }

    server.streamFile(file, "text/html");
    file.close();
}

void setup() {
    Serial.begin(115200);
    delay(1000); //small 1s delay so it doesnt immediately jump
    analogSetPinAttenuation(THERM_PIN, ADC_11db);
    analogSetPinAttenuation(LDR_PIN, ADC_11db);
    pinMode(TRIG, OUTPUT);
    pinMode(ECHO, INPUT);

    if (!LittleFS.begin(true)) { 
    Serial.println("Critical Failure: LittleFS could not mount or auto-format!");
    } else {
        Serial.println("Success! LittleFS partition initialized.");
        Serial.printf("Total Flash Space: %d bytes\n", LittleFS.totalBytes());
    }
   

    digitalWrite(TRIG, LOW);
    
    Serial.print("Connecting to WiFi: "); Serial.print(ssid);
    WiFi.begin(ssid, password);
    int att = 0;
    while(WiFi.status() != WL_CONNECTED && att < 40) {
        delay(1000);
        Serial.print(".");
        att++;
    }

    if(WiFi.status() == WL_CONNECTED) { //if it connects we start up the web server and mappings
        Serial.println("\nConnected Sucessfully!");
        Serial.print("Your link: http://"); Serial.print(WiFi.localIP()); Serial.println("/");
        
        //firing up the server
        server.on("/", handleRoot);
        server.on("/data", getData);
    
        routeJS();

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