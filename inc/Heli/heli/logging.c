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
    uart_buffer_t* uart_buffer;
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
        UARTCharPut(UART_USB_BASE, *msg_buffer);
        msg_buffer++;
    }
    #if ENABLE_UART_QUEUE == 1
    xSemaphoreGive(uart_send_mutex);
    }
    #endif
}

void log_debug(char* message, char const *caller) {
    #if HELI_LOG_ENABLE == 1
    char* debug_message = (char*)malloc(sizeof(char)*(MAX_LOG_MESSAGE_LENGTH + COLOUR_SIZE));
    memset(debug_message, '\0', sizeof(debug_message));

    usprintf(debug_message, "[%sDEBUG%s] %s: %s\r\n", LOG_DEBUG_COLOUR, LOG_CLEAR, caller, message);

    #if ENABLE_UART_QUEUE == 1
        add_uart_to_queue(message);
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
        free(error_message);
    #endif
    #endif
}

#if ENABLE_UART_QUEUE == 1
void init_uart_queue(void) {
    uart_send_mutex = xSemaphoreCreateMutex();

    #if HELI_LOG_LEVEL >= 1
    if (uart_send_mutex == NULL) {
        uart_send("ERROR: UART MUTEX FAILED\r\n");
    }
    #endif

    uart_buffer = (uart_buffer_t*)malloc(sizeof(uart_buffer_t));
    uart_buffer->read_head = 0;
    uart_buffer->write_head = 0;
    uart_buffer->size = UART_QUEUE_LENGTH;
    
    uart_buffer->data = (char**)malloc(sizeof(char*)*UART_QUEUE_LENGTH);

    uart_buffer->mutex = xSemaphoreCreateMutex();
    uart_buffer->read_sem = xSemaphoreCreateCounting(UART_QUEUE_LENGTH, 0);
    uart_buffer->write_sem = xSemaphoreCreateCounting(UART_QUEUE_LENGTH, UART_QUEUE_LENGTH);

    #if HELI_LOG_LEVEL >= 3
        uart_send("UART SETUP SUCCESSFULLY\r\n");
    #endif
}

void add_uart_to_queue(char* message) {
    if (xSemaphoreTake(uart_buffer->write_sem, UART_QUEUE_TICK_TIME) == pdTRUE) {
        if (xSemaphoreTake(uart_buffer->mutex, UART_QUEUE_TICK_TIME) == pdTRUE) {
            *(uart_buffer->data + uart_buffer->write_head) = message;
            uart_buffer->write_head = (uart_buffer->write_head+1) & uart_buffer->size;
            xSemaphoreGive(uart_buffer->mutex);
        } else {
            free(message);
        }
        xSemaphoreGive(uart_buffer->read_sem);
    } else {
        free(message);
    }
}

void send_uart_from_queue(void) {
    if (xSemaphoreTake(uart_buffer->read_sem, UART_QUEUE_TICK_TIME) == pdTRUE) {
        if (xSemaphoreTake(uart_buffer->mutex, UART_QUEUE_TICK_TIME) == pdTRUE) {
            char* message = *(uart_buffer->data + uart_buffer->read_head);
            uart_send(message);
            free(message);
            uart_buffer->read_head = (uart_buffer->read_head+1) % uart_buffer->size;
            xSemaphoreGive(uart_buffer->mutex);
        }
        xSemaphoreGive(uart_buffer->write_sem);
    }
}
#endif
