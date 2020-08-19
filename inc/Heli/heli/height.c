/**
 * heli.c - Heli Height interface
 *
 * Authors: Jos Craw, Josh Hulbert, Harry Dobbs
 */

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/adc.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"

#include "height.h"
#include "heli.h"

#define ADC_SEQUENCE_THREE 3
#define ADC_CHANNEL_ZERO 0

void init_height(void);
void sample_height(void);
void set_adc_callback(void (*callback)());

void set_max_height(uint16_t value);
void set_min_height(uint16_t value);
int8_t get_height_percentage(void);
void adc_run_callback(void);

void (*adc_callback)(uint32_t); // The callback function for the ADC

volatile uint16_t max_height;
volatile uint16_t min_height;
volatile uint16_t current_height;

void init_height(void) {
    SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_ADC0)) ;
    
    ADCSequenceConfigure(ADC0_BASE, ADC_SEQUENCE_THREE, ADC_TRIGGER_PROCESSOR, ADC_CHANNEL_ZERO);
  
    ADCSequenceStepConfigure(ADC0_BASE, ADC_SEQUENCE_THREE, ADC_CHANNEL_ZERO, ADC_CTL_CH9 | ADC_CTL_IE |
                             ADC_CTL_END);    
                             
    ADCSequenceEnable(ADC0_BASE, ADC_SEQUENCE_THREE);

    ADCIntRegister(ADC0_BASE, ADC_SEQUENCE_THREE, adc_run_callback);
  
    ADCIntEnable(ADC0_BASE, ADC_SEQUENCE_THREE);
}

/**
 * Triggers the ADC to take a sample
 */
void sample_height(void) {
    ADCProcessorTrigger(ADC0_BASE, ADC_SEQUENCE_THREE);
}

void set_max_height(uint16_t value) {
    max_height = value;
}

void set_min_height(uint16_t value) {
    min_height = value;
}

void set_current_height(uint16_t value) {
    current_height = value;
}

int16_t get_current_height(void) {
    return current_height;
}

/**
 * Interrupt function for the ADC, removes the
 * value and passes it into the callback.
 */
void adc_run_callback(void) {
    uint32_t height_val;
    ADCSequenceDataGet(ADC0_BASE, ADC_SEQUENCE_THREE, &height_val);
    ADCIntClear(ADC0_BASE, 3);
    adc_callback(height_val);
}

/**
 * Sets the callback function for the ADC
 */
void set_adc_callback(void (*callback)(uint32_t)) {
    adc_callback = callback;
}

