#include <Arduino.h>
#include <freertos/FreeRTOS.h>

#define IDLE_TASK_DELAY (10)
#define BLINK_INTERVAL (500)

TaskHandle_t x_task_blocking_handle;

/* tasks PFPs */
void x_task_blocking(void* arguments);

void timer1_callback(TimerHandle_t xTimer) {
  Serial.println("Timer expired");
  
}


void setup() {
  Serial.begin(115200);

  TimerHandle_t tmr1 = xTimerCreate(
    "My Timer",
    pdMS_TO_TICKS(1000),
    pdTRUE,
    (void*) 0,
    timer1_callback
    );

    /* check if the timer was created successfully */
    if(tmr1 == NULL) {
      Serial.println("Could not create timer");
    } else {
      Serial.println("Timer created OK");

      /* start timer */
      xTimerStart(tmr1, 0);
    }

    /* create tasks */
    xTaskCreatePinnedToCore(
      x_task_blocking,
      "x_task_blocking_task",
      1000,
      NULL,
      2,
      &x_task_blocking_handle,
      1
    );

}

void loop() {
  vTaskDelay(pdMS_TO_TICKS(IDLE_TASK_DELAY));
}

/* TASKS */
void x_task_blocking(void* arguments) {
  TickType_t x_task_start_tick = xTaskGetTickCount();

  for(;;) {
    Serial.println("BLOCKING TASK CALLED");
    vTaskDelayUntil(&x_task_start_tick, BLINK_INTERVAL);
  }

}
