/**
 * counting sempahores are mainly used for task syncronization
 * between tasks
 */

#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"

SemaphoreHandle_t xSemphr = NULL;

TaskHandle_t xTaskHandleDemo1;
TaskHandle_t xTaskHandleDemo2;


void demo_task_1(void* pvParameters) {
    for(;;) {
        Serial.printf("Message sent: %d\r\n", xTaskGetTickCount()); // print current tick count 
        xSemaphoreGive(xSemphr);        // release the binary semaphore to any waiting task
        vTaskDelay(pdMS_TO_TICKS(500));

    }
}

void demo_task_2(void* pvParameters) {
    for(;;) {
        
        if(xSemaphoreTake(xSemphr, portMAX_DELAY)) { // attempt to take the semaphore
            Serial.printf("Message recieved: %d\r\n", xTaskGetTickCount());
        }
    }
}

void setup() {
    Serial.begin(115200);

    
    xSemphr = xSemaphoreCreateBinary(); // create sempahore 
    xTaskCreate(demo_task_1, "demo task 1", 4096, NULL, 10, &xTaskHandleDemo1);
    xTaskCreate(demo_task_2, "demo task 2", 4096, NULL, 10, &xTaskHandleDemo2);

}

void loop() {

}