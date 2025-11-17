/**
 * @file ring_buffer.h 
 * @brief Declares functions to use to implement a ring buffer for data filtering 
 * @author Edwin Mwiti
 */

#pragma once 

#include <iostream>
#include <cstdint>
#include <cstring>
#include <cstdlib>

#define DUMP_LINEAR     (1)  ///< print array in a straight line 
#define DUMP_VERTICAL   (0)  ///< printf array in vertical fashion showing index and value

/**
 * Errors list for ring buffer functions 
 */
typedef enum
{
    ERR_EMPTY_FULL = 0,
    ERR_NULL = -1,
    ERR_FULL = -2,
    ERR_FATAL = -3
} ERR;

#define  RING_BUFFER_LENGTH   (6)       ///< how many items the buffer can hold 


struct ring_buffer {
    uint8_t head;
    uint8_t tail;
    uint16_t data[RING_BUFFER_LENGTH];
};

typedef struct ring_buffer* ring_buffer_t;

ring_buffer_t ring_buffer_init();
uint8_t ring_buffer_empty(ring_buffer_t buffer);
uint8_t ring_buffer_full(ring_buffer_t buffer);
void ring_buffer_add(ring_buffer_t buffer, uint16_t item);
void ring_buffer_remove();
void ring_buffer_purge(ring_buffer_t);
uint8_t check_not_null(ring_buffer_t);
void dump_ring_buffer(ring_buffer_t buffer);
