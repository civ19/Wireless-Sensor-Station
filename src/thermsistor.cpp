#include <Arduino.h>
#include <math.h>

#define THERM_PIN 1

// Assumptions (typical Freenove kit thermistor)
const float SERIES_RESISTOR = 10000.0;   // 10k resistor
const float NOMINAL_RESISTANCE = 10000.0; // 10k thermistor @ 25°C
const float NOMINAL_TEMP = 25.0;          // 25°C
const float BETA = 3950.0;                // common beta value

void setup() {
  Serial.begin(115200);
  delay(1000);

  analogSetPinAttenuation(THERM_PIN, ADC_11db);

  Serial.println("Thermistor -> Temperature conversion starting...");
}

float readTemperatureC(int adc) {
  // Convert ADC to resistance
  float voltage = (adc / 4095.0) * 3.3;
  float resistance = SERIES_RESISTOR * ((3.3 / voltage) - 1.0);

  // Beta formula
  float steinhart;
  steinhart = resistance / NOMINAL_RESISTANCE;      // (R/Ro)
  steinhart = log(steinhart);                       // ln(R/Ro)
  steinhart /= BETA;                                // 1/B * ln(...)
  steinhart += 1.0 / (NOMINAL_TEMP + 273.15);       // + (1/To)
  steinhart = 1.0 / steinhart;                      // invert

  return steinhart - 273.15;                        // K → °C
}

void loop() {
  int adc = analogRead(THERM_PIN);

  float voltage = (adc / 4095.0) * 3.3;
  float tempC = readTemperatureC(adc);

  Serial.print("ADC: ");
  Serial.print(adc);

  Serial.print(" | Voltage: ");
  Serial.print(voltage, 3);

  Serial.print(" V | Temp: ");
  Serial.print(tempC, 2);

  Serial.println(" °C");

  delay(500);
}