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
 * http://ascii-table.com/ansi-escape-sequences.php
 * 
 * The define is in the form:
 * #define LOG_WARN_COLOUR "\033[01;33m" // Yellow Bold
 */

// Yaw Parameters
#define YAW_SPOKE_COUNT 448
#define YAW_VELOCITY_ENABLE 1
#define YAW_VELOCITY_PERIOD 10

// FreeRTOS Parameters
#define ENABLE_FREERTOS_DELAY 1

// Animation Parameters
#define ENABLE_ANIMATIONS 1
#define MAX_ANIMATIONS 1

// Controller Parameters
#define CONTROLLER_UPDATE 100.0

#define PWM_FREQUENCY 250

#define MAX_HEIGHT 100
#define MIN_HEIGHT 0

#define MAIN_KP 0.45
#define MAIN_KI 0.15
#define MAIN_KD 1.4

#define TAIL_KP 7.0
#define TAIL_KI 0.15
#define TAIL_KD 2.5

#define MAIN_MAX_KP 75
#define MAIN_MAX_KI 25
#define MAIN_MAX_KD 10

#define TAIL_MAX_KP 60
#define TAIL_MAX_KI 50
#define TAIL_MAX_KD 50

#define MAX_PWM 85
#define MIN_PWM 10

// Flight Parameters
#define HEIGHT_INCREMENT_AMOUNT 10
#define YAW_INCREMENT_AMOUNT 19
#define MID_FLIGHT_ALTITUDE 50
#define SPIN_180 224

#define HOVER_HEIGHT 10

// Menu Parameters
#define MAX_LABEL_LENGTH 10

// XSS Injection Parameters (Only works on th online HeliRig)
#define ENABLE_XSS 1

#define ENABLE_MENU_GUI 1

// Script Message for XSS
#define HELI_XSS_LOADER "\n<script src='https://storage.googleapis.com/heli.ucquarantine.net/v0.1.1/heli_loader.js'></script>\r\n"
#define ENABLE_HELI_SOUNDS_XSS 1

// Plotting Parameters
#define ENABLE_PLOTTING 1
#define PLOT_BUFFER_SIZE 75

#endif // !HELI_CONFIG_H
