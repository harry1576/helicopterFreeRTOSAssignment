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
#include <string.h>
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


#include "yaw.h"
#include "heli.h"
#include "logging.h"

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

#if ENABLE_UART_QUEUE == 1
    SemaphoreHandle_t uart_send_mutex = NULL;
    QueueHandle_t uart_queue = NULL;
#endif

void log_init(void);
void log_debug(char* message, char const *caller);
void log_info(char* message, char const *caller);
void log_warn(char* message, char const *caller);
void log_error(char* message, char const *caller);

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
    #if ENABLE_UART_QUEUE == 1
        init_uart_queue();
    #endif
}

void uart_send(char* msg_buffer) {
#if ENABLE_UART_QUEUE == 1
    if (xSemaphoreTake(uart_send_mutex, UART_QUEUE_TICK_TIME) == pdTRUE) {
#endif
        while(*msg_buffer) {
            UARTCharPut(UART0_BASE, *(msg_buffer));
            msg_buffer++;
        }
#if ENABLE_UART_QUEUE == 1
        xSemaphoreGive(uart_send_mutex);
    }
#endif
    // free(msg_buffer)

}

void log_debug(char* message, char const *caller) {
    #if HELI_LOG_ENABLE == 1
    char* debug_message = (char*)malloc(sizeof(char)*(MAX_LOG_MESSAGE_LENGTH + COLOUR_SIZE));
    memset(debug_message, '\0', sizeof(debug_message));

    usprintf(debug_message, "[%sDEBUG%s] %s: %s\r\n", LOG_DEBUG_COLOUR, LOG_CLEAR, caller, message);

    #if ENABLE_UART_QUEUE == 1
        add_uart_to_queue(debug_message);
    #else
        uart_send(debug_message);
        free(debug_message);
    #endif
    #endif
}

void log_info(char* message, char const *caller) {
    #if HELI_LOG_ENABLE == 1
        char* info_message = (char*)malloc(sizeof(char)*(MAX_LOG_MESSAGE_LENGTH + COLOUR_SIZE));
        memset(info_message, '\0', sizeof(info_message));

        usprintf(info_message, "[%sINFO%s] %s: %s\r\n", LOG_INFO_COLOUR, LOG_CLEAR, caller, message);

    #if ENABLE_UART_QUEUE == 1
        add_uart_to_queue(info_message);
    #else
        uart_send(info_message);
        free(info_message);
    #endif
    #endif
}

void log_warn(char* message, char const *caller) {
    #if HELI_LOG_ENABLE == 1
        char* warn_message = (char*)malloc(sizeof(char)*(MAX_LOG_MESSAGE_LENGTH + COLOUR_SIZE));
        memset(warn_message, '\0', sizeof(warn_message));

        usprintf(warn_message, "[%sWARN%s] %s: %s\r\n", LOG_WARN_COLOUR, LOG_CLEAR, caller, message);

    #if ENABLE_UART_QUEUE == 1
        add_uart_to_queue(warn_message);
    #else
        uart_send(warn_message);
        free(warn_message);
    #endif
    #endif
}

void log_error(char* message, char const *caller) {
    #if HELI_LOG_ENABLE == 1
        char* error_message = (char*)malloc(sizeof(char)*(MAX_LOG_MESSAGE_LENGTH + COLOUR_SIZE));
        memset(error_message, '\0', sizeof(error_message));

        usprintf(error_message, "[%sERROR%s] %s: %s\r\n", LOG_ERROR_COLOUR, LOG_CLEAR, caller, message);
    
    #if ENABLE_UART_QUEUE == 1
        add_uart_to_queue(error_message);
    #else
        uart_send(error_message);
        free(error_log);
    #endif
    #endif
}

#if ENABLE_UART_QUEUE == 1
void init_uart_queue(void) {
    uart_send_mutex = xSemaphoreCreateMutex();

    uart_queue = xQueueCreate(UART_QUEUE_LENGTH, sizeof(char*));
}

void add_uart_to_queue(char* message) {
    if (xQueueSend(uart_queue, &message, UART_QUEUE_TICK_TIME) != pdTRUE) {
        free(message);
    }
}

void send_uart_from_queue(void) {
    char* message;
    if (xQueueReceive(uart_queue, &message, UART_QUEUE_TICK_TIME) == pdTRUE) {
        uart_send(message);
        free(message);
    }
}


#endif
