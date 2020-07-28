/**
 * logging.c - UART Logging for Tiva Heli Project
 *
 *
 * Author: Jos Craw, Josh Hulbert, Harry Dobbs
 * Last Modified: 28.07.2020
 *
 */

#include <stdint.h>
#include <stdbool.h>
#include <inc/hw_memmap.h>
#include <inc/hw_types.h>
#include <inc/hw_ints.h>
#include <driverlib/gpio.h>
#include <driverlib/uart.h>
#include <driverlib/sysctl.h>
#include <driverlib/pin_map.h>
#include <utils/ustdlib.h>
#include <stdio.h>
#include <stdlib.h>

#include "heli.h"

#define UART_USB_BASE           UART0_BASE
#define UART_USB_PERIPH_UART    SYSCTL_PERIPH_UART0
#define UART_USB_PERIPH_GPIO    SYSCTL_PERIPH_GPIOA
#define UART_USB_GPIO_BASE      GPIO_PORTA_BASE
#define UART_USB_GPIO_PIN_RX    GPIO_PIN_0
#define UART_USB_GPIO_PIN_TX    GPIO_PIN_1
#define UART_USB_GPIO_PINS      UART_USB_GPIO_PIN_RX | UART_USB_GPIO_PIN_TX

#if UART_COLOUR_ENABLE == 1
    #define COLOUR_SIZE 7
#else
    #define COLOUR_SIZE 0 
#endif

void log_init(void);
void log_debug(char* message);
void log_info(char* message);
void log_warn(char* message);
void log_error(char* message);

void uart_send(char* msg_buffer);
void uart_init(void);


void uart_init(void) {
    SysCtlPeripheralEnable(UART_USB_PERIPH_UART);
    SysCtlPeripheralEnable(UART_USB_PERIPH_GPIO);

    GPIOPinTypeUART(UART_USB_GPIO_BASE, UART_USB_GPIO_PINS);
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);

    UARTConfigSetExpClk(UART_USB_BASE, SysCtlClockGet(), UART_BAUD_RATE,
            UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |
            UART_CONFIG_PAR_NONE);

    UARTFIFOEnable(UART_USB_BASE);
    UARTEnable(UART_USB_BASE);
}

void log_init(void) {
    uart_init();
}

void uart_send(char* msg_buffer) {
    while(*msg_buffer) {
        UARTCharPut(UART_USB_BASE, *msg_buffer);
        msg_buffer++;
    }
}

void log_debug(char* message) {
    #if HELI_LOG_ENABLE == 1
        char debug_message[MAX_LOG_MESSAGE_LENGTH + 11 + COLOUR_SIZE];

        usprintf(debug_message, "[%sDEBUG%s] %s\r\n", LOG_DEBUG_COLOUR, LOG_CLEAR, message);
        uart_send(debug_message);
    #endif
}

void log_info(char* message) {
    #if HELI_LOG_ENABLE == 1
        char info_message[MAX_LOG_MESSAGE_LENGTH + 10 + COLOUR_SIZE];

        usprintf(info_message, "[%sINFO%s] %s\r\n", LOG_INFO_COLOUR, LOG_CLEAR, message);
        uart_send(info_message);
    #endif
}

void log_warn(char* message) {
    #if HELI_LOG_ENABLE == 1
        char warn_message[MAX_LOG_MESSAGE_LENGTH + 10 + COLOUR_SIZE];

        usprintf(warn_message, "[%sWARN%s] %s\r\n", LOG_WARN_COLOUR, LOG_CLEAR, message);
        uart_send(warn_message);
    #endif
}

void log_error(char* message) {
    #if HELI_LOG_ENABLE == 1
        char error_message[MAX_LOG_MESSAGE_LENGTH + 11 + COLOUR_SIZE];

        usprintf(error_message, "[%sERROR%s] %s\r\n", LOG_ERROR_COLOUR, LOG_CLEAR, message);
        uart_send(error_message);
    #endif
}

