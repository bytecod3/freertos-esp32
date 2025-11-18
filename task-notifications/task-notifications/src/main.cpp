#include <Arduino.h>
#include "freertos/FreeRTOS.h"

/**
 * task handles 
 */
TaskHandle_t x_task_consume_handle;
TaskHandle_t x_task_produce_handle;
TaskHandle_t v_handler_task_handle;

TimerHandle_t my_isr_timer;

/* rate for interrut generation */
const TickType_t x_interrupt_freq = pdMS_TO_TICKS(500UL);

/* tasks */
void v_handler_task(void* pv_parameters) {
  const TickType_t expected_block_time = x_interrupt_freq + pdMS_TO_TICKS(10);
  uint32_t events_to_process;

  for(;;) {

    /* wait for a task notification from ISR */
    ulTaskNotifyTake(pdTRUE, expected_block_time); 
    Serial.println("Software interrupt triggered");

    // if(events_to_process != 0){ /* at least one event must have occured to get here */
    //   while(events_to_process > 0) {
    //     Serial.printf("Handler task - processing event.\r\n");
    //     events_to_process--;
    //   }
    // } else {
    //   /* interrupt did not arrive within thw wxpected time - perfom error recovery */
    // }

  }
}

static void IRAM_ATTR ul_example_interrupt_handler(TimerHandle_t x_timer) {
  BaseType_t x_higher_priority_task_woken;
  x_higher_priority_task_woken = pdFALSE;

  /* send notification directly to the task to which the interrupt is being deferred */
  vTaskNotifyGiveFromISR(v_handler_task_handle, &x_higher_priority_task_woken);

  /* check for a context switch */
  portYIELD_FROM_ISR(&x_higher_priority_task_woken);

}

void setup() {
  Serial.begin(115200);
  delay(400);

  if(xTaskCreate(v_handler_task, "v_task_handler", 1024, NULL, 1, &v_handler_task_handle)) {
    Serial.println("V task handler created OK");
  } else {
    Serial.println("V task handler failed to create");
  }

  /* create timer to periodically call the ISR */
  my_isr_timer = xTimerCreate("myTimer", pdMS_TO_TICKS(1000), pdTRUE, NULL, ul_example_interrupt_handler);
  xTimerStart(my_isr_timer, 0);

}

void loop() {
  
}
