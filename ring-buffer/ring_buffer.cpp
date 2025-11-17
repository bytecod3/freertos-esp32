/**
 * @file ring_buffer.cpp
 * @brief This file implements functions for ring buffer for data filtering 
 * @author Edwin 
 */

#include "ring_buffer.h"

/**
 * @brief Initialize the ring buffer
 * @return 
 */
ring_buffer_t ring_buffer_init() {
    ring_buffer_t mem = (ring_buffer_t)malloc(sizeof(struct ring_buffer));

    if(mem != NULL) {
        mem->head = 0;
        mem->tail = 0;
        memset(mem->data, 0, RING_BUFFER_LENGTH);
    } else {
        return NULL;
    }

    return mem;
}

/**
 * @brief checks if the ring buffer is empty
 */
uint8_t ring_buffer_empty(ring_buffer_t buffer)
{
    if(buffer->head == buffer->tail) {
        return 1;
    } else {
        return ERR_EMPTY_FULL;
    }
}

/**
 * @brief Checks if the ring buffer is full
 */
uint8_t ring_buffer_full(ring_buffer_t buffer)
{
    if(buffer->head == RING_BUFFER_LENGTH) {
        return 1;
    } else {
        return ERR_EMPTY_FULL;
    }
}

/**
 * @brief Add an item to the buffer 
 * @param buffer pointer to the buffer location
 * @param item uint16_t item to add
 */
void ring_buffer_add(ring_buffer_t buffer, uint16_t item)
{

    if(buffer->data != NULL) {
        if(ring_buffer_full(buffer)) {
            buffer->head = buffer->head % RING_BUFFER_LENGTH;
        } 
        printf("head: %d\r\n", buffer->head);
        buffer->data[buffer->head++] = item;
    }
}

/**
 * @brief Remove an item from the tail of the buffer 
 * @param buffer buffer to remove the item from
 */
uint16_t ring_buffer_remove(ring_buffer_t buffer) {
    if(buffer != NULL) {
        uint16_t a = buffer->data[buffer->tail];
        buffer->tail += 1;
        return a;
    } else {
        return ERR_EMPTY_FULL;
    }
}

/**
 * @brief Set all values of the buffer to 0
 */
void ring_buffer_purge(uint16_t* buffer) {
    if(check_not_null(buffer)) {
        memset(buffer, 0, RING_BUFFER_LENGTH);
    }
}

/**
 * @brief Check that the pointer passed is not NULL
 * @param b pointer to check
 */
uint8_t check_not_null(uint16_t* b) {
    return (b != NULL);
}

/**
 * @brief Print all the contents of the buffer
 * @param buffer ring buffer instance
 */
void dump_ring_buffer(ring_buffer_t buffer)
{
    if(!ring_buffer_empty(buffer)) {
        for(uint8_t i = 0; i < RING_BUFFER_LENGTH; i++) {
            printf("indx: [%d], value: %d\r\n", i, buffer->data[i]);
        }

    } else {
        puts("Buffer is empty");
    }
}