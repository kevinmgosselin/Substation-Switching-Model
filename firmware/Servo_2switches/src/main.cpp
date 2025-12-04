#include <Arduino.h>
#include <ESP32Servo.h>

#define switchOpenPin 13
#define switchClosePin 2

static const int servoPin = 18;

Servo servo;

typedef enum {
  OPEN,
  CLOSE
} State;

State sysState = OPEN;

void servoTask(void *parameter){
  int posDegrees = 0;
  for(;;){
    int switchStateOpen = digitalRead(switchOpenPin);
    int switchStateClose = digitalRead(switchClosePin);
    if (switchStateOpen == 0 && sysState == OPEN){
      posDegrees++;
    }
    if (switchStateClose == 0 && sysState == CLOSE){
      posDegrees--;
    }
    servo.write(posDegrees);
    vTaskDelay(100/portTICK_PERIOD_MS);
    Serial.printf("OpenSwitch: %u", switchStateOpen);
    Serial.printf("CloseSwitch: %u", switchStateClose);
    Serial.println(posDegrees);
  }
}

void stateSwitcher(void *parameter){
  for(;;){
    sysState = OPEN;
    vTaskDelay(10000/portTICK_PERIOD_MS);
    sysState = CLOSE;
    vTaskDelay(10000/portTICK_PERIOD_MS);
  }
}

void setup() {
  Serial.begin(115200);
  servo.attach(servoPin);

  pinMode(switchOpenPin, INPUT_PULLUP);
  pinMode(switchClosePin, INPUT_PULLUP);

  xTaskCreatePinnedToCore(servoTask, "servoTask", 3000, NULL, 1, NULL, 1);
  xTaskCreatePinnedToCore(stateSwitcher, "stateSwitcher", 3000, NULL, 1, NULL, 1);
}

void loop() {
  
}

