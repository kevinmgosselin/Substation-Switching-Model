#include <Arduino.h>
#include <ESP32Servo.h>

#define switchOpenPin 13
#define switchClosePin 4
#define sensorPin 35

const float vRef = 3.3;
const float adcResolution = 4095;
const float zeroPoint = 1.67;
const float dividerRatio = 0.6667; // Divider Ratio for a 1k + 2k Ohm V. Div.
const float sensitivity = 0.100 * dividerRatio;

static const int servoPin = 5;

float current = 0;

Servo servo;

typedef enum {
  OPEN,
  CLOSE
} State;

State sysState = OPEN;

void sensorRead(void *parameter){
  for(;;){
    uint32_t sumPin_mV = 0;
    for (int i = 0; i <= 99; i++){
      uint32_t pin_mV = analogReadMilliVolts(sensorPin);
      sumPin_mV = sumPin_mV + pin_mV;
    }
    float avgPin_mV = sumPin_mV/100;
    float pinVoltage = avgPin_mV/1000;
    current = (pinVoltage - zeroPoint)/sensitivity;

    Serial.printf("Current: %f\n",current);
    vTaskDelay(100/portTICK_PERIOD_MS);
  }
}

void servoTask(void *parameter){
  int posDegrees = 0;
  for(;;){
    int switchStateOpen = digitalRead(switchOpenPin);
    int switchStateClose = digitalRead(switchClosePin);
    if (switchStateOpen == 1 && sysState == OPEN && posDegrees < 180){
      posDegrees++;
    }
    if (switchStateClose == 1 && sysState == CLOSE && posDegrees > 0){
      posDegrees--;
    }
    servo.write(posDegrees);
    vTaskDelay(10/portTICK_PERIOD_MS);
    Serial.printf("OpenSwitch: %u\n", switchStateOpen);
    Serial.printf("CloseSwitch: %u\n", switchStateClose);
    Serial.println(posDegrees);
  }
}

void stateSwitcher(void *parameter){
  for(;;){
    if (current > 0.3){ // For 5v and 10 ohm resistor
      sysState = OPEN;
    }
    else{
      sysState = CLOSE;
    }
    vTaskDelay(100/portTICK_PERIOD_MS);
    Serial.printf("System State: %s\n", sysState);
  }
}

void setup() {
  Serial.begin(115200);
  servo.attach(servoPin);

  analogSetPinAttenuation(sensorPin, ADC_11db);
  pinMode(sensorPin, INPUT);
  pinMode(switchOpenPin, INPUT_PULLUP);
  pinMode(switchClosePin, INPUT_PULLUP);

  xTaskCreatePinnedToCore(servoTask, "servoTask", 3000, NULL, 1, NULL, 1);
  xTaskCreatePinnedToCore(stateSwitcher, "stateSwitcher", 3000, NULL, 1, NULL, 1);
  xTaskCreatePinnedToCore(sensorRead, "sensorRead", 3000, NULL, 1, NULL, 1);
}

void loop() {
  
}

