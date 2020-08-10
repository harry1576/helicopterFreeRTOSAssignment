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

    uint16_t max_Kp;
    uint16_t max_Ki;
    uint16_t max_Kd;
    int32_t p_error;

    int16_t cumulative_err;
} controller_t;



//*****************************************************************************
//
// Initalize PID controller
//
//*****************************************************************************
controller_t* init_PID(uint16_t Kp, uint16_t Ki, uint16_t Kd, uint16_t max_Kp, uint16_t max_Ki, uint16_t max_Kd);


//*****************************************************************************
//
// Updates the PID controller
//
//*****************************************************************************
uint16_t update_PID(controller_t* pid, int32_t error, uint16_t dT);

#endif