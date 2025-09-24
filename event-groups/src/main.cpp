/**
 * Using event groups 
 */

#include <Arduino.h>
#include <freertos/FreeRTOS.h>

float die_temperature = 0.0f; // internal chip temperature 

#define X_WAIT_TIME  pdMS_TO_TICKS(400) // in ms to ticks
#define X_FEED_QUEUE_DELAY_TIME  pdMS_TO_TICKS(800) // in ms to ticks

/**
 * Queues
 */
QueueHandle_t data_queue_handle;

/**
 * Event group handle 
 */
EventGroupHandle_t data_consumption_event_handle;       // event group handle 

/**
 * Bit 0 -> OLED task received data 
 * Bit 1 -> Serial debug task received data
 */
#define PRINT_SCREEN_BIT (1 << 0UL)
#define PRINT_SERIAL_BIT (1 << 1UL)

EventBits_t data_consume_event_group;


/**
 * Task handles 
 */
TaskHandle_t x_task_read_temp_handle;
TaskHandle_t x_task_print_to_serial_handle;
TaskHandle_t x_task_display_ui_handle;
TaskHandle_t x_task_clean_queue_handle;

/**
 * Tasks
 */
void x_task_read_temp(void* arg) { // producer
    uint16_t x_count_value = 0;
    for(;;) {
        x_count_value++;

        if(!xQueueSend(data_queue_handle, &x_count_value, X_FEED_QUEUE_DELAY_TIME) ) {
            Serial.println("Failed to send to queue");
        }

        //vTaskDelay(X_FEED_QUEUE_DELAY_TIME);

    }
}

void x_task_print_to_serial(void* arg){ // consumer
    uint16_t x_recvd_val;

    for(;;) {
        if(!xQueuePeek(data_queue_handle, &x_recvd_val, X_WAIT_TIME) ) {
            Serial.println("SERIAL: Failed to receive from queue");
        }

        // set the event group bit to show that we have received this value
        xEventGroupSetBits(
            data_consumption_event_handle, 
            PRINT_SERIAL_BIT
        );

        Serial.printf("SERIAL val: %d\n", x_recvd_val);
        vTaskDelay(X_WAIT_TIME);

    }
}

void x_task_display_ui(void* arg) { // consumer
    uint16_t a;
    for(;;) {
        if(!xQueuePeek(data_queue_handle, &a, X_WAIT_TIME)) {
            Serial.println("UI: Failed to receive from queue");
        }

        xEventGroupSetBits(
            data_consumption_event_handle, 
            PRINT_SCREEN_BIT
        );

        Serial.printf("UI val: %d\n", a);
        vTaskDelay(X_WAIT_TIME);
    }
}

void x_task_clean_queue(void* arg) {  // cleaner

    EventBits_t x_event_group_value;
    const EventBits_t x_bits_to_wait_for = (PRINT_SCREEN_BIT | PRINT_SERIAL_BIT);

    uint16_t item;

    for(;;) {

        /**
         * Block until this condition/group of bits are set
         */
        x_event_group_value = xEventGroupWaitBits(
            data_consumption_event_handle, // event group to read
            x_bits_to_wait_for,             // bits to test 
            pdTRUE,                         // clear on exit if unblock condition is met 
            pdTRUE,                         // wait for all bit to be set
            portMAX_DELAY                   // do not time out
        );

        /**
         * Here since all the items have received(peeked ) from data queue, 
         * remove the item from queue
         */
        xQueueReceive(data_queue_handle, &item, portMAX_DELAY);

        // just to debug 
        if((x_event_group_value & PRINT_SCREEN_BIT)) {
            Serial.println("Printed to screen");
        }

        if((x_event_group_value & PRINT_SERIAL_BIT)) {
            Serial.println("Printed to Serial");
        }

        // clear the bits 
        vTaskDelay(pdMS_TO_TICKS(10));

    }
}


void setup() {
    Serial.begin(115200);

    data_queue_handle = xQueueCreate(20, sizeof(float));
    if(data_queue_handle == NULL) {
        Serial.println("Could not create data queue");
    } else {
        Serial.println("Data queue created OK");
    }

    data_consumption_event_handle = xEventGroupCreate();
    if(data_consumption_event_handle == NULL) {
        // log this 
        Serial.println("Could not create event group");
    } else {
        Serial.println("Event group created OK");
    }

    /**
     * create tasks
     * 
     * todo: check successful creation  
     * 
     * The priority of the task that reads from Event group is higher than that of the tasks 
     * writing to the event group 
     * THis ensures that the reading task will pre-empt the writing task each time the reading tasks's 
     * unblock condition is met
     * 
     */
    xTaskCreate(x_task_read_temp, "x_task_read_temp", 2048, NULL, tskIDLE_PRIORITY + 2, &x_task_read_temp_handle);
    xTaskCreate(x_task_print_to_serial, "x_task_print_to_serial", 2048, NULL, tskIDLE_PRIORITY + 1, &x_task_print_to_serial_handle);
    xTaskCreate(x_task_display_ui, "x_task_display_ui", 2048, NULL, tskIDLE_PRIORITY + 1, &x_task_display_ui_handle);
    xTaskCreate(x_task_clean_queue, "x_task_clean_queue", 2048, NULL, tskIDLE_PRIORITY + 5, &x_task_clean_queue_handle);


}

void loop() {
    vTaskDelay(pdMS_TO_TICKS(10));

}