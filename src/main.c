// ************************************************************
// week2_blink
// Sample code for Week 2 ENCE361 Lab
// Author:  Phil Bones
// Last edited:   3.2.2018
// Based on Texas example code, and additions by Steve Weddell
//
// Purpose: This program will cause the LED connected to Pin 3
// of Port F to blink.
// ************************************************************
//

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

// TivaWare Library Includes:
#include "inc/hw_memmap.h"        // defines GPIO_PORTF_BASE
#include "inc/tm4c123gh6pm.h"     // defines interrupt vectors
                                  //   and register addresses
#include "driverlib/gpio.h"       // defines for GPIO peripheral
#include "driverlib/sysctl.h"     // system control functions

#include "FreeRTOS.h"
#include "task.h"

#define RED_LED   GPIO_PIN_1
#define BLUE_LED  GPIO_PIN_2
#define GREEN_LED GPIO_PIN_3

void BlinkLED(void *);

int main(void) {
    uint32_t clock_rate;
	// Set up the system clock (refer to pp.220 of the TM4C123 datasheet for an overview). 
	// Many options exist here but basically the 16MHz crystal oscillator signal is
	// boosted to 400Mz via a phase-locked loop (PLL), divided by 2 and then again by 10
    // (via the SYSCTL_SYSDIV_10 setting) to make the system clock rate 20 MHz.
	SysCtlClockSet(SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ | SYSCTL_SYSDIV_10);

	SysCtlDelay(100);  // Allow time for the oscillator to settle down.
	// SysCtlDelay() is an API function which executes a 3-instruction loop the number of
	//   times specified by the argument).
	
	clock_rate = SysCtlClockGet();  // Get the clock rate in pulses/s.
	 
    // Enable GPIO Port F
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);  
	
	// Set up the specific port pin as medium strength current & pull-down config.
	// Refer to TivaWare peripheral lib user manual for set up for configuration options
	GPIOPadConfigSet(GPIO_PORTF_BASE, GREEN_LED, GPIO_STRENGTH_4MA, GPIO_PIN_TYPE_STD_WPD);
	
	// Set data direction register as output
	GPIODirModeSet(GPIO_PORTF_BASE, GREEN_LED, GPIO_DIR_MODE_OUT);

	// Write a zero to the output pin 3 on port F
	GPIOPinWrite(GPIO_PORTF_BASE, GREEN_LED, 0x00);

	// Enter a gadfly loop (kernel) to make the LED blink
        if (pdTRUE != xTaskCreate(BlinkLED, "Blinker", 32, (void *)1, 4, NULL)) {
            while (1) ; // error creating task, out of memory?    
        }
        vTaskStartScheduler();
}
void BlinkLED(void *pvParameters) {    unsigned int whichLed = (unsigned int)pvParameters;
    const uint8_t whichBit = 1 << whichLed; // TivaWare GPIO calls require the pin# as a binary bitmask, not a simple number.    
    // Alternately, we could have passed the bitmask into pvParameters instead of a simple number.    
    uint8_t currentValue = 0;
    while (1) {
        currentValue ^= whichBit; // XOR keeps flipping the bit on / off alternately each time this runs.
        GPIOPinWrite(GPIO_PORTF_BASE, whichBit, currentValue);
        vTaskDelay(1000);  // Suspend this task (so others may run) for 125ms or as close as we can get with the current RTOS tick setting.    }
    }
}
