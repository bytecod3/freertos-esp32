/** 
 * This code blinks LED using timer and notification
 */


#include <Arduino.h>
#include <freertos/FreeRTOS.h>

#define IDLE_TASK_DELAY (10)
#define BLINK_INTERVAL (500)

#define LED 8

TaskHandle_t task_handle_1;
TaskHandle_t task_handle_2;

/* timer handles */
TimerHandle_t blink_timer_handle;

/* timer callback functions */
void blink_timer_callback(TimerHandle_t tmr);

/* tasks PFPs */
void x_task_1(void* arguments);
void x_task_2(void* arguments);

bool led_level = false;

void setup() {
  Serial.begin(115200);

  /* create timer */
  blink_timer_handle = xTimerCreate("blink_timer", pdTICKS_TO_MS(500), pdTRUE, NULL, blink_timer_callback);
  /* todo: check if timer created OK */

  /* start timer immediately */
  xTimerStart(blink_timer_handle, 0);

  /* create tasks */
   /* create the task receiving the notification first -> or you can defer task creation */
  // xTaskCreatePinnedToCore(
  //   x_task_2,
  //   "x_task_2",
  //   1000,
  //   NULL,
  //   2,
  //   &task_handle_2,
  //   1
  // );

  xTaskCreatePinnedToCore(
    x_task_1,
    "x_task_1",
    1000,
    NULL,
    2,
    &task_handle_1,
    1
  );

}

void loop() {
  vTaskDelay(pdMS_TO_TICKS(IDLE_TASK_DELAY));
}

/* TIMER CALLBACKS */
void blink_timer_callback(TimerHandle_t tmr) {
  // notify the LED task 
  xTaskNotifyGive(task_handle_1);
}

/* TASKS */
void x_task_1(void* arguments) {

  digitalWrite(LED, LOW); 

  for(;;) {
    // Serial.println("Task1: sending notification to task 2");
    // xTaskNotifyGive(task_handle_2);
    // vTaskDelay(pdMS_TO_TICKS(1000));

    // blink LED on receiving task notification from timer 
    ulTaskNotifyTake(pdTRUE, portMAX_DELAY);    // wait until timer notifies
    led_level = !led_level;
    digitalWrite(LED, led_level);

    Serial.println("LED toggled");

  }
}

// void x_task_2(void* arguments) {
//   for(;;) {
//     /* receive notification */
//     /* this will automatically clear the notification */
//     // ulTaskNotifyTake(pdTRUE, portMAX_DELAY); 
//     // Serial.println("Task 2: Notification received");
//   }

// }
