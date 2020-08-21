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
 * Sets the callback for the ADC.
 * 
 * Enables the ADC interrupts and 
 * sets the callback
 * 
 * @param callback The callback function for the ADC
 */
void set_adc_callback(void (*callback)(uint32_t));

/**
 * Sets the maximum height for the HeliRigs.
 * 
 * @param value The adc value for the max height
 */
void set_max_height(uint16_t value);

/**
 * Sets the minimum height for the HeliRigs.
 * 
 * @param value The adc value for the min height
 */
void set_min_height(uint16_t value);

/**
 * Sets the current height of the helicopter.
 * 
 * Sets the helicopter current height to be used
 * to get the current height percentage
 * 
 * @param value The adc value for the current height
 */
void set_current_height(uint16_t value);

/**
 * Gets the current height in percent.
 * 
 * @return height The current percentage height
 */
int16_t get_current_height(void);

#endif
