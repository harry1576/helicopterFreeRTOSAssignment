#ifndef CONTROLLER_H
#define CONTROLLER_H

/**
 * The different helicopter states
 */
typedef enum
{
    LANDED,
    FIND_REF,
    FLYING,
    LANDING
} control_states_t;

typedef struct 
{
    int32_t ground_reference;
    int32_t current_altitude; // current height 
    int32_t target_altitude; // desired height

    int32_t target_yaw;
    int32_t current_yaw;

    int8_t state; // helicopter state 
} heli_t;

/**
 * Initialises both of the controllers for the Helicopter
 */
void init_controllers(void);

/**
 * Runs an update for both of the controllers.
 * 
 * This function is called regularly as
 * a FreeRTOS task to update both of the controllers.
 */
void update_controllers(void);

/**
 * Gets the current helicopter state.
 * 
 * Reterns the current state of the helicopter 
 * from one of the following:
 * LANDED, FIND_REF, FLYING, LANDED
 * 
 * @return state the current state of the helicopter
 */
int8_t get_helicopter_state(void);

/**
 * Sets the state of the helicopter.
 * 
 * @param state the state to set the helicopter to.
 */
void set_helicopter_state(int8_t state);

/**
 * Increments the target angle of the helicopter.
 * 
 * Increments the helicopter target angle by 19 slots (15 degrees)
 */
void increment_angle(void);

/**
 * Decrements the target angle of the helicopter.
 * 
 * Decrements the helicopter target angle by 19 slots (15 degrees)
 */
void decrement_angle(void);

/**
 * Corrects drift in the yaw.
 * 
 * Correct the helicopter yaw drift by rounding
 * the current yaw value to the closest yaw at reference
 * (a multiple of TOTAL_SLOTS).
 */
void yaw_ref_handler(void);

/**
 * Called when the yaw reference is found when in mode FIND_REF.
 * 
 * When the helicopter is landed this function is set as
 * the callback for the yaw reference interrupt. Once the helicopter
 * crosses the reference this first time this function is executed
 * causing the helicopter to enter flying mode. Once called this function
 * sets the new yaw reference interrupt to be yaw_ref_handler to
 * handle yaw drift.
 */
void ref_found(void);

/**
 * Increments the target height of the helicopter.
 * 
 * Increments the helicopter target height by 10%
 */
void increment_height(void);

/**
 * Decrements the target height of the helicopter.
 * 
 * Decrements the helicopter target height by 10%
 */
void decrement_height(void);

/**
 * Sets the ground reference for the helicopter.
 * 
 * This function updates the helicopter ground
 * reference, this is used to ensurer the ground reference
 * remains accurate while landed. This function is called while
 * the helicopter is landed. 
 */
void set_heli_ground_ref(uint32_t value);

/**
 * Sets the helicopter to Mid flight mode.
 * 
 * Sets the helicopter height to 50%
 */
void mid_flight_adjustment(void);

/**
 * Spins the helicopter 180 degrees.
 * 
 * Increases the helicopter target by
 * 224 slots (180 degrees)
 */
void spin_180_deg(void);

/**
 * Sets a new target yaw.
 * 
 * @param target the new target yaw
 */
void set_yaw_target(int16_t target);

/**
 * Sets a new height target.
 * 
 * @param target the new target height
 */
void set_height_target(int16_t target);

#endif