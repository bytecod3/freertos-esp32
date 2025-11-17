/**

 * Reference:
 */

#include <Arduino.h>

#define Q1_ITEM_SIZE sizeof (uint32_t)


/*======================
 * Tasks
 *=====================*/
TaskHandle_t t1_handle;
TaskHandle_t t2_handle;
TaskHandle_t t3_handle;
TaskHandle_t t4_handle;
TaskHandle_t vSenderTask;

void task_1(void *);
void task_2(void *);

/*======================
 * Queues
 *=====================*/
QueueHandle_t q1;
QueueHandle_t q2;
QueueHandle_t q3;
QueueHandle_t q4;

/**
 * @brief initialize queues
 * @return
 */
void queue_init() {
    BaseType_t  q1_crt_stat;
    q1 = xQueueCreate(10, sizeof(uint32_t));
    if(q1 == nullptr) {
        Serial.println("q1 create failed.");
    } else {
        Serial.println("q1 created OK.");
    }

}

/**
 * @brief send data to q1
 * @param d uint32_t integer to send
 */
void q1_send(uint32_t d) {
    BaseType_t q_send_s;
    TickType_t ticks_to_wait = 100; // 100 MS

    uint32_t h = d;

    q_send_s = xQueueSend(q1, &h, ticks_to_wait);
    if(q_send_s != pdPASS) {
        Serial.println("Failed to send to q1");
    }

}

/**
 * @brief peak value from Q1 without removing the queue
 * @return d uint32 data read from q1
 */
uint32_t q1_receive() {
    uint32_t dt;
    TickType_t t_to_wait = 100;
    xQueueReceive(q1, &dt, t_to_wait); // check successful read
    return dt;
}

/**
 * @brief task 1
 */
void task_1(void * argument) {
    uint32_t dt = 56;
    TickType_t wait_time = 500;
    while(1) {
        //q1_send(dt);
        //xQueueSend(q1, &dt, 50);
        //vTaskDelay(wait_time);
    }
}

void task_2(void * argument) {
    uint32_t dt;
    TickType_t wait_time = 500;

    while(1) {
        //xQueueReceive(q1, &dt, 50);
        //Serial.printf("Read from q1: %c\n", dt);
        //vTaskDelay(wait_time);
    }

}

void tasks_init() {
    BaseType_t x_return;
    x_return = xTaskCreate(task_1,
                            "Task 1",
                            1024,
                           nullptr,
                            1,
                            &t1_handle);

    if(x_return != pdPASS) {
        Serial.println("Failed to create task 1");
    } else {
        Serial.println("Task 1 created OK");
    }

    //========================== task 2 ===========================
    BaseType_t x2_return;
    x2_return = xTaskCreate(task_2,
                           "Task 2",
                           1024,
                           nullptr,
                           1,
                           &t2_handle);

    if(x2_return != pdPASS) {
        Serial.println("Failed to create task 2");
    } else {
        Serial.println("Task 2 created OK");
    }
}

void setup() {
    Serial.begin(115200);
    //queue_init();
    //tasks_init();
}

void loop() {
}