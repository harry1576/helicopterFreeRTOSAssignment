/*
 * controller.c 
 * Controller used to drive the logic to ensure correct PWM.
 * Authors: Jos Craw, Josh Hulbert, Harry Dobbs
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

#include "heli.h"
#include "pid.h"
#include "controller.h"
#include "rotors.h"
#include "height.h"
#include "input.h"
#include "yaw.h"
#include "logging.h"

static controller_t main_controller;
static controller_t tail_controller;
static heli_t* helicopter;

void ref_found(void);

//*****************************************************************************
//
// Initialisation for Controllers (One for main rotor and one for tail rotor).
//
//*****************************************************************************
void init_controllers()
{
    helicopter = (heli_t*)malloc(sizeof(heli_t));
    // Initialise PID controllers
    controller_t* main_controller = init_PID(MAIN_KP, MAIN_KI, MAIN_KD, MAIN_MAX_KP, MAIN_MAX_KI, MAIN_MAX_KD);

    controller_t* tail_controller = init_PID(TAIL_KP, TAIL_KI, TAIL_KD, TAIL_MAX_KP, TAIL_MAX_KI, TAIL_MAX_KD);

    //TODO: CHANGE TO ADC VALUE
    helicopter->ground_reference = get_height();
    helicopter->current_altitude = 0;
    
    set_helicopter_state(LANDED);

    helicopter->current_yaw = 0;
    helicopter->target_yaw = 0;

    set_min_height(helicopter->ground_reference); // (4095*1)/3.3 -> Maximum height as we know if 0.8V less than ground
    set_max_height(helicopter->ground_reference - 1240); // (4095*1)/3.3 -> Maximum height as we know if 0.8V less than ground
    
    helicopter->target_altitude = 0;
}

void set_helicopter_state(int8_t state)
{
    if (state == LANDED) {
        set_yaw_ref_callback(ref_found);
    }

    helicopter->state = state;
    #if HELI_LOG_LEVEL >= 3
    switch (state)
    {
        case LANDED:
            debug_log("LANDED");
            break;
        case FIND_REF:
            debug_log("FIND_REF");
            break;
        case FLYING:
            debug_log("FLYING");
            break;
        case LANDING:
            debug_log("LANDING");
            break;
    }
    #endif
}

int8_t get_helicopter_state(void)
{
    return helicopter->state;
}

void increment_height(void)
{
    helicopter->target_altitude += HEIGHT_INCREMENT_AMOUNT;
}

void decrement_height(void)
{
    helicopter->target_altitude -= HEIGHT_INCREMENT_AMOUNT;
}

void increment_angle(void)
{
    helicopter->target_yaw += YAW_INCREMENT_AMOUNT;
}

void decrement_angle(void)
{
    helicopter->target_yaw -= YAW_INCREMENT_AMOUNT;
}

void ref_found(void) {
    yawRefSignalIntHandler();
    set_yaw_ref_callback(yawRefSignalIntHandler);\
    set_helicopter_state(FLYING);
}


void update_controllers(void)
{

    helicopter->current_yaw = get_current_yaw();
    helicopter->current_altitude = get_height_percentage();

    int16_t error_altitude;
    int16_t error_yaw;
    uint16_t control_main;
    uint16_t control_tail;

    switch(helicopter->state)
    {
        case LANDED:
            set_main_PWM(250,0);
            set_tail_PWM(250, 0);
            setReferenceAngleSetState(0);
            break;
    
        case FIND_REF:
            set_main_PWM(250, MIN_PWM);
            set_tail_PWM(250, MIN_PWM);
            break;

        case FLYING:       
            error_altitude = helicopter->target_altitude - helicopter->current_altitude;
            error_yaw = helicopter->target_yaw - helicopter->current_yaw;

            control_main = update_PID(&main_controller, error_altitude, 200);
            control_tail = update_PID(&tail_controller, error_yaw, 200);

            set_main_PWM(250, control_main);
            set_tail_PWM(250, control_tail);
            break;

        case LANDING:
            helicopter->target_yaw = 0;

            error_altitude = helicopter->target_altitude - helicopter->current_altitude;
            error_yaw = helicopter->target_yaw - helicopter->current_yaw;

            control_main = update_PID(&main_controller, error_altitude, 200);
            control_tail = update_PID(&tail_controller, error_yaw, 200);

            set_main_PWM(250, control_main);
            set_tail_PWM(250, control_tail);

            if (abs(error_yaw) < 10) {
                helicopter->target_altitude = 10;
            }

            if (helicopter->target_altitude == 10 && abs(error_altitude) < 5) {
                set_main_PWM(250, 0);
                set_tail_PWM(250, 0);
                set_helicopter_state(LANDED);
            }

            break;
    }

    set_main_PWM(250,control_main);
    set_tail_PWM(250, control_tail);
}

