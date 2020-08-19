#ifndef HELI_DATA_H
#define HELI_DATA_H

/**
 * Gets the current height as a percentage to
 * be used to generate labels.
 * 
 * @return height String containing the height percentage
 */
char* get_height_percent(void);

/**
 * Gets the current yaw slot to
 * be used to generate labels.
 * 
 * @return yaw String containing the yaw slot count
 */
char* get_yaw_slot(void);

/**
 * Gets the current main PWM output to
 * be used to generate labels.
 * 
 * @return pwm String containing the main output PWM
 */
char* get_main_pwm_output(void);

/**
 * Gets the current tail PWM output to
 * be used to generate labels.
 * 
 * @return pwm String containing the tail output PWM
 */
char* get_tail_pwm_output(void);

#endif