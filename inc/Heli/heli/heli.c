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
#include "stickman_image.h"
#include "heli_display.h"
#include "OrbitOLEDInterface.h"
=======
#include "rotors.h"
>>>>>>> 14f49a6... Added PWM module

#include "driverlib/interrupt.h"

void heli_init(void) {
    if (HELI_LOG_ENABLE) {
        log_init();   
    }

    init_yaw();
    init_height();
<<<<<<< HEAD
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
    init_pwm();
>>>>>>> 14f49a6... Added PWM module

    IntMasterEnable();
}
