#include <Arduino.h>

#define ledPin 4
#define switchPinFwd 5
#define switchPinBack 21
#define queueSize 5

QueueHandle_t switchCommand;

typedef enum {
  OPEN,
  CLOSE
} State;

State sysState = OPEN;

void ledTask(void *parameter){
  int dutyCycle = 0;
  for(;;){
    int switchStateFwd = digitalRead(switchPinFwd);
    int switchStateBack = digitalRead(switchPinBack);
    if (switchStateFwd == 0 && sysState == OPEN && dutyCycle <= 255){
      dutyCycle++;
    }
    if (switchStateBack == 0 && sysState == CLOSE && dutyCycle > 0){
      dutyCycle--;
    }
    analogWrite(ledPin, dutyCycle);
    vTaskDelay(100/portTICK_PERIOD_MS);
    Serial.println(dutyCycle);
    //Serial.printf("Forward Switch: %u\nBack Switch: %u", switchStateFwd, switchStateBack);q
    //Serial.println(switchStateBack);
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

void setup(){
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  pinMode(switchPinFwd, INPUT_PULLUP);
  pinMode(switchPinBack, INPUT_PULLUP);

  xTaskCreatePinnedToCore(ledTask, "ledTask", 3000, NULL, 1, NULL, 1);
  xTaskCreatePinnedToCore(stateSwitcher, "stateSwitcher", 3000, NULL, 1, NULL, 1);
}

void loop(){

}

