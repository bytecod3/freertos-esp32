/*
 * driver.cpp
 *
 *  Created on: 14 Nov 2025
 *      Author: emwit
 */

#include <iostream>
#include "ring_buffer.h"

#define MAX_VALUES 1500

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
	//dump_ring_buffer(buffer);

	// for(int i = 0; i< RING_BUFFER_LENGTH; i++) {
	// 	printf("%d\r\n", buffer->data[i]);
	// }


	// check if full
	//printf("full? %d\r\n", ring_buffer_full(buffer));

	/**
	 * test the filter 
	 */
	
	/**
	 * Open csv raw file 
	 */
	FILE* fp = fopen("vaisala1_data_raw.csv", "r");
	if(fp == NULL) {
		printf("Error opening file ");
	}
	
	/* file to store filtered values */
	FILE* fp_filt = fopen("vaisala1_filtered.csv", "w");
	if(fp_filt == NULL) {
		printf("Failed to open file for filtered data");
	}

	/* array to store the read values */
	int ppm_raw[MAX_VALUES] = {0};
	int ppm_filtered[MAX_VALUES] = {0};
	int index = 0;

	while(fscanf(fp, "%d", &ppm_raw[index]) == 1) {
		index++;
		if(index >= MAX_VALUES) {
			printf("Max values reached\r\n");
			break;
		}

	}

	fclose(fp);


	// verify values 
	for (int j = 0; j < index; j++) {
		//printf("%d\r\n", ppm_raw[j]);

		/* feed into ring buffer */
		ring_buffer_add(buffer, (uint16_t)ppm_raw[j]);

		/* loop through the buffer find average */
		int sum = 0;
		int f = 0;
		for(int i= 0; i < RING_BUFFER_LENGTH; i++) {
			sum += buffer->data[i];
			f = sum / RING_BUFFER_LENGTH;
		}

		/* write to array */
		ppm_filtered[j] = f;
	}

	/* write filtered values to file */
	int l = sizeof(ppm_filtered) / sizeof(ppm_filtered[0]);
	for(int k = 0; k < l; k++) {
		fprintf(fp_filt, "%d\n", ppm_filtered[k]);
	}

	fclose(fp_filt);

	return 0;
}



