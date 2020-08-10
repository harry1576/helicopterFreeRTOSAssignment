/*
 * pid.c 
 * Support PID controllers with different types of input.
 * Authors: Jos Craw, Josh Hulbert, Harry Dobbs
 */

#include <stdint.h>
#include <stdbool.h>
#include "utils/ustdlib.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/pin_map.h" //Needed for pin configure
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/pwm.h"
#include "driverlib/systick.h"
#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"

#include "pid.h"
//*****************************************************************************
//
// Initialisation for PID controller instance
//
//*****************************************************************************
void init_PID(controller_t* pid, uint16_t Kp, uint16_t Ki, uint16_t Kd)
{
    pid->Kp = Kp;
    pid->Ki = Ki;
    pid->Kd = Kd;

    pid->p_error = 0;
    pid->i_error = 0;
    pid->d_error = 0;

    pid->previous_error = 0;

    pid->output = 0;
}

//*****************************************************************************
//
// Updates controller output based on error and change in time.
//
//*****************************************************************************
void update_PID(controller_t* pid, int32_t error, uint16_t dT)
{
    pid->p_error = error;
    pid->d_error = (error - pid->previous_error) / dT;
    pid->i_error +=  pid->previous_error <= 100 ? pid->previous_error : 0 ;

    pid->previous_error = error;
    
    pid->output = (pid->Kp * pid->p_error) + (pid->Ki * pid->i_error) + (pid->Kd * pid->d_error);
    pid->output = pid->output <= 100 ? pid->output: 100;
    pid->output = pid->output >= 0 ? pid->output: 0;
}

//*****************************************************************************
//
// Gets controller PID output
//
//*****************************************************************************
uint32_t get_PID_output(controller_t* pid)
{
    return pid->output;
}