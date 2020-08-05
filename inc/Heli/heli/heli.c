/**
 * heli.c - Heli initialiser
 *
 * Authors: Jos Craw, Josh Hulbert, Harry Dobbs
 */

#include <stdint.h>
#include <stdbool.h>
#include <utils/ustdlib.h>

#include "logging.h"
#include "yaw.h"
#include "height.h"
#include "heli.h"
<<<<<<< HEAD
#include "rotors.h"
#include "stickman_image.h"
#include "heli_display.h"
#include "OrbitOLEDInterface.h"
=======
#include "tail_rotor.h"
#include "main_rotor.h"
>>>>>>> d4877774a300b77a032a6c5d75ea3fb50238c184

#include "driverlib/interrupt.h"

void heli_init(void) {
    if (HELI_LOG_ENABLE) {
        log_init();   
    }

    init_yaw();
    init_height();
<<<<<<< HEAD
    init_pwm();
    OLEDInitialise();

    init_animation();

    int8_t rc = begin_animation(stickman_image_frames, stickman_image_frame_count, stickman_image_width, stickman_image_height, 0, 0);
    char rc_char[5];
    usprintf(rc_char, "%d", rc);
    info_log(rc_char);

    if (rc != 0) {
        while (1)
        {
            
        }
        
    }

=======
    init_main_rotor();
    init_tail_rotor();
    set_main_PWM(200,50);
>>>>>>> d4877774a300b77a032a6c5d75ea3fb50238c184
    IntMasterEnable();
    
}
