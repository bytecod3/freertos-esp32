/**
 * @file ring_buffer.cpp
 * @brief This file implements functions for ring buffer for data filtering 
 * @author Edwin 
 */

#include "ring_buffer.h"

uint8_t head = 0;
uint8_t tail = 0;

struct ring_buffer* ring_buffer_init() {
    struct ring_buffer* mem = (struct ring_buffer*) malloc(sizeof(struct ring_buffer));

    if(mem != NULL) {
        mem->head = 0;
        mem->tail = 0;
        memset(mem->data, 0, RING_BUFFER_LENGTH);
    } else {
        return NULL;
    }

    return mem;
}

uint8_t ring_buffer_empty(struct ring_buffer* buffer) {
    if(buffer->head == buffer->tail) {
        return 1;
    } else {
        return 0;
    }
}

uint8_t ring_buffer_full(struct ring_buffer* buffer) {
    
    if(buffer->head == RING_BUFFER_LENGTH) {
        return 1;
    } else {
        return 0;
    }
}

void ring_buffer_add(struct ring_buffer* buffer, uint16_t item) {

    if(buffer->data != NULL) {
        if(ring_buffer_full(buffer)) {
            buffer->head = buffer->head % RING_BUFFER_LENGTH;
        } 
        printf("head: %d\r\n", buffer->head);
        buffer->data[buffer->head++] = item;
    }
}

uint16_t ring_buffer_remove(uint16_t* buffer) {
    if(buffer != NULL) {
        uint16_t a = buffer[tail];
        tail += 1;
        return a;
    }
}

void ring_buffer_purge(uint16_t* buffer) {
    if(check_not_null(buffer)) {
        memset(buffer, 0, RING_BUFFER_LENGTH);
    }
}

uint8_t check_not_null(uint16_t* b) {
    return (b != NULL);
}

void dump_ring_buffer(struct ring_buffer* buffer) {
    if(!ring_buffer_empty(buffer)) {
        for(uint8_t i = 0; i < RING_BUFFER_LENGTH; i++) {
            printf("indx: [%d], value: %d\r\n", i, buffer->data[i]);
        }

    } else {
        puts("Buffer is empty");
    }
}