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
static int currentYawState;          // The current state of the yaw sensors
static int previousYawState;         // The previous state of the yaw sensors
int32_t reference_point_crossing = 0;

void initYawReferenceSignal(void);
void init_yaw(void);
void yawRefSignalIntHandler(void);
void increment_yaw(void);
void quadratureDecode(void);
int get_current_yaw(void);
void reset_yaw(void);

//*****************************************************************************
//
// Initialisation for the independent yaw reference.
// A low value on PC4 indicates the reference is found.
//
//*****************************************************************************
void initYawReferenceSignal(void) {
    // Enable Port C
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);

    // Set pin 4 as an input
    GPIOPinTypeGPIOInput(GPIO_PORTC_BASE, GPIO_PIN_4);
}

void set_yaw_ref_callback(void (*callback)()) {
    // Enable interrupts on PC4
    GPIOIntEnable(GPIO_PORTC_BASE, GPIO_INT_PIN_4);

    // Set interrupts on PC4 as a low level interrupt
    GPIOIntTypeSet(GPIO_PORTC_BASE, GPIO_PIN_4, GPIO_FALLING_EDGE);

    // Register the interrupt handler
    GPIOIntRegister(GPIO_PORTC_BASE, callback);
}

void init_yaw(void) {
    initYawReferenceSignal();
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB); // Enable Port B

    // Set PB0 and PB1 as inputs
    GPIOPinTypeGPIOInput(GPIO_PORTB_BASE, CHANNEL_A | CHANNEL_B);

    // Enable interrupts on PB0 and PB1
    GPIOIntEnable(GPIO_PORTB_BASE, GPIO_INT_PIN_0 | GPIO_INT_PIN_1);

    // Set interrupts on PB0 and PB1 as pin change interrupts
    GPIOIntTypeSet(GPIO_PORTB_BASE, CHANNEL_A | CHANNEL_B, GPIO_BOTH_EDGES);

    // Register the interrupt handler
    GPIOIntRegister(GPIO_PORTB_BASE, increment_yaw);

    // Read the values on PB0 and PB1
    currentYawState = GPIOPinRead(GPIO_PORTB_BASE, CHANNEL_A | CHANNEL_B);
}

//*****************************************************************************
//
// The interrupt handler for the independent yaw reference signal.
// The interrupt is triggered by falling edges on PC4.
//
//*****************************************************************************
void yawRefSignalIntHandler(void) {
    GPIOIntClear(GPIO_PORTC_BASE, GPIO_INT_PIN_4); // Clear the interrupt
    reference_point_crossing = yawSlotCount;
}

void increment_yaw(void) {
    GPIOIntClear(GPIO_PORTB_BASE, GPIO_INT_PIN_0 | GPIO_INT_PIN_1); // Clear the interrupt

    previousYawState = currentYawState; // Save the previous state

    // Read the values on PB0 and PB1
    // The yaw signals are on pins 0 and 1. GPIOPinRead returns a bit packed
    // byte where the zeroth bit is the state of pin 0, the first bit is the state 
    // of pin 1 on the port, etc. Bits two to seven are not read by the quadrature decoder,
    // and hence their bit in the returned byte is zero. So PB0 low and PB1 low returns 0x00
    // when read, PB0 high and PB1 low returns 0x01 when read etc. The returned value will 
    // therefore match the desired state as given in the yawStates enum (yaw.h)
    currentYawState = (int) GPIOPinRead(GPIO_PORTB_BASE, CHANNEL_A | CHANNEL_B);

    // Determine the direction of rotation. Increment or decrement yawSlotCount appropriately.
    quadratureDecode();
}

//*****************************************************************************
//
// Determines the rotation direction of the disk and increments or decrements
// the slot count appropriately. Sets the slot count to zero if the maximum
// number is exceeded (i.e. 360 degrees rotation performed).
// This function is called upon rising and falling edges on PB1, PB2.
//
//*****************************************************************************
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

void reset_yaw(void) {
    yawSlotCount = 0;
}