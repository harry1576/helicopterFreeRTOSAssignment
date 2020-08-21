/*
 * pid.c 
 * 
 * Support PID controllers with different types of input.
 * 
 * Authors: Jos Craw, Josh Hulbert, Harry Dobbs
 * Last Modified: 21.08.2020
 */

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

#include <utils/ustdlib.h>
#include <inc/hw_memmap.h>
#include <inc/hw_types.h>
#include <driverlib/pin_map.h> //Needed for pin configure
#include <driverlib/debug.h>
#include <driverlib/gpio.h>
#include <driverlib/pwm.h>
#include <driverlib/systick.h>
#include <driverlib/sysctl.h>


#include "pid.h"
#include "heli.h"

float clamp(float input, int16_t abs_val) {
    int16_t maximum_val = abs(abs_val);
    int16_t minimim_val = 0 - maximum_val;

    if (input < minimim_val) {
        return minimim_val;
    } else if (input > maximum_val) {
        return maximum_val;
    }

    return input;
}


controller_t* init_PID(float Kp, float Ki, float Kd, uint16_t max_Kp, uint16_t max_Ki, uint16_t max_Kd)
{
    controller_t* pid = (controller_t*)malloc(sizeof(controller_t));
    if (pid == NULL) {
        return false;
    }

    pid->Kp = Kp;
    pid->Ki = Ki;
    pid->Kd = Kd;

    pid->max_Kp = max_Kp;
    pid->max_Ki = max_Ki;
    pid->max_Kd = max_Kd;

    pid->cumulative_err = 0.0;

    pid->p_error = 0;

    return pid;
}


uint16_t update_PID(controller_t* controller, int32_t error, float dT)
{  
    int16_t output;
    
    int16_t tempPErr = controller->Kp*error;
    int16_t tempDErr = controller->Kd*((error-(controller->p_error))/dT);
    float tempIErr = controller->Ki*(error*dT);

    // Clamp the outputs for each of the gain values to reduce instability with large errors
    int16_t pErr = clamp(tempPErr, controller->max_Kp);
    int16_t dErr = clamp(tempDErr, controller->max_Kd);

    controller->cumulative_err += tempIErr;
    controller->cumulative_err = clamp(controller->cumulative_err, controller->max_Ki);

    output = pErr + controller->cumulative_err + dErr;
    controller->p_error = error;

    // Clamp the maximum output values for the outputs
    output = (output > MAX_PWM) ? MAX_PWM : output;
    output = (output < MIN_PWM) ? MIN_PWM : output;

    return output;
}