#include <Arduino.h>

#define ledPin 4
#define switchPin 5
#define queueSize 5

QueueHandle_t switchQueue = NULL;

void queueTask(void *parameter){
  for(;;){
    int switchState = digitalRead(switchPin);
    xQueueSend(switchQueue, &switchState, portMAX_DELAY);
    Serial.printf("switchTask: Sent switch state %d\n", switchState);
    vTaskDelay(10/portTICK_RATE_MS);
  }
}

void ledTask(void *parameter){
  for(;;){
    int switchState;
    if (xQueueReceive(switchQueue, &switchState, portMAX_DELAY))
    if (switchState){
      digitalWrite(ledPin, HIGH);
    }
    else{
      digitalWrite(ledPin, LOW);
    }
  }
}

void setup(){
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  pinMode(switchPin, INPUT_PULLUP);

  switchQueue = xQueueCreate(queueSize, sizeof(int));
  if (switchQueue == NULL){
    Serial.println("Failed to create queue!");
    while(1);
  }

  xTaskCreatePinnedToCore(queueTask, "queueTask", 3000, NULL, 1, NULL, 1);
  xTaskCreatePinnedToCore(ledTask, "ledTask", 3000, NULL, 1, NULL, 1);
}

void loop(){

}

