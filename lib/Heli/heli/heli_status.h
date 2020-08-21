#ifndef HELI_DATA_H
#define HELI_DATA_H

/**
 * Gets the current height as a percentage to
 * be used to fill labels.
 * 
 * @param label the char pointer to copy the label into
 */
void get_height_percent(char* label);

/**
 * Gets the current yaw slot to
 * be used to fill labels.
 * 
 * @param label the char pointer to copy the label into
 */
void get_yaw_slot(char* label);

/**
 * Gets the current main PWM output to
 * be used to fill labels.
 * 
 * @param label the char pointer to copy the label into
 */
void get_main_pwm_output(char* label);

/**
 * Gets the current tail PWM output to
 * be used to fill labels.
 * 
 * @param label the char pointer to copy the label into
 */
void get_tail_pwm_output(char* label);

#endif