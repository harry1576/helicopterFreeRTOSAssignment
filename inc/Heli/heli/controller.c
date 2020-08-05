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
    init_PID(&pid_main, 0, 0, 0);
    init_PID(&pid_tail, 0, 0, 0);

    //TODO: CHANGE TO ADC VALUE
    helicopter->ground_reference = 0;
    helicopter->current_altitude = 0;
    helicopter -> target_altitude = 0;
    helicopter->state = LANDED;
}



void update_controllers()
{
    uint16_t control_main = 0;
    uint16_t control_tail = 0;
    // NEED TO GET ALTITUDE
    // AND YAW
    // CHANGE IN TIME TOO
    
    switch(helicopter->state)
    {
        case LANDED:
            control_main = 0;
            control_tail = 0;
            break;
    
        case SWEEP:
            break;

        case FLYING:            
            break;

        case LANDING:
            break;
    }
}

