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
#include "rotors.h"
#include "stickman_image.h"
#include "helicopter_image.h"
#include "heli_display.h"
#include "OrbitOLEDInterface.h"
#include "menu.h"
#include "input.h"

#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/interrupt.h"

uint8_t currentValue = 0;

void toggleLED(void)
{  
    int rc = put_image_to_oled(helicopter_image_frame_0, helicopter_image_width, helicopter_image_height, 0, 0);
       if (rc != 0) {
        while (1)
        {
            
        }
        
    }
}

void useless(void) {
    clear_oled();
}

void heli_init(void) {
    if (HELI_LOG_ENABLE) {
        log_init();   
    }
    initButtons();
    init_yaw();
    init_height();
    init_pwm();
    init_controllers();
    OLEDInitialise();


    menu_t* main_menu = create_menu("Main Menu");

    add_menu_item("Heli", main_menu, useless);
    menu_t* flight_menu = add_submenu("Flight", main_menu);
    add_menu_item("test", flight_menu, toggleLED);
    add_menu_item("foo", flight_menu, useless);
    add_menu_item("bar", flight_menu, useless);

    set_current_menu(main_menu);



    // init_animation();
    // int8_t rc = begin_animation(stickman_image_frames, stickman_image_frame_count, stickman_image_width, stickman_image_height, 0, 0);

    IntMasterEnable();
    
}
