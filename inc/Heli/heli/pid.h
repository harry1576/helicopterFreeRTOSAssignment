#ifndef PID_H
#define PID_H

#include <stdint.h>


//*****************************************************************************
//
// PID structure
//
//*****************************************************************************
typedef struct 
{
    uint16_t Kp; // Proportional Gain
    uint16_t Ki; // Integral Gain
    uint16_t Kd; // Derivative Gain
    int32_t p_error; // Proportional Error
    int32_t i_error; // Integral Error
    int32_t d_error;
    int32_t previous_error;
    int32_t output;
} controller_t;



//*****************************************************************************
//
// Initalize PID controller
//
//*****************************************************************************
void init_PID(controller_t* pid, uint16_t Kp, uint16_t Ki, uint16_t Kd);


//*****************************************************************************
//
// Updates the PID controller
//
//*****************************************************************************
uint32_t update_PID(controller_t* pid, int32_t error, uint16_t dT);

#endif