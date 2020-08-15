#ifndef ROTORS_H
#define ROTORS_H


//*****************************************************************************
//
// Initialisation for PWM (PWM Module 0 PWM 7 for main rotor and
// PWM module 1 PWM 5 for the tail rotor).
//
//*****************************************************************************
void init_pwm(void);


//*****************************************************************************
//
// Set the main rotor PWM.
//
//*****************************************************************************
void set_main_PWM(uint32_t ui32MainFreq, uint32_t ui32MainDuty);


//*****************************************************************************
//
// Set the tail rotor PWM.
//
//*****************************************************************************
void set_tail_PWM(uint32_t ui32TailFreq, uint32_t ui32TailDuty);

uint8_t get_main_pwm(void);

uint8_t get_tail_pwm(void);

#endif