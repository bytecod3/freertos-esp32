/**
 * @file ring_buffer.cpp
 * @brief This file implements functions for ring buffer for data filtering 
 * @author Edwin 
 */

#include "ring_buffer.h"

RingBuffer::RingBuffer(uint8_t window_size) {
    uint8_t _d_wndw_sz = 10;

    /* window size can only be max 255 */
    if(window_size > UINT8_MAX) {
        this->_window_size = _d_wndw_sz;
    } else {
        this->_window_size = window_size;
    }

}

/**
 * @brief Initialize the ring buffer
 * @return pointer to malloced buffer memory
 */
uint16_t* RingBuffer::init() {
    this->_data = (uint16_t*) malloc(sizeof(uint16_t) * this->_window_size);
    if(this->_data != nullptr) {
        this->_head = 0;
        this->_tail = 0;
        memset(this->_data, 0, this->_window_size);
    } else {
        return nullptr;
    }  
}

/**
 * @brief checks if the ring buffer is empty
 */
uint8_t RingBuffer::is_empty() {
    if(this->_head == this->_tail) {
        return 1;
    } else {    
        return 0;
    }
}

/**
 * @brief Checks if the ring buffer is full
 */
uint8_t RingBuffer::is_full() {
    if(  ( (this->_head + 1) % this->_window_size ) == (this->_tail) ){
        return 1;
    } else {
        return 0;
    }
}

/**
 * @brief Add an item to the buffer
 * @param item uint16_t item to add
 */
void RingBuffer::add(uint16_t data) {
    printf("add: %d \r\n", data);

    if(this->is_full()) {
        this->_head %= this->_window_size; /* wrap around */
    }

    this->_data[this->_head++] = data;

}

/**
 * @brief Remove an item from the tail of the buffer 
 * @return removed item 
 */
uint16_t RingBuffer::pop() {
    uint16_t item;

    if(this->is_not_null()) {
        item = this->_data[this->_tail];
        this->_tail = (this->_tail + 1) % this->_window_size;
    }

    return this->_data[this->_tail];
}

/**
 * @brief Set all values of the buffer to 0
 */
void RingBuffer::set_zero() {
    if (this->is_not_null()) {
        memset(this->_data, 0, this->_window_size);
    }
}

/**
 * @brief Check that the pointer to buffer passed is not NULL
 * @param b pointer to check
 */
uint8_t RingBuffer::is_not_null() {
    return (this->_data != nullptr);
}

/**
 * @brief Print all the contents of the buffer
 * @param buffer ring buffer instance
 * 
 */
void RingBuffer::dump() {
    if(is_not_null()) {
        for(uint8_t i = 0; i < this->_window_size; i++) {

            #if (DUMP_VERTICAL ^ DUMP_LINEAR)
                #if DUMP_VERTICAL
                            printf("indx: [%d], value: %d\r\n", i, buffer->data[i]);
                #elif DUMP_LINEAR
                            printf("%d ", this->_data[i]);
                #endif
            #endif
        }


    } else {
        puts("Buffer is empty");
    }
}
