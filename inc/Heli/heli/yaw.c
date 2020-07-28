/**
 * yaw.c - Yaw access and control for heli project
 *
 * Authors: Jos Craw, Josh Hulbert, Harry Dobbs
 * Last Modified: 28.07.2020
 */

#include <stdint.h>
#include <stdbool.h>
#include <inc/hw_memmap.h>
#include <inc/hw_types.h>
#include <inc/hw_ints.h>
#include <driverlib/gpio.h>
#include <driverlib/sysctl.h>
#include <driverlib/qei.h>
#include <driverlib/pin_map.h>
#include <stdio.h>

#include "heli.h"

#define QEI_PERIPH  SYSCTL_PERIPH_QEI0
#define QEI_BASE    QEI0_BASE

void init_yaw(void);
void set_yaw(int rotation);
void increment_yaw(void);
int get_current_yaw(void);
void reset_yaw(void);

void init_yaw(void) {
    SysCtlPeripheralEnable(QEI_PERIPH);

    while(!SysCtlPeripheralReady(QEI_PERIPH)) {
    }

    QEIConfigure(QEI_BASE, (QEI_CONFIG_CAPTURE_A_B | QEI_CONFIG_RESET_IDX |
                QEI_CONFIG_QUADRATURE | QEI_CONFIG_NO_SWAP),
                (YAW_SPOKE_COUNT * 4 - 1));

    #ifdef YAW_VELOCITY_ENABLE
    if (YAW_VELOCITY_ENABLE == 1) {
        QEIVelocityConfigure(QEI_BASE, QEI_VELDIV_1, YAW_VELOCITY_PERIOD);
    }
    #endif

    QEIEnable(QEI0_BASE);
}

void set_yaw(int rotation) {
    return;
}

void increment_yaw(void) {
    return;
}

int get_current_yaw(void) {
    return QEIPositionGet(QEI_BASE);
}

int get_yaw_velocity(void) {
    return 1;
}

void reset_yaw(void) {
    return;
}
