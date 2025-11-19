/*
 * driver.cpp
 *
 *  Created on: 14 Nov 2025
 *      Author: emwiti
 */

#include <iostream>
#include "ring_buffer.h"

#define MAX_VALUES 1500

/* create a buffer instance */
uint8_t BUFFER_WINDOW = 10;
RingBuffer data_buffer(BUFFER_WINDOW);

/*******************************INSERTION SORT*****************/

void insertion_sort(uint16_t arr[], uint16_t len) {

	for(int step =1; step < len; step++) {
		int key = arr[step];
		int j = step - 1;

		while (j >= 0 && (key < arr[j])) {
			arr[j + 1] = arr[j];
			--j;
		}

		arr[j + 1] = key;
	}
}

void dump_array(uint16_t arr[], uint16_t len) {
	for(int i = 0; i < len; i++) {
		printf("%d ", arr[i]);
	}

	puts("\r\n");
}

/*************************************SHELL SORT*****************/

int main() {
	data_buffer.init();

	// test if empty 
	// uint8_t ring_empty = ring_buffer_empty(buffer);
	// printf("Empty: %d\r\n", ring_empty);

	// add an item 
	data_buffer.add(34);
	data_buffer.add(35);
	data_buffer.add(88);
	data_buffer.add(67);
	data_buffer.add(388);
	data_buffer.add(900);
	data_buffer.add(674);
	data_buffer.add(909);
	data_buffer.add(2);

	// show contents 
	data_buffer.dump();

	// test buffer purging 
	// ring_buffer_purge(buffer);

	// sort the contents 

	// insertion_sort(buffer->data, RING_BUFFER_LENGTH);

	// // recheck the buffer contents
	// puts("\r\nsorted buffer\r\n");
	// dump_ring_buffer(buffer);

	// /**
	//  * test the filter 
	//  */
	
	// /**
	//  * Open csv raw file 
	//  */
	// FILE* raw_file = fopen("vaisala1_data_raw.csv", "r");
	// if (raw_file == NULL)
	// {
	// 	printf("Error opening file ");
	// }

	// /* file to store filtered values with moving average */
	// FILE* fp_filt = fopen("vaisala1_mov_avg_filtered.csv", "w");
	// if(fp_filt == NULL) {
	// 	printf("Failed to open file for filtered data");
	// }

	// /* file to store filtered values with median filter */
	
	// /* array to store the read values */
	// int ppm_raw[MAX_VALUES] = {0};
	// int ppm_movavg_filtered[MAX_VALUES] = {0};
	// int ppm_median_filtered[MAX_VALUES] = {0};

	// int index = 0; /* holds the max values in raw array */

	// /* read from file to raw data array */
	// while (fscanf(raw_file, "%d", &ppm_raw[index]) == 1) {
	// 	index++;
	// 	if(index >= MAX_VALUES) {
	// 		printf("Max values reached\r\n");
	// 		break;
	// 	}
	// }
	// fclose(raw_file);

	// /* feed raw values into ring buffer */
	// for (int j = 0; j < index; j++) {
	// 	ring_buffer_add(buffer, (uint16_t)ppm_raw[j]);

	// 	/*======================== loop through buffer and apply moving average ======================== */
	// 	int sum = 0;
	// 	int f = 0;
	// 	for(int i= 0; i < RING_BUFFER_LENGTH; i++) {
	// 		sum += buffer->data[i];
	// 		f = sum / RING_BUFFER_LENGTH;
	// 	}

	// 	/* write to array */
	// 	ppm_movavg_filtered[j] = f;
	// }

	// /* write moving average filtered values to file */
	// int l = sizeof(ppm_movavg_filtered) / sizeof(ppm_movavg_filtered[0]);
	// for(int k = 0; k < l; k++) {
	// 	fprintf(fp_filt, "%d\n", ppm_movavg_filtered[k]);
	// }

	// fclose(fp_filt);

	// /* apply median filter and compare the readings */
	// /* use the array of raw values */
	// for(int j = 0; j < index; j++) {
	// 	ring_buffer_add(buffer, (uint16_t)ppm_raw[j]);

	// 	// todo: add a delay to wait for buffer to become full 

	// 	/**
	// 	 * with a moving window, find the median of each window
	// 	 * sort the array first then find median
	// 	 **/
	// 	insertion_sort(buffer->data, RING_BUFFER_LENGTH);

	// 	/**
	// 	 * for even window size Med = (a(N/2) + a((N/2) + 1)) / 2;
	// 	 */
	// 	uint16_t m = ( (buffer->data[RING_BUFFER_LENGTH/2]) + (buffer->data[(RING_BUFFER_LENGTH / 2) + 1]) ) / 2;

	// 	/** store the median values in a separate buffer */
	// 	ppm_median_filtered[j] = m;
	// }

	// /* put ppm_median filtered values in a file */
	// FILE* median_filtered_values_file = fopen("vaisala_median_filtered.csv", "w");
	// if (median_filtered_values_file == NULL) {
	// 	puts("Median file handle is NULL\r\n");
	// }

	// for(int k = 0; k < index; k++) {
	// 	fprintf(median_filtered_values_file, "%d\n", ppm_median_filtered[k]);
	// }

	// fclose(median_filtered_values_file);

	return 0;
}



