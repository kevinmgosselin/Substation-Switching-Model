#include <Arduino.h>

#define LED_PIN 23
#define SWITCH_PIN 18

TaskHandle_t BlinkTaskHandle = NULL;

volatile bool taskSuspended = false;
volatile uint32_t lastInterruptTime = 0;
const uint32_t debounceDelay = 100;

void IRAM_ATTR buttonISR(){
  uint32_t currentTime = millis();
  if(currentTime - lastInterruptTime < debounceDelay){
    return;
  }
  lastInterruptTime = currentTime;

  taskSuspended = !taskSuspended;
  if (taskSuspended){
    vTaskSuspend(BlinkTaskHandle);
    Serial.println("Blink Suspended");
  }
  else{
    vTaskResume(BlinkTaskHandle);
    Serial.println("Blink Resumed");
  }


}

void BlinkTask(void *parameter){
  for(;;){
    digitalWrite(LED_PIN, HIGH);
    Serial.println("BlinkTask: LED ON");
    vTaskDelay(1000/portTICK_PERIOD_MS);
    digitalWrite(LED_PIN, LOW);
    Serial.println("BlinkTask: LED OFF");
    vTaskDelay(1000/portTICK_PERIOD_MS);
    Serial.print("BlinkTask running on core ");
    Serial.println(xPortGetCoreID());
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  pinMode(SWITCH_PIN, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(SWITCH_PIN), buttonISR, FALLING);
  xTaskCreatePinnedToCore(BlinkTask, "BlinkTask", 10000, NULL, 1, &BlinkTaskHandle, 1);
}
void loop() {}
