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

void init_height(void);
void sample_height(void);
void set_adc_callback(void (*callback)());

#define ADC_SEQUENCE_THREE 3
#define ADC_CHANNEL_ZERO 0


void init_height(void) {
    SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
    
    ADCSequenceConfigure(ADC0_BASE, ADC_SEQUENCE_THREE, ADC_TRIGGER_PROCESSOR, ADC_CHANNEL_ZERO);
  
    ADCSequenceStepConfigure(ADC0_BASE, ADC_SEQUENCE_THREE, ADC_CHANNEL_ZERO, ADC_CTL_CH9 | ADC_CTL_IE |
                             ADC_CTL_END);    
                             
    ADCSequenceEnable(ADC0_BASE, ADC_SEQUENCE_THREE);
}

uint16_t get_height(void) {
    uint32_t height_val;
    ADCSequenceDataGet(ADC0_BASE, ADC_SEQUENCE_THREE, &height_val);
    ADCIntClear(ADC0_BASE, 3);
    return (uint16_t) height_val;
}

void sample_height(void) {
    ADCProcessorTrigger(ADC0_BASE, ADC_SEQUENCE_THREE);
}

void set_adc_callback(void (*callback)()) {
    ADCIntRegister(ADC0_BASE, ADC_SEQUENCE_THREE, callback);
  
    ADCIntEnable(ADC0_BASE, ADC_SEQUENCE_THREE);

}