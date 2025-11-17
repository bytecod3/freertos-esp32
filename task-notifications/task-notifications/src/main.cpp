#include <Arduino.h>
#include "freertos/FreeRTOS.h"

/**
 * task handles 
 */
TaskHandle_t x_task_consume;
TaskHandle_t x_task_produce;
TaskHandle_t v_handler_task;

/* rate for interrut generation */
const TickType_t x_interrupt_freq = pdMS_TO_TICKS(500UL);

/* tasks */
void v_handler_task(void* pv_parameters) {
  const TickType_t expected_block_time = x_interrupt_freq + pdMS_TO_TICKS(10);
  uint32_t events_to_process;

  for(;;) {

    events_to_process = ulTaskNotifyTake(pdTRUE, expected_block_time); /* wait for a task notification from ISR */

    if(events_to_process != 0){ /* at least one event must have occured to get here */
      while(events_to_process > 0) {
        Serial.printf("Handler task - processing event.\r\n");
        events_to_process--;
      }
    } else {
      /* interrupt did not arrive within thw wxpected time - perfom error recovery */
    }
  }
}

void setup() {
  Serial.println(115200);

  delay(400);
}

void loop() {
  
}
