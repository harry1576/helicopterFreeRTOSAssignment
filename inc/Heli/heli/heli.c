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
#include "tail_rotor.h"
#include "main_rotor.h"

#include "driverlib/interrupt.h"

void heli_init(void) {
    if (HELI_LOG_ENABLE) {
        log_init();   
    }

    init_yaw();
    init_height();
    init_main_rotor();
    init_tail_rotor();
    set_main_PWM(200,50);
    IntMasterEnable();
    
}
