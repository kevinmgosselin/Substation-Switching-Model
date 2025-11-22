#include <Arduino.h>

#define sensorPin 34

const float vRef = 3.3;
const float adcResolution = 4095;
const float zeroPoint = 1.67;
const float dividerRatio = 0.665;
const float sensitivity = 0.100 * dividerRatio;

void sensorRead(void *parameter){
  for(;;){
    float avgCurrent = 0;
    float sumCurrent = 0;
    for (int i = 0; i <= 99; i++){
    int adcValue = analogRead(sensorPin);
    float pinVoltage = (adcValue/adcResolution)*vRef;
    float current = (pinVoltage - zeroPoint)/sensitivity;
    sumCurrent = current + sumCurrent;
    }
    avgCurrent = sumCurrent/100;
    Serial.println(avgCurrent);
    vTaskDelay(100/portTICK_PERIOD_MS);
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  analogSetAttenuation(ADC_11db);
  pinMode(sensorPin, INPUT);
  xTaskCreatePinnedToCore(sensorRead, "sensorRead", 3000, NULL, 1, NULL, 1);
}

void loop() {
  // put your main code here, to run repeatedly:
}