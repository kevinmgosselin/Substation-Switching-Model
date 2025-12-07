#include <Arduino.h>

#define sensorPin 33

const float vRef = 3.3;
const float adcResolution = 4095;
const float zeroPoint = 1.67;
const float dividerRatio = 0.6667; // Divider Ratio for a 1k + 2k Ohm V. Div.
const float sensitivity = 0.100 * dividerRatio;

void sensorRead(void *parameter){
  for(;;){
    uint32_t sumPin_mV = 0;
    for (int i = 0; i <= 99; i++){
      uint32_t pin_mV = analogReadMilliVolts(sensorPin);
      sumPin_mV = sumPin_mV + pin_mV;
    }
    float avgPin_mV = sumPin_mV/100;
    float pinVoltage = avgPin_mV/1000;
    float current = (pinVoltage - zeroPoint)/sensitivity;

    Serial.println(current);
    vTaskDelay(100/portTICK_PERIOD_MS);
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  analogSetPinAttenuation(sensorPin, ADC_11db);
  pinMode(sensorPin, INPUT);
  xTaskCreatePinnedToCore(sensorRead, "sensorRead", 3000, NULL, 1, NULL, 1);
}

void loop() {
  // put your main code here, to run repeatedly:
}