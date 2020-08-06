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

void quadratureIntHandler(void);

/**
 * Initialise the Yaw peripherals.
 *
 * Initialises all of the required GPIO for yaw quadrature decoding
 */
void init_yaw(void);

/**
 * Increments the yaw value by a defined value for the
 * heli rig.
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
 * Returns the yaw value in degrees.
 *
 * Returns the yaw value in degrees where the
 * platform is:
 *
 *              -180/180
 *       -135       |       135
 *                  |           
 *     -90----------X----------90
 *                  |
 *        -45       |       45
 *                  0
 */
int get_current_yaw(void);

/**
 * Resets the yaw value, for use at
 * the reference position.
 */
void reset_yaw(void);

#endif
