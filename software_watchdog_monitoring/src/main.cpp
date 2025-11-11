/**
 * @brief This file tests a method of resetting the ESP32 in case of a software hang
 * @author edwin
 *
 */

#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <esp_log.h>

#define BAUDRATE 115200

/* heartbeat flag */
uint8_t heartbeat_flag = 0x00;

/* tasks heartbeat bit positions */
#define GET_RANDOM_NUMBER_TASK_FLAG (1 << 0)
#define READ_TIME_TASK_FLAG 		(1 << 1)
#define READ_MPU_TASK_FLAG			(1 << 2)

/**
 * declare spinlock (mutex) variable first for use in critical section 
 * This is used specifically for esp32 because it has 2 cores, and track must be kept 
*/
portMUX_TYPE heartbeat_mux = portMUX_INITIALIZER_UNLOCKED;

/* for simulating a mpu data struct */
struct position_3d {
	int8_t x;	/* x position */
	int8_t y;	/* y position */
	int8_t z;	/* z position */
};

/* for logging */
const char* debug_tag = "WATCHDOG";



/**
 * @brief task 1 to simulate reading an actual sensor into integer queue
 */
void get_random_number_task(void* pv_parameters) {

	uint16_t x = 45674;

	for(;;) {
		
		//vTaskDelay(pdMS_TO_TICKS(1000));

		/* crude method of mutual exclusion */
		taskENTER_CRITICAL(&heartbeat_mux);
		{
			/* update heartbeat flag here */
			heartbeat_flag |= GET_RANDOM_NUMBER_TASK_FLAG;
		}
		taskEXIT_CRITICAL(&heartbeat_mux);

		vTaskDelay(pdMS_TO_TICKS(5));

	}

}

/**
 * @brief task 2 to simulate reading a uint32_t time
 * this can be any sensor being read
 */
void read_time_task(void* pv_parameters) {

	uint32_t time_32 = 123456789;

	for(;;) {

		//ESP_LOGI("read time task", "reading time");

		taskENTER_CRITICAL(&heartbeat_mux);
		{
			/* update heartbeat flag here */
			heartbeat_flag |= READ_TIME_TASK_FLAG;
		}
		taskEXIT_CRITICAL(&heartbeat_mux);

		vTaskDelay(pdMS_TO_TICKS(2));

	}
}

/**
 * @brief simulate read into an IMU struct 
 */
void read_mpu_task(void* pv_parameters) {

	struct position_3d pos = {0};

	for(;;) {

		vTaskDelay(pdMS_TO_TICKS(250));

		/* simulate reading x, y, z values */

		taskENTER_CRITICAL(&heartbeat_mux);
		{
			/* update heartbeat flag here */
			heartbeat_flag |= READ_MPU_TASK_FLAG;
		}
		taskEXIT_CRITICAL(&heartbeat_mux);

		vTaskDelay(pdMS_TO_TICKS(2));
	}
}

/**
 * @brief This task checks the state of tasks status flag 
 * 	This task samples the heartbeat_flag every 1ms to check if any of the tasks have hanged.
 * 
 * A task will be considered frozen if it does not update its bit value on time (before 100ms are over)
 */
void watchdog_manager_task(void* pv_parameters) {

	TickType_t last_wake_time = xTaskGetTickCount();
	const TickType_t watchdog_window = 100;

	for(;;) {
		/* wait for next cycle */
		vTaskDelayUntil(&last_wake_time, watchdog_window);


		/* read the heartbeat flag and check for hanging task */
		if(heartbeat_flag & (GET_RANDOM_NUMBER_TASK_FLAG)) {
			/* get_random number task is running OK */
			ESP_LOGI("watchdog manager", "get random number task OK");
		} else {
			ESP_LOGE("watchdog manager", "get random number task frozen, resetting...");
		}

		if(heartbeat_flag & (READ_TIME_TASK_FLAG)) {
			/* read time task is running OK */
			ESP_LOGI("watchdog manager", "read time task OK");
		} else {
			ESP_LOGE("watchdog manager", "read time task frozen, resetting");
		}

		if(heartbeat_flag & (READ_MPU_TASK_FLAG)) {
			/* read mpu task is working OK */
			ESP_LOGI("watchdog manager", "read MPU task OK");
		} else {
			ESP_LOGE("watchdog manager", "read MPU task frozen, resetting");
		}

		/* inspect the heartbeat flag */
		ESP_LOGI("watchdog manager", "heartbeat flag: %0X\r\n", heartbeat_flag);

		taskENTER_CRITICAL(&heartbeat_mux);
		{
			/* reset all bits and wait for the next watch window */
			heartbeat_flag = 0x00;
		}
		taskEXIT_CRITICAL(&heartbeat_mux);

	}
}

/**
 * @brief this task create other tasks then self-deletes
 */
void x_create_tasks() {

	ESP_LOGI(debug_tag, "Creating tasks...");

	/* task 1*/
	xTaskCreate(
		get_random_number_task,		/* task code */
		"get_random_number_task",	/* task name */
		1024, 						/* task stack size in words */
		NULL,						/* parameters to task  */
		2,							/* priority */
		NULL);						/* task handle */

	/* task 2 */			
	xTaskCreate(
		read_time_task,		
		"read_time_task",	
		1024, 						
		NULL,						
		2,							
		NULL);						

	/* task 3 */
	xTaskCreate(
		read_mpu_task,		
		"read_mpu_task",	
		1024, 						
		NULL,						
		2,							
		NULL);						

	/* task 4 - watchdog task */
	xTaskCreate(
		watchdog_manager_task,		
		"watchdog_manager_task",	
		2048, 						
		NULL,						
		1,							
		NULL);	
}

void setup() {
	Serial.begin(115200);

	/* set logging level */
	esp_log_level_set(debug_tag, ESP_LOG_INFO);

	x_create_tasks();

	delay(1000);

}

void loop() {
	/* nothing to do here  */
	vTaskDelay(pdMS_TO_TICKS(2));
}