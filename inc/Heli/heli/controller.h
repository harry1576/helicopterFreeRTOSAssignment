#ifndef CONTROLLER_H
#define CONTROLLER_H

//*****************************************************************************
//
// Enumerated Helicopter States
//
//*****************************************************************************
typedef enum
{
    LANDED,
    SWEEP,
    FLYING,
    LANDING
} control_states_t;

//*****************************************************************************
//
// Helicopter structure
//
//*****************************************************************************
typedef struct 
{
    int32_t ground_reference; // desired height
    int32_t current_altitude; // current height 
    int32_t target_altitude; // desired height

    int32_t reference_yaw; // desired height
    int32_t target_yaw;
    int32_t current_yaw;

    int32_t state; // helicopter state 
} heli_t;

//*****************************************************************************
//
// Initialisation for PWM (PWM Module 0 PWM 7 for main rotor and
// PWM module 1 PWM 5 for the tail rotor).
//
//*****************************************************************************
void init_controllers(void);

//*****************************************************************************
//
// Set the main rotor PWM.
//
//*****************************************************************************
void update_controllers(void);


#endif