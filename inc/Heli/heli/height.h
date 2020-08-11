#ifndef HEIGHT_H
#define HEIGHT_H

#include <stdint.h>
#include "heli.h"

/**
 * Initialises the peripherals for height.
 * 
 * Initialises the ADC and registers the required
 * interupts
 */
void init_height(void);

/**
 * Triggers a height sample.
 * 
 * Triggers the ADC to sample the current height
 */
void sample_height(void);

/**
 * Gets the current height value (not percent).
 * 
 * Returns the current average value
 * inside the buffer, showing the height
 */
uint16_t get_height(void);

/**
 * Sets the callback for the ADC.
 * 
 * Enables the ADC interrupts and 
 * sets the callback
 * 
 * @param callback The callback function for the ADC
 */
void set_adc_callback(void (*callback)());

/**
 * Sets the maximum height value.
 *
 * Sets the maximum height value for use in calculating
 * percentage height
 *
 * @param value The ADC value to be set as max height
 */
void set_max_height(uint16_t value);

/**
 * Sets the minimum height value.
 *
 * Sets the minimum height value for use in calculating
 * percentage height
 *
 * @param value The ADC value to be set as min height
 */
void set_min_height(uint16_t value);

uint16_t get_min_height(void);

uint16_t get_max_height(void);

/**
 * Converts a given height to percentage.
 *
 * Using a given ADC value to convert to percentage,
 * requires the max and min values to be set
 *
 * @param height The ADC height value to convert
 */
int8_t height_to_percent(uint16_t height);

/**
 * Gets the current height value and returns as a percentage.
 *
 * Uses the get_height function to get the current height then
 * convert to a percentage using the max and min height values.
 */
int8_t get_height_percentage(void);

uint16_t update_height(void);

#endif
