
#include <stdbool.h>
#include <stdlib.h>

#include <FreeRTOS.h>
#include <semphr.h>

#include "adc_buffer.h"

adc_buffer_t* init_adc_buffer(uint16_t size) {
    adc_buffer_t* buffer = (adc_buffer_t*) malloc(sizeof(adc_buffer_t));

    buffer->size = size;
    buffer->read_head = 0;
    buffer->write_head = 0;
    
    buffer->mutex = xSemaphoreCreateMutex();
    buffer->read_sem =  xSemaphoreCreateCounting(size, 0);
    
    buffer->data = (uint16_t*) malloc(sizeof(uint16_t)*size);

    return buffer;
}

void adc_buffer_insert(adc_buffer_t* buffer, uint16_t value) {
    if (xSemaphoreTake(buffer->mutex, (TickType_t) 10) == pdTRUE) {

        *(buffer->data + buffer->write_head) = value;

        buffer->write_head = (buffer->write_head+1) % buffer->size;

        xSemaphoreGive(buffer->mutex);
        xSemaphoreGive(buffer->read_sem);
    }
    
}

int16_t adc_buffer_retrieve(adc_buffer_t* buffer) {
    if (xSemaphoreTake(buffer->read_sem, (TickType_t) 1) == pdTRUE) {

        if (xSemaphoreTake(buffer->mutex, (TickType_t) 10) == pdTRUE) {

            uint16_t value = *(buffer->data + buffer->read_head);
            buffer->read_head = (buffer->read_head+1) % buffer->size;

            xSemaphoreGive(buffer->mutex);
            return value;
        } else {
            return -1;
        }
        xSemaphoreGive(buffer->read_sem);
    } else {
        return -1;
    }
}

int16_t adc_buffer_get_average(adc_buffer_t* buffer) {
    if (xSemaphoreTake(buffer->mutex, (TickType_t) 10) == pdTRUE) {
        uint32_t sum;

        for (int i=0; i<buffer->size; i++) {
            sum += *(buffer->data + i);
        }

        xSemaphoreGive(buffer->mutex);
        uint16_t average = sum / buffer->size;
        return average;
    } else {
        return -1;
    }
}