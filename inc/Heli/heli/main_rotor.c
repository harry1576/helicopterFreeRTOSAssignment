/**
 * main_rotor.c - Heli Height interface
 *
 * Authors: Jos Craw, Josh Hulbert, Harry Dobbs
 */

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/pin_map.h" //Needed for pin configure
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/pwm.h"
#include "driverlib/systick.h"
#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"
#include "driverlib/uart.h"
#include "stdlib.h"
#include "inc/hw_memmap.h"
#include "utils/ustdlib.h"


// PWM configuration
#define PWM_START_RATE_HZ 250
#define PWM_RATE_STEP_HZ 50
#define PWM_RATE_MIN_HZ 250
#define PWM_RATE_MAX_HZ 250
#define PWM_FIXED_DUTY 0
#define PWM_DIVIDER_CODE SYSCTL_PWMDIV_4
#define PWM_DIVIDER 4

//  PWM Hardware Details M0PWM7 (gen 3)
//  ---Main Rotor PWM: PC5, J4-05
#define PWM_MAIN_BASE PWM0_BASE
#define PWM_MAIN_GEN PWM_GEN_3
#define PWM_MAIN_OUTNUM PWM_OUT_7
#define PWM_MAIN_OUTBIT PWM_OUT_7_BIT
#define PWM_MAIN_PERIPH_PWM SYSCTL_PERIPH_PWM0
#define PWM_MAIN_PERIPH_GPIO SYSCTL_PERIPH_GPIOC
#define PWM_MAIN_GPIO_BASE GPIO_PORTC_BASE
#define PWM_MAIN_GPIO_CONFIG GPIO_PC5_M0PWM7
#define PWM_MAIN_GPIO_PIN GPIO_PIN_5
#define OUTPUT_MAX 98
#define OUTPUT_MIN 2


//*****************************************************************************
//
// @Description This function is used to set the duty cycle and frequency of
// the main rotor PWM.
// @Param ui32Freq is the desired PWM frequency
// @param ui32Duty is the desired duty cycle for the main rotor
// @Return none
//
//*****************************************************************************
void set_main_PWM(uint32_t ui32Freq, uint32_t ui32Duty)
{
    // Calculate the PWM period corresponding to the freq.
    uint32_t ui32Period = SysCtlClockGet() / PWM_DIVIDER / ui32Freq;
    PWMGenPeriodSet(PWM_MAIN_BASE, PWM_MAIN_GEN, ui32Period);
    PWMPulseWidthSet(PWM_MAIN_BASE, PWM_MAIN_OUTNUM, ui32Period * ui32Duty / 100);
}

//*****************************************************************************
//
// @Description This function is used initialize the main rotor PWM
// @Param void
// @Return void
//
//*****************************************************************************
void init_main_rotor(void)
{

    SysCtlPeripheralEnable(PWM_MAIN_PERIPH_PWM); // Enable the PWM peripheral
    SysCtlPeripheralEnable(PWM_MAIN_PERIPH_GPIO); // Enable the GPIO peripheral
    GPIOPinConfigure(PWM_MAIN_GPIO_CONFIG);
    GPIOPinTypePWM(PWM_MAIN_GPIO_BASE, PWM_MAIN_GPIO_PIN);

    PWMGenConfigure(PWM_MAIN_BASE, PWM_MAIN_GEN, PWM_GEN_MODE_UP_DOWN | PWM_GEN_MODE_NO_SYNC);
    // Set the initial PWM parameters
    //setMainPWM(PWM_START_RATE_HZ, PWM_FIXED_DUTY);

    PWMGenEnable(PWM_MAIN_BASE, PWM_MAIN_GEN);

    // Disable the output.  Repeat this call with 'true' to turn O/P on.
    PWMOutputState(PWM_MAIN_BASE, PWM_MAIN_OUTBIT, false);
    PWMOutputState(PWM_MAIN_BASE, PWM_MAIN_OUTBIT, true); // set output states of rotors to true


}

