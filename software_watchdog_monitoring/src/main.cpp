/**
 * @brief This file tests a methid of resetting the ESP32 in case of a software hang
 * @author edwin
 *
 */

#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <esp_log.h>

#define BAUDRATE 115200

/* heartbeat flag */
uint8_t heartbeat_flag = 0x00;

/* tasks heartbeat bit positions */
uint8

/* for logging */
const char* debug_tag = "WATCHDOG";

/**
 * @brief this task create other tasks then self-deletes
 */
void x_task_create_tasks(void* pv_parameters) {

	for(;;) {

		ESP_LOGI(debug_tag, "Creating tasks...");

		xTaskCreate(
			get_random_number_task,		/* task code */
			"get_random_number_task",	/* task name */
			1024, 						/* task stack size in words */
			NULL,						/* parameters to task  */
			1,							/* priority */
			NULL);						/* task handle */

			
		xTaskCreate(
			read_time_task,		
			"read_time_task",	
			1024, 						
			NULL,						
			1,							
			NULL);						

		xTaskCreate(
			read_mpu_task,		
			"read_mpu_task",	
			1024, 						
			NULL,						
			1,							
			NULL);						

		xTaskCreate(
			watchdog_manager_task,		
			"watchdog_manager_task",	
			1024, 						
			NULL,						
			1,							
			NULL);						


		vTaskDelete(NULL);

	}

}

/**
 * @brief task 1 to simulate reading an actual sensor into integer queue
 */
void get_random_number_task(void* pv_parameters) {

	for(;;) {

	}

}

/**
 * @brief task 2 to simulate reading a uint32_t time
 * this can be any sensor being read
 */
void read_time_task(void* pv_parameters) {

	for(;;) {

	}
}

/**
 * @brief simulate read into an IMU struct 
 */
void read_mpu_task(void* pv_parameters) {
	for(;;) {


	}
}

/**
 * @brief This task checks the state of tasks status flag 
 * 	This task samples the heartbeat_flag every 1ms to check if any of the tasks have hanged.
 * 
 * A task will be considered frozen if it does not update its bit value on time (before 100ms are over)
 */
void watchdog_manager_task(void* pv_parameters) {

	for(;;) {

	}
}


void setup() {
	Serial.begin(115200);

	/* set logging level */
	esp_log_level_set(debug_tag, ESP_LOG_INFO);


	xTaskCreate(
			x_task_create_tasks,
			"x_task_create_tasks",
			1024,
			NULL,
			1,
			NULL
		);

}
