#include <Arduino.h>
#include <math.h>
#include "thermsistor.h"

// Assumptions for thermsistor
const float SERIES_RESISTOR = 10000.0;   // 10k resistor
const float NOMINAL_RESISTANCE = 10000.0; // 10k thermistor @ 25°C
const float NOMINAL_TEMP = 25.0;          // 25°C
const float BETA = 3950.0;                // common beta value


float readTemperatureC() {
  int adc = analogRead(THERM_PIN);
  // Convert ADC to resistnce
  float voltage = (adc / 4095.0) * 3.3;
  float resistance = SERIES_RESISTOR * ((3.3 / voltage) - 1.0);

  // Beta formla
  float steinhart;
  steinhart = resistance / NOMINAL_RESISTANCE;      // (R/Ro)
  steinhart = log(steinhart);                       // ln(R/Ro)
  steinhart /= BETA;                                // 1/B * ln(...)
  steinhart += 1.0 / (NOMINAL_TEMP + 273.15);       // + (1/To)
  steinhart = 1.0 / steinhart;                      // invert

  return steinhart - 273.15;                        // K → °C
}
