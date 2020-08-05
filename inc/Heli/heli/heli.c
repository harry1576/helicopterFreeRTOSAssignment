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
#include "rotors.h"
#include "stickman_image.h"
#include "helicopter_image.h"
#include "heli_display.h"
#include "OrbitOLEDInterface.h"

#include "driverlib/interrupt.h"

void heli_init(void) {
    if (HELI_LOG_ENABLE) {
        log_init();   
    }

    init_yaw();
    init_height();
    init_pwm();
    OLEDInitialise();

    init_animation();

    int rc = put_image_to_oled(helicopter_image_frame_0, helicopter_image_width, helicopter_image_height, 0, 0);
    // int8_t rc = begin_animation(stickman_image_frames, stickman_image_frame_count, stickman_image_width, stickman_image_height, 0, 0);
    char rc_char[5];
    usprintf(rc_char, "%d", rc);
    info_log(rc_char);

    if (rc != 0) {
        while (1)
        {
            
        }
        
    }

    IntMasterEnable();
}
