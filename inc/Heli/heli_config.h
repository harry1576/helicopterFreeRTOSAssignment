#ifndef HELI_CONFIG_H
#define HELI_CONFIG_H

// UART Logging Parameters
#define HELI_LOG_ENABLE 1
#define HELI_LOG_LEVEL 3

#define UART_BAUD_RATE 9600
#define MAX_LOG_MESSAGE_LENGTH 100

#define ENABLE_UART_QUEUE 1
#define UART_QUEUE_LENGTH 10

#define UART_QUEUE_TICK_TIME 10 // Using semaphores

#define UART_COLOUR_ENABLE 0 // Warning HeliRig does not support colours
/*
 * Log Colours can be defined here
 * using terminal colours found at:
 * http://web.theurbanpenguin.com/adding-color-to-your-output-from-c/
 * 
 * The define is in the form:
 * #define LOG_WARN_COLOUR "\033[01;33m" // Yellow Bold
 */

// Yaw Parameters
#define YAW_SPOKE_COUNT 360
#define YAW_VELOCITY_ENABLE 1
#define YAW_VELOCITY_PERIOD 10

// Animation Parameters
#define ENABLE_ANIMATIONS 1
#define MAX_ANIMATIONS 2

// Controller Parameters
#define MAIN_KP 10
#define MAIN_KI 10
#define MAIN_KD 10

#define TAIL_KP 10
#define TAIL_KI 10
#define TAIL_KD 10

#define MAIN_MAX_KP 25
#define MAIN_MAX_KI 25
#define MAIN_MAX_KD 10

#define TAIL_MAX_KP 25
#define TAIL_MAX_KI 25
#define TAIL_MAX_KD 10

#define MAX_PWM 90
#define MIN_PWM 0

// Flight Parameters
#define HEIGHT_INCREMENT_AMOUNT 10
#define YAW_INCREMENT_AMOUNT 15

#define HOVER_HEIGHT 10

#endif // !HELI_CONFIG_H
