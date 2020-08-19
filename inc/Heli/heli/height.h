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

void set_max_height(uint16_t value);

void set_min_height(uint16_t value);

void set_current_height(uint16_t value);

uint16_t get_current_height_percent(void);

#endif
