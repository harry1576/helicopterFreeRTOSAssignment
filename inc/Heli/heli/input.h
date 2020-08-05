#ifndef HELI_INPUT_H
#define HELI_INPUT_H

#include <stdint.h>
#include <stdbool.h>

/**
 * Initalises the required GPIO for input.
 */
void init_input(void);

/**
 * Polls the input buttons and switches.
 * 
 * Polls the inputs on the device and triggers
 * the set callback when complete 
 */
void update_input(void);

/**
 * Sets the callback for a given button.
 * 
 * Sets the callback for a button press given
 * the layer and the button. Where the button
 * number is:
 * 
 *                  [0]
 *              [3]     [1]
 *                  [2]
 * 
 * -------------------------------------------
 * 
 * @param callback The function callback
 * @param layer The layer for the button to be on
 * @param button_num The number for the button
 */
int8_t set_input_callback(void (*callback)(), bool layer, uint8_t button_num);

#endif