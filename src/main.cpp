#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>  
#include "thermsistor.h"
#include "photoresistor.h"
#include "distSensor.h"
#include <SPIFFS.h>

const char* ssid = "wifi";
const char* password = "pass";

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
    
    server.on("/", HTTP_GET, []() {
        File file = SPIFFS.open("/index.html", "r"); //get saved html fdile from spiffs and make it read only
        server.streamFile(file, "text/html"); //file = loaded file, text/html = content type of file. streamfile => send file contents to browser over http req. basically sendiung html page to browser http caller
        file.close(); //obvious, releases file
    });
   
}

void setup() {
    Serial.begin(115200);
    delay(1000); //small 1s delay so it doesnt immediately jump
    analogSetPinAttenuation(THERM_PIN, ADC_11db);
    analogSetPinAttenuation(LDR_PIN, ADC_11db);
    pinMode(TRIG, OUTPUT);
    pinMode(ECHO, INPUT);

    if(!SPIFFS.begin(true)) {
        Serial.println("SPIFFS mount failed");
        return;
    }
   

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