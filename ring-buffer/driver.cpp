/*
 * driver.cpp
 *
 *  Created on: 14 Nov 2025
 *      Author: emwit
 */

#include <iostream>
#include "ring_buffer.h"

struct ring_buffer buffer;

int main() {

	struct ring_buffer* buffer = ring_buffer_init();

	// test if empty 
	// uint8_t ring_empty = ring_buffer_empty(buffer);
	// printf("Empty: %d\r\n", ring_empty);

	// add an item 
	ring_buffer_add(buffer, 34);
	ring_buffer_add(buffer, 35);
	ring_buffer_add(buffer, 88);
	ring_buffer_add(buffer, 67);
	ring_buffer_add(buffer, 388);
	ring_buffer_add(buffer, 900);
	ring_buffer_add(buffer, 674);
	ring_buffer_add(buffer, 909);
	ring_buffer_add(buffer, 2);

	// // show contents 
	dump_ring_buffer(buffer);


	// check if full
	printf("full? %d\r\n", ring_buffer_full(buffer));

	return 0;
}



