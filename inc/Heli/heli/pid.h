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
    float Kp; // Proportional Gain
    float Ki; // Integral Gain
    float Kd; // Derivative Gain

    uint16_t max_Kp;
    uint16_t max_Ki;
    uint16_t max_Kd;
    int32_t p_error;

    float cumulative_err;
} controller_t;



//*****************************************************************************
//
// Initalize PID controller
//
//*****************************************************************************
controller_t* init_PID(float Kp, float Ki, float Kd, uint16_t max_Kp, uint16_t max_Ki, uint16_t max_Kd);


//*****************************************************************************
//
// Updates the PID controller
//
//*****************************************************************************
uint16_t update_PID(controller_t* pid, int32_t error, float dT);

#endif