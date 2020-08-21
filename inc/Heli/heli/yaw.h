#ifndef YAW_H
#define YAW_H

#include <driverlib/gpio.h>

// Possible states of the yaw sensors
// The yaw signals are on pins 0 and 1. GPIOPinRead returns a bit packed
// byte where the zeroth bit is the state of pin 0, the first bit is the state 
// of pin 1 on the port, etc. Bits two to seven are not read by the quadrature decoder,
// and hence their bit in the returned byte is zero. So PB0 low and PB1 low returns 0x00
// when read, PB0 high and PB1 low returns 0x01 when read etc.
enum yawStates {B_LOW_A_LOW = 0, B_LOW_A_HIGH, B_HIGH_A_LOW, B_HIGH_A_HIGH};

#define TOTAL_SLOTS 448
#define YAW_INCREMENT 1
#define YAW_DECREMENT 1
#define MAX_DEGREES 360
#define HALF_DEGREES 180
#define CHANNEL_A GPIO_PIN_0
#define CHANNEL_B GPIO_PIN_1


/**
 * Initialise the Yaw peripherals.
 *
 * Initialises all of the required GPIO for yaw quadrature decoding
 */
void init_yaw(void);

/**
 * Sets the callback for the yaw reference.
 * 
 * Sets the callback for the yaw reference, this
 * is used when changing states eg. when finding the
 * reference value the interrupt should trigger the
 * mode change to FLYING but when flying the interrupt
 * corrects for yaw drift.
 * 
 * @param callback the callback to be register to the reference falling edge interrupt 
 */
void set_yaw_ref_callback(void (*callback)());

/**
 * Decodes a quadrature input.
 * 
 * A handler that is registered to the interrupt
 * of the two quadrature phases. This fuction
 * triggers the quadratureDecode function after
 * reading the pin changes and clearing the interrupts
 */
void increment_yaw(void);

/**
* Determines the rotation direction of the disk and increments or decrements
* the slot count appropriately. Sets the slot count to zero if the maximum
* number is exceeded (i.e. 360 degrees rotation performed).
* This function is called upon rising and falling edges on PB1, PB2.
*/
void quadratureDecode(void);

/**
 * Returns the yaw value in slots.
 *
 * Returns the yaw value in slots where the
 * platform is for the first rotation:
 *
 *                 224
 *        280       |       168
 *                  |           
 *     336----------X----------112
 *                  |
 *        392       |       56
 *                  0
 * 
 * The yaw will continue to increase/decrease
 * as the system uses absolute yaw values to
 * map its position this allows multiple rotations
 * to be performed using a single reference change.
 * 
 * @return slots the current position in slots
 */
int get_current_yaw(void);

/**
 * Sets the current yaw.
 * 
 * Sets the current yaw, used to prevent drift
 * by correcting the yaw values based on the
 * yaw reference.
 * 
 * @param yaw the yaw value to set the yaw value to.
 */
void set_current_yaw(int yaw);

/**
 * Resets the yaw value, for use at
 * the reference position.
 */
void reset_yaw(void);

#endif
