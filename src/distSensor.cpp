#include "distSensor.h"
#include <Arduino.h>


void setup() {
    pinMode(TRIG, OUTPUT);
    pinMode(ECHO, INPUT);
    Serial.begin(115200);

    digitalWrite(TRIG, LOW);
}

float readDistanceCM() {
    digitalWrite(TRIG, LOW);
    delayMicroseconds(2); //2 us
    
    digitalWrite(TRIG, HIGH); //send out a 10us pulse, then echo receives it
    delayMicroseconds(10);
    digitalWrite(TRIG, LOW);

    //read echo pulse duration
    long t = pulseIn(ECHO, HIGH); //return time echo goes high in us
    float dist = t * 0.0343/2; //d = t*

    return dist;

}
void loop() {
    float d = readDistanceCM();

    Serial.print("Distance: ");
    Serial.print(d);
    Serial.println(" cm");

    delay(500);
}