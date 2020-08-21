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
#include <driverlib/pin_map.h>
#include <stdio.h>
#include "heli.h"
#include "yaw.h"

int32_t volatile yawSlotCount = 0;
static int currentYawState; // The current state of the yaw sensors
static int previousYawState; // The previous state of the yaw sensors

void initYawReferenceSignal(void);
void init_yaw(void);
void yawRefSignalIntHandler(void);
void increment_yaw(void);
void quadratureDecode(void);
int get_current_yaw(void);
void reset_yaw(void);


void initYawReferenceSignal(void) {
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);

    GPIOPinTypeGPIOInput(GPIO_PORTC_BASE, GPIO_PIN_4);
}

void set_yaw_ref_callback(void (*callback)()) {
    GPIOIntRegister(GPIO_PORTC_BASE, callback);
}

void init_yaw(void) {
    initYawReferenceSignal();
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);

    GPIOPinTypeGPIOInput(GPIO_PORTB_BASE, CHANNEL_A | CHANNEL_B);

    GPIOIntEnable(GPIO_PORTB_BASE, GPIO_INT_PIN_0 | GPIO_INT_PIN_1);

    GPIOIntTypeSet(GPIO_PORTB_BASE, CHANNEL_A | CHANNEL_B, GPIO_BOTH_EDGES);

    GPIOIntRegister(GPIO_PORTB_BASE, increment_yaw);

    GPIOIntEnable(GPIO_PORTC_BASE, GPIO_INT_PIN_4);

    GPIOIntTypeSet(GPIO_PORTC_BASE, GPIO_PIN_4, GPIO_FALLING_EDGE);

    currentYawState = GPIOPinRead(GPIO_PORTB_BASE, CHANNEL_A | CHANNEL_B);
}

void increment_yaw(void) {
    GPIOIntClear(GPIO_PORTB_BASE, GPIO_INT_PIN_0 | GPIO_INT_PIN_1); // Clear the interrupt

    previousYawState = currentYawState; // Save the previous state

    currentYawState = (int) GPIOPinRead(GPIO_PORTB_BASE, CHANNEL_A | CHANNEL_B);

    // Determine the direction of rotation. Increment or decrement yawSlotCount appropriately.
    quadratureDecode();
}


void quadratureDecode(void) {
    // FSM implementation for quadrature decoding.
    // States are changed by the interrupt handler.
    if (currentYawState == B_HIGH_A_LOW) {
        if (previousYawState == B_LOW_A_LOW) {
            yawSlotCount = yawSlotCount + YAW_INCREMENT; // Clockwise rotation
        } else {
            yawSlotCount = yawSlotCount - YAW_DECREMENT; // Anticlockwise rotation
        }
    } else if (currentYawState == B_HIGH_A_HIGH) {
        if (previousYawState == B_HIGH_A_LOW) {
            yawSlotCount = yawSlotCount + YAW_INCREMENT;
        } else {
            yawSlotCount = yawSlotCount - YAW_DECREMENT;
        }
    } else if (currentYawState == B_LOW_A_HIGH) {
        if (previousYawState == B_HIGH_A_HIGH) {
            yawSlotCount = yawSlotCount + YAW_INCREMENT;
        } else {
            yawSlotCount = yawSlotCount - YAW_DECREMENT;
        }
    } else {
        if (previousYawState == B_LOW_A_HIGH) {
            yawSlotCount = yawSlotCount + YAW_INCREMENT;
        } else {
            yawSlotCount = yawSlotCount - YAW_DECREMENT;
        }
    }
}


int get_current_yaw(void) {
    return yawSlotCount;
}

void set_current_yaw(int yaw) {
    yawSlotCount = yaw;
}

void reset_yaw(void) {
    yawSlotCount = 0;
}