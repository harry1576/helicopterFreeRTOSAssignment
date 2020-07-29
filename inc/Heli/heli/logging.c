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

#if ENABLE_SEM_MUT_UART_QUEUE == 1
    SemaphoreHandle_t uart_queue_mutex = NULL;
#endif

#if ENABLE_UART_QUEUE == 1
    void write_to_uart_queue(char* message);
    char* get_uart_queue_message(void);
    void init_uart_queue(void);
    void write_uart_queue(void);

    typedef struct UARTQueue
    {
        int size;
        int write_head;
        int read_head;
        #if ENABLE_SEM_MUT_UART_QUEUE == 1
        SemaphoreHandle_t read_sem, write_sem, mutex;
        #endif
        char** data;
    } uart_queue_t;

    static uart_queue_t* uart_queue;
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
    while(*msg_buffer) {
        UARTCharPut(UART_USB_BASE, *msg_buffer);
        msg_buffer++;
    }
}

void log_debug(char* message, char const *caller) {
    #if HELI_LOG_ENABLE == 1

    char debug_message[MAX_LOG_MESSAGE_LENGTH + COLOUR_SIZE];
    usprintf(debug_message, "[%sDEBUG%s] %s: %s\r\n", LOG_DEBUG_COLOUR, LOG_CLEAR, caller, message);

    #if ENABLE_UART_QUEUE == 1
        write_to_uart_queue(debug_message);
    #else
        uart_send(debug_message);
    #endif
    #endif
}

void log_info(char* message, char const *caller) {
    #if HELI_LOG_ENABLE == 1
        char info_message[MAX_LOG_MESSAGE_LENGTH + COLOUR_SIZE];

        usprintf(info_message, "[%sINFO%s] %s: %s\r\n", LOG_INFO_COLOUR, LOG_CLEAR, caller, message);

    #if ENABLE_UART_QUEUE == 1
        write_to_uart_queue(info_message);
    #else
        uart_send(info_message);
    #endif
    #endif
}

void log_warn(char* message, char const *caller) {
    #if HELI_LOG_ENABLE == 1
        char warn_message[MAX_LOG_MESSAGE_LENGTH + COLOUR_SIZE];

        usprintf(warn_message, "[%sWARN%s] %s: %s\r\n", LOG_WARN_COLOUR, LOG_CLEAR, caller, message);

    #if ENABLE_UART_QUEUE == 1
        write_to_uart_queue(warn_message);
    #else
        uart_send(warn_message);
    #endif
    #endif
}

void log_error(char* message, char const *caller) {
    #if HELI_LOG_ENABLE == 1
        char error_message[MAX_LOG_MESSAGE_LENGTH + COLOUR_SIZE];

        usprintf(error_message, "[%sERROR%s] %s: %s\r\n", LOG_ERROR_COLOUR, LOG_CLEAR, caller, message);
    
    #if ENABLE_UART_QUEUE == 1
        write_to_uart_queue(error_message);
    #else
        uart_send(error_message);
    #endif
    #endif
}

#if ENABLE_UART_QUEUE == 1
void init_uart_queue(void) {
    uart_queue->size = UART_QUEUE_LENGTH;
    uart_queue->write_head = 0;
    uart_queue->read_head = 0;

    char data[UART_QUEUE_LENGTH][MAX_LOG_MESSAGE_LENGTH];
    uart_queue->data = (char**) data;

    #if ENABLE_SEM_MUT_UART_QUEUE == 1

    uart_queue->read_sem = xSemaphoreCreateCounting(UART_QUEUE_LENGTH, 0);
    uart_queue->write_sem = xSemaphoreCreateCounting(UART_QUEUE_LENGTH, UART_QUEUE_LENGTH);
    uart_queue->mutex = xSemaphoreCreateMutex();

    uart_queue_mutex = xSemaphoreCreateMutex();

    #endif
}

void write_to_uart_queue(char* message) {
    #if ENABLE_SEM_MUT_UART_QUEUE == 1
    if (xSemaphoreTake(*(uart_queue->write_sem), (TickType_t) UART_QUEUE_TICK_TIME) == pdTRUE) {
        if (xSemaphoreTake(*(uart_queue->mutex), (TickType_t) UART_QUEUE_TICK_TIME) == pdTRUE) {
    #endif
            usprintf(*(uart_queue->data+uart_queue->write_head), "%s", message);
            uart_queue->write_head = (uart_queue->write_head + 1) % uart_queue->size;
    #if ENABLE_SEM_MUT_UART_QUEUE == 1
            xSemaphoreGive(uart_queue->mutex);
        }
        xSemaphoreGive(uart_queue->read_sem);
    }
    #endif

}

char* get_uart_queue_message(void) {
    #if ENABLE_SEM_MUT_UART_QUEUE == 1
    if (xSemaphoreTake(*(uart_queue->read_sem), (TickType_t) UART_QUEUE_TICK_TIME) == pdTRUE) {
        if (xSemaphoreTake(*(uart_queue->mutex), (TickType_t) UART_QUEUE_TICK_TIME) == pdTRUE) {
    #endif
            char message[MAX_LOG_MESSAGE_LENGTH];
            usprintf(message, "%s", *(uart_queue->data+uart_queue->read_head));
            uart_queue->read_head = (uart_queue->read_head + 1) % uart_queue->size;
    #if ENABLE_SEM_MUT_UART_QUEUE == 1
            xSemaphoreGive(uart_queue->mutex);
        }
        xSemaphoreGive(uart_queue->write_sem);
    }
    #endif
}

void write_uart_queue(void) {
    if (xSemaphoreTake(uart_queue_mutex, UART_QUEUE_TICK_TIME) == pdTRUE) {
        char* message = get_uart_queue_message();
        uart_send(message);
    }
}
#endif

