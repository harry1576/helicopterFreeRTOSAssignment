#ifndef HELI_CONFIG_H
#define HELI_CONFIG_H

#define HELI_CLOCK_RATE = 80

// UART Logging Parameters
#define HELI_LOG_ENABLE 0

#define UART_BAUD_RATE 9600
#define MAX_LOG_MESSAGE_LENGTH 16

#define UART_COLOUR_ENABLE 1
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

#endif // !HELI_CONFIG_H