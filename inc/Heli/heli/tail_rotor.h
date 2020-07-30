#ifndef TAIL_ROTOR_H_
#define TAIL_ROTOR_H_

//*****************************************************************************
// Thurs PM Group 23
//
// tailRotorController.h - This file contains a PID controller that controls
// the tail rotor. It additionally has the files required to setup the tail rotor.
//
// Authors (student ID): Harry Dobbs (89030703), Sam Purdy (48538646), Sam Dunshea (26500850)
// Last modified: 2.6.2019
//
//*****************************************************************************

//*****************************************************************************
//
// @Description This function is used initialize the tail rotor PWM
// @Param void
// @Return void
//
//*****************************************************************************
void init_tail_rotor (void);

//*****************************************************************************
//
// @Description This function is used to set the duty cycle and frequency of
// the tail rotor PWM.
// @Param ui32Freq is the desired PWM frequency
// @param ui32Duty is the desired duty cycle for the tail rotor
// @Return none
//
//*****************************************************************************
void set_tail_pwm (uint32_t ui32Freq, uint32_t ui32Duty);


#endif /* TAIL_ROTOR_H_ */
