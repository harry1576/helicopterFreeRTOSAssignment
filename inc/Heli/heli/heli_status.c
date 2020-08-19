#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <utils/ustdlib.h>

#include "rotors.h"
#include "heli.h"

char* get_height_percent(void) {
    char* height = (char*)calloc('\0', sizeof(char)*MAX_LABEL_LENGTH);

    return height;
}

char* get_yaw_degrees(void) {
    char* yaw = (char*)calloc(MAX_LABEL_LENGTH, sizeof(char));
    

    return yaw;
}

char* get_main_pwm_output(void) {
    char* main_pwm = (char*)calloc('\0', sizeof(char)*MAX_LABEL_LENGTH);
    usprintf(main_pwm, "%d", get_main_pwm());
    return main_pwm;
}

char* get_tail_pwm_output(void) {
    char* tail_pwm = (char*)calloc('\0', sizeof(char)*MAX_LABEL_LENGTH);
    usprintf(tail_pwm, "%d", get_tail_pwm());
    return tail_pwm;
}