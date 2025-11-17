#include <Arduino.h>
#include "ESP.h"

void setup() {
	Serial.begin(115200);

	// simulate hardware setup
	int index = 0;
	while(index < 6) {
		Serial.printf("Index: [%d] \r\n", index);
		index++;
		delay(2000);
	}

	// restart the ESP
	Serial.println("Resetting");
	ESP.restart();
}

void loop() {

}
