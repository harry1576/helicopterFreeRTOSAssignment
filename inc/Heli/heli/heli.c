/**
 * heli.c - Heli initialiser
 *
 * Authors: Jos Craw, Josh Hulbert, Harry Dobbs
 */

#include <stdint.h>
#include <stdbool.h>

#include "logging.h"
#include "yaw.h"
#include "height.h"
#include "heli.h"
#include "arrow.h"
#include "heli_display.h"
#include "OrbitOLEDInterface.h"

#include "driverlib/interrupt.h"

void heli_init(void) {
    if (HELI_LOG_ENABLE) {
        log_init();   
    }

    init_yaw();
    init_height();
    OLEDInitialise();

    int rc = put_image_to_oled(arrow, arrow_width, arrow_height, 2, 0);
    if (rc != 0) {
        while (1)
        {
            
        }
        
    }

    IntMasterEnable();
}
