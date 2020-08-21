/**
 * heli.c - Heli initialiser
 *
 * Authors: Jos Craw, Josh Hulbert, Harry Dobbs
 * 
 * Last Modified : 21.08.2020
 */

#include <stdint.h>
#include <stdbool.h>
#include <utils/ustdlib.h>

#include <driverlib/pin_map.h>
#include <driverlib/sysctl.h>

#include "logging.h"
#include "yaw.h"
#include "height.h"
#include "heli.h"
#include "rotors.h"
#include "plot.h"
#include "OrbitOLEDInterface.h"


void init_clocks(void) {
    SysCtlClockSet (SYSCTL_SYSDIV_2_5 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN |
                    SYSCTL_XTAL_16MHZ);
}

void heli_init(void) {
    init_clocks();

    log_init();

    #if ENABLE_XSS == 1
        // Delay to ensure the webpage is receiving serial
        SysCtlDelay(SysCtlClockGet()/6);
        // Send script tag for the JavaScript loader
        uart_send(HELI_XSS_LOADER);

        /*
         * Delay to ensure that the UART stream is not cutoff by the webpage as
         * the UART buffer is only cleared every half second.
         */
        SysCtlDelay(SysCtlClockGet()/6);
    #endif

    initButtons();
    init_yaw();
    init_height();
    init_pwm();
    OLEDInitialise();

    #if ENABLE_PLOTTING == 1
    init_plot();
    #endif
    
    IntMasterEnable();
    
}
