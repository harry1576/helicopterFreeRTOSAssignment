/*
 * controller.c 
 * Controller used to drive the logic to ensure correct PWM.
 * Authors: Jos Craw, Josh Hulbert, Harry Dobbs
 */

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

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
#include "controller.h"
#include "rotors.h"
#include "height.h"
#include "input.h"
#include "yaw.h"
#include "logging.h"

static controller_t pid_main;
static controller_t pid_tail;
static heli_t* helicopter;

uint16_t control_main = 0;
uint16_t control_tail = 0;
    
int16_t error_altitude = 0;
int32_t error_yaw = 0;


//*****************************************************************************
//
// Initialisation for Controllers (One for main rotor and one for tail rotor).
//
//*****************************************************************************
void init_controllers()
{
    helicopter = (heli_t*)malloc(sizeof(heli_t));
    // Initialise PID controllers
    init_PID(&pid_main, 1, 1, 0); // Kp , Ki , Kd
    init_PID(&pid_tail, 1, 1, 0);

    //TODO: CHANGE TO ADC VALUE
    helicopter->ground_reference = get_height();
    helicopter->current_altitude = 0;
    helicopter->state = LANDED;

    helicopter->current_yaw = 0;
    helicopter->target_yaw = 0;

    set_min_height(helicopter->ground_reference); // (4095*1)/3.3 -> Maximum height as we know if 0.8V less than ground
    set_max_height(helicopter->ground_reference - 1240); // (4095*1)/3.3 -> Maximum height as we know if 0.8V less than ground
    
    helicopter->target_altitude = 0;

    //helicopter.state = LANDED;
}


void set_helicopter_state(int8_t state)
{
    helicopter->state = state;
}

int8_t get_helicopter_state(void)
{
    return helicopter->state;
}

void increment_height(void)
{
    helicopter->target_altitude += 10;
}

void decrement_height(void)
{
    helicopter->target_altitude -= 10;
}

void increment_angle(void)
{
    helicopter->target_yaw += 19;
}

void decrement_angle(void)
{
    helicopter->target_yaw -= 19;
}


void update_controllers(void)
{

    helicopter->current_yaw = get_current_yaw();
    helicopter->current_altitude = get_height_percentage(); 

    // NEED TO GET ALTITUDE
    // AND YAW
    // CHANGE IN TIME TOO
    pollButtons();
    error_log("ye");

    switch(helicopter->state)
    {
        case LANDED:
            debug_log("LANDED");
            set_main_PWM(250,0);
            set_tail_PWM(250, 0);
            setReferenceAngleSetState(0);
            break;
    
        case SWEEP:
            debug_log("SWEEP");

            helicopter->target_altitude = 10;

            error_altitude = helicopter->target_altitude - helicopter->current_altitude;
            control_main = update_PID(&pid_main, error_altitude, 200);
            
            if(getReferenceAngleSetState())
            {
                helicopter->target_yaw = 0;
                error_yaw = helicopter->target_yaw - helicopter->current_yaw;
                control_tail = update_PID(&pid_tail, error_yaw, 200);
            }
            else
            {
                helicopter->target_yaw = 448; // -> Equivalent to 360 degrees
                error_yaw = helicopter->target_yaw - helicopter->current_yaw;
                control_tail = update_PID(&pid_tail, error_yaw, 200);
            }

            if(getReferenceAngleSetState() &&  helicopter->current_altitude == 10 && helicopter->current_yaw < 6 && helicopter->current_yaw > -6)
            {
                helicopter->state = FLYING;
            }
            break;

        case FLYING:       
            debug_log("FLYING");

            error_altitude = helicopter->target_altitude - helicopter->current_altitude;
            control_main = update_PID(&pid_main, error_altitude, 200);

            error_yaw = helicopter->target_yaw - helicopter->current_yaw;
            control_tail = update_PID(&pid_tail, error_yaw, 200);
            break;

        case LANDING:

            debug_log("LANDING");

            helicopter->target_altitude = 10;
            helicopter->target_yaw = 0;

            if(helicopter->current_yaw < 10 && helicopter->current_yaw > -10 &&  helicopter->current_altitude == 10){
                helicopter->target_altitude = 5;
            }
            else if(helicopter->current_yaw < 4 && helicopter->current_yaw > 4 && helicopter->current_altitude < 10)
            {
                helicopter->target_altitude = 0;
            }

            error_altitude = helicopter->target_altitude - helicopter->current_altitude;
            control_main = update_PID(&pid_main, error_altitude, 200);

            error_yaw = helicopter->target_yaw - helicopter->current_yaw;
            control_tail = update_PID(&pid_tail, error_yaw, 200);

            if(helicopter->current_altitude == 0)
            {
                set_helicopter_state(LANDED);
            }

            break;
    }

    set_main_PWM(250,control_main);
    set_tail_PWM(250, control_tail);
}

