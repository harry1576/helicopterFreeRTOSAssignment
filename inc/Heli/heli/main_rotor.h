#ifndef MAIN_ROTOR_H_
#define MAIN_ROTOR_H_

//*****************************************************************************
// Thurs PM Group 23
//
// mainRotorController.c - This file contains a PID controller that controls
// the main rotor. It additionally has the files required to setup the main rotor.
//
// Authors: Jos Craw, Josh Hulbert, Harry Dobbs
// Last modified: 2.6.2019
//
//*****************************************************************************

//*****************************************************************************
//
// @Description This function is used initialize the main rotor PWM
// @Param void
// @Return void
//
//*****************************************************************************
void init_main_rotor (void);


//*****************************************************************************
//
// @Description This function is used to set the duty cycle and frequency of
// the main PWM.
// @Param ui32Freq
// @param ui32Duty
// @Return none
//
//*****************************************************************************
void set_main_PWM (uint32_t ui32Freq, uint32_t ui32Duty);


#endif /* MAIN_ROTOR_CONTROLLER_H_ */