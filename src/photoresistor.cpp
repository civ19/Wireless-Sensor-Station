#include <Arduino.h>

#include "photoresistor.h"

int readLightRaw() {
    return analogRead(LDR_PIN);
}

int readLightPercent() {
    int raw = analogRead(LDR_PIN);
    int brightness = map(raw, 0, 4095, 0, 100);

    return brightness;
}