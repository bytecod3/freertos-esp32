#include <Arduino.h>
#include "freertos/FreeRTOS.h"

#define SEND 0

QueueHandle_t data_queue;

void x_task_generate_integers(void* pvParameters) {
	uint8_t x = 4;

	for(;;) {
		x++;

#if SEND
		xQueueSend(data_queue, &x, portMAX_DELAY);
#endif
		vTaskDelay(pdMS_TO_TICKS(1000));

	}
}

void x_task_receive_integers(void* pvParameters) {
	uint8_t x = 0;
	for(;;) {
		x++;

		xQueueReceive(data_queue, &x, portMAX_DELAY);

		Serial.printf("Received integer: %d", x);
		vTaskDelay(pdMS_TO_TICKS(1000));

	}
}


void setup() {
	Serial.begin(115200);

	data_queue = xQueueCreate(10, sizeof(uint8_t));
	if( data_queue == NULL) {
		Serial.println("Failed to create data queue");
	}

	xTaskCreate(
		x_task_generate_integers,
		"generate_integers",
		2048,
		NULL,
		1,
		NULL
	);

	xTaskCreate(
		x_task_receive_integers,
		"receive_integers",
		2048,
		NULL,
		1,
		NULL
	);


}

void loop() {
	vTaskDelay(pdMS_TO_TICKS(5));

}
