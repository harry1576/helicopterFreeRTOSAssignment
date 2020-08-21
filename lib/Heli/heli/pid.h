#ifndef PID_H
#define PID_H

#include <stdint.h>

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



/**
 * Initalises the PID controller.
 * 
 * Creates a PID controller given the gain values
 * and the maximum output values for each of the
 * components.
 * 
 * @param Kp The Proportional Gain
 * @param Ki The Integral Gain
 * @param Kd The Differential Gain
 * @param max_Kp The absolute maximum proportional output value 
 * @param max_Ki The absolute maximum integral output value
 * @param max_Kd The absolute maximum differential output value  
 * 
 * @return controller The pointer to the created controller
 */
controller_t* init_PID(float Kp, float Ki, float Kd, uint16_t max_Kp, uint16_t max_Ki, uint16_t max_Kd);


/**
 * Updates the PID controller.
 * 
 * Uses the provided PID controller with a given error
 * to provide an output value. This is used to update the
 * tail and main PWM values.
 * 
 * @param controller the controller to use to generate the output
 * @param error the error to use to determine the output
 * @param dT the time since the last contoller call
 * 
 * @return output the putput value of the controller
 */
uint16_t update_PID(controller_t* controller, int32_t error, float dT);

#endif