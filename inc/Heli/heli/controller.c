/*
 * controller.c 
 * Controller used to drive the logic to ensure correct PWM.
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
#include "controller.h"
#include "rotors.h"
#include "height.h"
#include "input.h"
#include "yaw.h"
#include "logging.h"

static controller_t pid_main;
static controller_t pid_tail;
static heli_t* helicopter;



//*****************************************************************************
//
// Initialisation for Controllers (One for main rotor and one for tail rotor).
//
//*****************************************************************************
void init_controllers()
{
    // Initialise PID controllers
    init_PID(&pid_main, 1, 1, 0); // Kp , Ki , Kd
    init_PID(&pid_tail, 1, 1, 0);

    //TODO: CHANGE TO ADC VALUE
    helicopter->ground_reference = get_height();
    helicopter->current_altitude = 0;

    set_max_height(helicopter->ground_reference - 1240); // (4095*1)/3.3 -> Maximum height as we know if 0.8V less than ground
    //helicopter.target_altitude = 0;
    //helicopter.state = LANDED;
}


void set_helicopter_state(int8_t state)
{
    helicopter->state = state;
}


void update_controllers()
{
    uint16_t control_main = 0;
    uint16_t control_tail = 0;
    // NEED TO GET ALTITUDE
    // AND YAW
    // CHANGE IN TIME TOO
    pollButtons();

    switch(helicopter->state)
    {
        case LANDED:
            control_main = 0;
            control_tail = 0;
            set_main_PWM(250,control_main);
            set_tail_PWM(250, control_tail);
            break;
    
        case SWEEP:
<<<<<<< HEAD
=======

            target_altitude = 10;
            current_altitude = get_height_percentage(); // Height as Percentage

            error_altitude = target_altitude - current_altitude;
            update_PID(&pid_main, error_altitude, 200);
            control_main = get_PID_output(&pid_main);
            set_main_PWM(250,control_main);
            error_log("ye");
            
            if(getReferenceAngleSetState())
            {
                target_yaw = 0;
                current_yaw = get_current_yaw();
                error_yaw = target_yaw - current_yaw;
                update_PID(&pid_tail, error_yaw, 200);
                control_tail = get_PID_output(&pid_tail);
                set_tail_PWM(250, control_tail);
            }
            else
            {
                target_yaw = 448; // -> Equivalent to 360 degrees
                current_yaw = get_current_yaw();
                error_yaw = target_yaw - current_yaw;
                update_PID(&pid_tail, error_yaw, 200);
                control_tail = get_PID_output(&pid_tail);
                set_tail_PWM(250, control_tail);
            }

            if(getReferenceAngleSetState() && current_altitude == 10 && current_yaw < 5 && current_yaw > -5)
            {
                helicopter->state = FLYING;
            }

>>>>>>> 33ed24c... Fixed some issues with controller
            break;

        case FLYING:       
                 
            break;

        case LANDING:
            break;
    }
}

