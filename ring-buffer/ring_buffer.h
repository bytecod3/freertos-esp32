/**
 * @file ring_buffer.h 
 * @brief Declares functions to use to implement a ring buffer for data filtering 
 * @author Edwin 
 */

#pragma once 

//#include <Arduino.h>
#include <iostream>
#include <cstdint>
#include <cstring>
#include <cstdlib>

#define  RING_BUFFER_LENGTH   6

extern uint8_t head;
extern uint8_t tail;

struct ring_buffer {
    uint8_t head;
    uint8_t tail;
    uint16_t data[RING_BUFFER_LENGTH];
};

struct ring_buffer* ring_buffer_init();
uint8_t ring_buffer_empty(struct ring_buffer* buffer);
uint8_t ring_buffer_full(struct ring_buffer* buffer);
void ring_buffer_add(struct ring_buffer* buffer, uint16_t item);
void ring_buffer_remove();
void ring_buffer_purge();
uint8_t check_not_null(uint16_t*);
void dump_ring_buffer(struct ring_buffer* buffer);

