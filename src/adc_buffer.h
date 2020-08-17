#ifndef ADC_BUFFER_H
#define ADC_BUFFER_H

#include <stdint.h>

#include <FreeRTOS.h>
#include <semphr.h>

/**
 * Buffer for the ADC.
 * 
 * The buffer contains a mutex to protect
 * the data. Only one semaphore is used to
 * ensure old data is overwritten and data can
 * only be read when new data is available.
 */ 
typedef struct adc_buffer_t {
    SemaphoreHandle_t mutex;
    SemaphoreHandle_t read_sem;
    uint16_t read_head;
    uint16_t write_head;
    uint16_t size;
    uint16_t* data;
} adc_buffer_t;

/**
 * Creates the ADC buffer of given size.
 * 
 * @param size The size of the ADC buffer
 * @return buffer The address of the created buffer
 */
adc_buffer_t* init_adc_buffer(uint16_t size);

/**
 * Inserts an item at the read head of the buffer.
 * 
 * Inserts an item into a buffer, note this can overwrite
 * existing unused data, this is expected as old ADC
 * is considered useless
 * 
 * @param buffer The buffer to insert the data into
 * @param value The value to insert into the buffer
 */
void adc_buffer_insert(adc_buffer_t* buffer, uint16_t value);

/**
 * Retrieves a value from the buffer.
 * 
 * Retrieves a value from the buffer, returns -1 when
 * the buffer is inaccessible or if there is no new data
 * since the last read.
 * 
 * @param buffer The buffer to retrieve the data from
 * @return value The value retrieved from the buffer
 */
int16_t adc_buffer_retrieve(adc_buffer_t* buffer);

/**
 * Gets the average of the buffer.
 * 
 * Returns the average of the entire buffer, this operation
 * takes the buffer then performs a summation of all contents.
 * A return value of -1 indicates that the buffer was not accessable.
 * 
 * @param buffer The buffer to average
 * @return average The average of the buffer
 */
int16_t adc_buffer_get_average(adc_buffer_t* buffer);


int16_t adc_buffer_get_range(adc_buffer_t* buffer);


#endif