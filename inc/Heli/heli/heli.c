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
#include "controller.h"
#include "heli.h"
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
=======
#include "rotors.h"
>>>>>>> 3b6d82e... Added a controller and PID file
#include "stickman_image.h"
#include "helicopter_image.h"
#include "heli_display.h"
#include "OrbitOLEDInterface.h"
<<<<<<< HEAD
=======
#include "rotors.h"
>>>>>>> 14f49a6... Added PWM module
=======
#include "tail_rotor.h"
#include "main_rotor.h"
>>>>>>> d487777... working setup
=======
>>>>>>> 3b6d82e... Added a controller and PID file

#include "driverlib/interrupt.h"




void heli_init(void) {
    if (HELI_LOG_ENABLE) {
        log_init();   
    }

    init_yaw();
    init_height();
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
=======
    init_pwm();
    init_controllers();
>>>>>>> 3b6d82e... Added a controller and PID file
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
=======
    init_pwm();
>>>>>>> 14f49a6... Added PWM module

<<<<<<< HEAD
=======
    init_main_rotor();
    init_tail_rotor();
    set_main_PWM(200,50);
>>>>>>> d487777... working setup
=======
>>>>>>> 3b6d82e... Added a controller and PID file
    IntMasterEnable();
    
}
