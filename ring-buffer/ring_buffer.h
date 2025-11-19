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

/**
* Ring buffer class declaration 
*/
class RingBuffer {
    private:
        uint8_t _window_size;
        uint8_t _head;
        uint8_t _tail;
        uint16_t* _data;
        
    public:
        RingBuffer(uint8_t window_size);
        uint16_t* init();

        uint8_t is_empty();
        uint8_t is_full();
        void add(uint16_t item);
        uint16_t pop();
        void set_zero();
        uint8_t is_not_null();
        void dump();
};
