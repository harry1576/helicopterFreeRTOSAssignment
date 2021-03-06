/*
 * controller.c 
 * Controller used to drive the logic to ensure correct PWM.
 * Authors: Jos Craw, Josh Hulbert, Harry Dobbs
 */

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

#include <heli/heli.h>
#include <heli/pid.h>
#include <heli/rotors.h>
#include <heli/height.h>
#include <heli/input.h>
#include <heli/yaw.h>
#include <heli/logging.h>

#include <utils/ustdlib.h>

#include "controller.h"
#include "adc_buffer.h"

extern adc_buffer_t* g_adc_buffer;

static controller_t* main_controller;
static controller_t* tail_controller;
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
    main_controller = init_PID(MAIN_KP, MAIN_KI, MAIN_KD, MAIN_MAX_KP, MAIN_MAX_KI, MAIN_MAX_KD);

    tail_controller = init_PID(TAIL_KP, TAIL_KI, TAIL_KD, TAIL_MAX_KP, TAIL_MAX_KI, TAIL_MAX_KD);

    //TODO: CHANGE TO ADC VALUE
    helicopter->ground_reference = 0;
    helicopter->current_altitude = 0;
    
    set_helicopter_state(LANDED);

    helicopter->current_yaw = 0;
    helicopter->target_yaw = 0;
    
    helicopter->target_altitude = 0;
}

void set_heli_ground_ref(uint32_t value) {
    helicopter->ground_reference = (uint16_t)value;
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
    if(helicopter->target_altitude + HEIGHT_INCREMENT_AMOUNT <= MAX_HEIGHT)
    {   
        helicopter->target_altitude += HEIGHT_INCREMENT_AMOUNT;
    }
}

void decrement_height(void)
{
    if(helicopter->target_altitude - HEIGHT_INCREMENT_AMOUNT >= MIN_HEIGHT)
    {
        helicopter->target_altitude -= HEIGHT_INCREMENT_AMOUNT;
    }
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
    set_yaw_ref_callback(yawRefSignalIntHandler);
    reset_yaw();
    helicopter->target_yaw = 0;
    set_helicopter_state(FLYING);
}

void set_yaw_target(int16_t target) {
    helicopter->target_yaw = target;
}

void set_height_target(int16_t target) {
    helicopter->target_altitude = target;
}

void update_controllers(void)
{
    int32_t current_yaw = get_current_yaw();
    int16_t height = adc_buffer_get_average(g_adc_buffer);
    if (height == -1) {
        return;
    }

    float current_altitude = ((helicopter->ground_reference - height))/1241.0;
    int16_t percent_altitude = current_altitude * 100;

    static int16_t error_altitude;
    static int16_t error_yaw;
    static uint16_t control_main;
    static uint16_t control_tail;

    switch(helicopter->state)
    {
        case LANDED:
            helicopter->ground_reference = adc_buffer_get_average(g_adc_buffer);
            set_main_PWM(PWM_FREQUENCY, 0);
            set_tail_PWM(PWM_FREQUENCY, 0);

            set_yaw_target(0);
            set_height_target(HOVER_HEIGHT);

            updateButtons();

            if (checkButton(SWITCH) == PUSHED) {
                set_helicopter_state(FIND_REF);
            }
            break;
    
        case FIND_REF:

            helicopter->target_altitude = 10;
            helicopter->target_yaw = 448;

            error_altitude = helicopter->target_altitude - percent_altitude;
            error_yaw = helicopter->target_yaw - current_yaw;

            control_main = update_PID(main_controller, error_altitude, 1/CONTROLLER_UPDATE);
            control_tail = update_PID(tail_controller, error_yaw, 1/CONTROLLER_UPDATE);

            set_main_PWM(PWM_FREQUENCY, control_main);
            set_tail_PWM(PWM_FREQUENCY, control_tail);
            
            break;

        case FLYING:       
            error_altitude = helicopter->target_altitude - percent_altitude;
            error_yaw = helicopter->target_yaw - current_yaw;

            control_main = update_PID(main_controller, error_altitude, 1/CONTROLLER_UPDATE);
            control_tail = update_PID(tail_controller, error_yaw, 1/CONTROLLER_UPDATE);

            set_main_PWM(PWM_FREQUENCY, control_main);
            set_tail_PWM(PWM_FREQUENCY, control_tail);
        
            if (checkButton(SWITCH) == RELEASED) {
                helicopter->target_altitude = 10;
                set_helicopter_state(LANDING);
            }
            break;

        case LANDING:
            
            
            if (abs(error_yaw) < 5 && adc_buffer_get_range(g_adc_buffer) < 10 && helicopter->target_altitude == 10){
                helicopter->target_altitude = 5;
            }
            else if (abs(error_yaw) < 5 && adc_buffer_get_range(g_adc_buffer) < 10 && helicopter->target_altitude == 5){
                helicopter->target_altitude = 0;
                set_helicopter_state(LANDED);           

            }
            else if(current_altitude <= 0 && helicopter->target_altitude == 0){
                set_helicopter_state(LANDED);           
            }

            current_yaw = current_yaw > 0 ? current_yaw % YAW_SPOKE_COUNT : (current_yaw % YAW_SPOKE_COUNT) - YAW_SPOKE_COUNT;
            helicopter->target_yaw = 0;

            error_altitude = helicopter->target_altitude - percent_altitude;
            error_yaw = helicopter->target_yaw - current_yaw;

            control_main = update_PID(main_controller, error_altitude, 1/CONTROLLER_UPDATE);
            control_tail = update_PID(tail_controller, error_yaw, 1/CONTROLLER_UPDATE);

            set_main_PWM(PWM_FREQUENCY, (uint32_t)control_main);
            set_tail_PWM(PWM_FREQUENCY, (uint32_t)control_tail);
            

            break;
    }
}