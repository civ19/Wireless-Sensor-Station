#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>  

const char* ssid = "1051A";
const char* password = "Secord1051A";

WebServer server(80);  // Create a web server on port 80

void getData() {
    String json = "{\"temperature\": 24.5, \"humidity\": 60}";
    server.send(200, "application/json", json);
}

void setup() {
    Serial.begin(115200);
    delay(1000); //small 1s delay so it doesnt immediately jump
    
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
        Serial.print("Your link: http://"); Serial.print(WiFi.localIP()); Serial.println("/data");
        
        //firing up the server
        server.begin();
        server.on("/data", getData);

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