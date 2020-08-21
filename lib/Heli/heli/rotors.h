#ifndef ROTORS_H
#define ROTORS_H


/**
 * Initialisation for PWM (PWM Module 0 PWM 7 for main rotor and
 * PWM module 1 PWM 5 for the tail rotor).
 */
void init_pwm(void);


/**
 * Sets the PWM of the main rotor.
 * 
 * @param ui32MainFreq the frequency to set the main rotor to
 * @param ui32MainDuty the duty cycle to set the main rotor to
 */
void set_main_PWM(uint32_t ui32MainFreq, uint32_t ui32MainDuty);


/**
 * Sets the PWM of the tail rotor.
 * 
 * @param ui32MainFreq the frequency to set the tail rotor to
 * @param ui32MainDuty the duty cycle to set the tail rotor to
 */
void set_tail_PWM(uint32_t ui32TailFreq, uint32_t ui32TailDuty);

/**
 * Gets the current PWM of the main rotor.
 * 
 * @return pwm the duty cycle of the main rotor
 */
uint8_t get_main_pwm(void);

/**
 * Gets the current PWM of the tail rotor.
 * 
 * @return pwm the duty cycle of the tail rotor
 */
uint8_t get_tail_pwm(void);

#endif