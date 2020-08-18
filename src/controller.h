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
    FIND_REF,
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
    int32_t ground_reference;
    int32_t current_altitude; // current height 
    int32_t target_altitude; // desired height

    int32_t target_yaw;
    int32_t current_yaw;

    int8_t state; // helicopter state 
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

int8_t get_helicopter_state(void);

void set_helicopter_state(int8_t state);

void increment_angle(void);

void decrement_angle(void);

void increment_height(void);

void decrement_height(void);

void set_heli_ground_ref(uint32_t value);

void mid_flight_adjustment(void);

void spin_180_deg(void);

#endif