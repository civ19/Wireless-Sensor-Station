#include "distSensor.h"
#include <Arduino.h>

float readDistanceCM() {
    // Make sure TRIG starts LOW
    digitalWrite(TRIG, LOW);
    delayMicroseconds(2);

    // Send 10µs pulse
    digitalWrite(TRIG, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG, LOW);

    // Read echo pulse (with timeout!)
    long t = pulseIn(ECHO, HIGH, 30000); // 30ms timeout

    // If no echo received
    if (t == 0) {
        return -1; // indicates "no reading"
    }

    // Convert to distance (cm)
    float dist = (t * 0.0343) / 2.0;



    return dist;
}