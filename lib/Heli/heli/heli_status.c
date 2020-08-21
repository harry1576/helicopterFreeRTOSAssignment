/*
 * heli_status.c - Fucntions to support menu labels
 * 
 * Author: Jos Craw 2020 
 */

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <utils/ustdlib.h>

#include "rotors.h"
#include "height.h"
#include "yaw.h"
#include "heli.h"

void get_height_percent(char* label) {
    usprintf(label, "%d\0", get_current_height());
}

void get_yaw_slot(char* label) {
    usprintf(label, "%d\0", get_current_yaw());
}

void get_main_pwm_output(char* label) {
    usprintf(label, "%d\0", get_main_pwm());
}

void get_tail_pwm_output(char* label) {
    usprintf(label, "%d\0", get_tail_pwm());
}