/**
 * This file tests a methid of resetting the ESP32 in case of a software hang
 *
 */

#include <Arduino.h>


void setup() {
	Serial.begin(115200);

	create_tasks();
}
