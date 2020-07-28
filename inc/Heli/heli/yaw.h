#ifndef YAW_H

/**
 * Initialise the Yaw peripherals.
 *
 * Initialises all of the required GPIO for yaw quadrature decoding
 */
void init_yaw(void);

/**
 * Updates the stored yaw values.
 *
 * Performs an update to the current yaw values, not required
 * as system is using interrupts, useful for testing.
 *
 * @param rotation The rotation in degrees to set the yaw to
 */
void set_yaw(int rotation);

/**
 * Increments the yaw value by a defined value for the
 * heli rig.
 */
void increment_yaw(void);

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
 * Returns the current velocity of the yaw.
 *
 * Returns the current yaw velocity using the built in QEI
 * API
 */
int get_current_velocity(void);

/**
 * Resets the yaw value, for use at
 * the reference position.
 */
void reset_yaw(void);

#endif
