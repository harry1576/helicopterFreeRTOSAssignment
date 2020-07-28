/**
 * heli.c - Heli initialiser
 *
 * Authors: Jos Craw, Josh Hulbert, Harry Dobbs
 */

#include "logging.h"
#include "yaw.h"

void heli_init(void) {
    #ifdef HELI_LOG_ENABLE
    if (HELI_UART_ENABLE == 1) {
        log_init();   
    }
    #endif

    init_yaw();


}
