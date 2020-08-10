#ifndef HELI_H
#define HELI_H

#include "../heli_config.h"

#ifndef HELI_LOG_ENABLE
    #define HELI_LOG_ENABLE 1
#endif

#ifndef HELI_LOG_LEVEL
    #define HELI_LOG_LEVEL 1
#endif

#ifndef UART_BAUD_RATE
    #define UART_BAUD_RATE 9600
#endif

#ifndef MAX_LOG_MESSAGE_LENGTH
    #define MAX_LOG_MESSAGE_LENGTH 16
#endif

#ifndef UART_COLOUR_ENABLE
    #define UART_COLOUR_ENABLE 0
#endif

#if UART_COLOUR_ENABLE == 1
    #ifndef LOG_ERROR_COLOUR
        #define LOG_ERROR_COLOUR "\033[1;31m" 
        // Red Bold
    #endif
    #ifndef LOG_WARN_COLOUR
        #define LOG_WARN_COLOUR "\033[01;33m" 
        // Yellow Bold
    #endif
    #ifndef LOG_INFO_COLOUR
        #define LOG_INFO_COLOUR ""
    #endif
    #ifndef LOG_DEBUG_COLOUR
        #define LOG_DEBUG_COLOUR ""
    #endif

    #define LOG_CLEAR "\033[0m"
#else
    #ifndef LOG_ERROR_COLOUR
        #define LOG_ERROR_COLOUR ""
    #endif
    #ifndef LOG_WARN_COLOUR
        #define LOG_WARN_COLOUR ""
    #endif
    #ifndef LOG_INFO_COLOUR
        #define LOG_INFO_COLOUR ""
    #endif
    #ifndef LOG_DEBUG_COLOUR
        #define LOG_DEBUG_COLOUR ""
    #endif

    #define LOG_CLEAR "\033[0m"
#endif

#ifndef YAW_SPOKE_COUNT
    #define YAW_SPOKE_COUNT 450
#endif

#ifndef YAW_VELOCITY_ENABLE
    #define YAW_VELOCITY_ENABLE 0
#endif

#ifndef YAW_VELOCITY_PERIOD
    #define YAW_VELOCITY_PERIOD 10
#endif

#ifndef ADC_BUFFER_SIZE
    #define ADC_BUFFER_SIZE 10
#endif

#ifndef ENABLE_UART_QUEUE
    #define ENABLE_UART_QUEUE 0
    #define ENABLE_SEM_MUT_UART_QUEUE 0
#endif

#ifndef UART_QUEUE_LENGTH
    #define UART_QUEUE_LENGTH 10
#endif

#if ENABLE_UART_QUEUE == 0
    #if ENABLE_SEM_MUT_UART_QUEUE == 1
        #error If Queues are disable mutexes and semaphores for the queue must also be disabled
    #endif
#endif

#ifndef UART_QUEUE_TICK_TIME
    #define UART_QUEUE_TICK_TIME 0
#endif

#ifndef ENABLE_ANIMATIONS
    #define ENABLE_ANIMATIONS 0
#endif

#ifndef MAX_ANIMATIONS
    #define MAX_ANIMATIONS 2
#endif

// Controller Parameters
#ifdef TAIL_KP
    #define TAIL_KP 0
#endif

#ifndef TAIL_KI
    #define TAIL_KI 0
#endif

#ifndef TAIL_KD
    #define TAIL_KD 0
#endif

#ifndef MAIN_KP
    #define MAIN_KP 0
#endif

#ifndef MAIN_KI
    #define MAIN_KI 0
#endif

#ifndef MAIN_KD
    #define MAIN_KD 0
#endif

#ifndef MAIN_MAX_KP
    #define MAIN_MAX_KP 25
#endif

#ifndef MAIN_MAX_KI
    #define MAIN_MAX_KI 25
#endif

#ifndef MAIN_MAX_KD
    #define MAIN_MAX_KD 10
#endif

#ifndef TAIL_MAX_KP
    #define TAIL_MAX_KP 25
#endif

#ifndef TAIL_MAX_KI
    #define TAIL_MAX_KI 25
#endif

#ifndef TAIL_MAX_KD
    #define TAIL_MAX_KD 10
#endif

#ifndef MAX_PWM
    #define MAX_PWM 60
#endif

#ifndef MIN_PWM
    #define MIN_PWM 10
#endif

#ifndef HEIGHT_INCREMENT_AMOUNT
    #define HEIGHT_INCREMENT_AMOUNT 10
#endif

#ifndef YAW_INCREMENT_AMOUNT
    #define YAW_INCREMENT_AMOUNT 15
#endif

#ifndef HOVER_HEIGHT
    #define HOVER_HEIGHT 10
#endif

/**
 * Initialiser for the heli project.
 *
 * Initialises the heli given the configuration
 * parameters contained in heli_config.h
 */
void heli_init(void);

#endif
