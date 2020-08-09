#ifndef LOGGING_H
#define LOGGING_H


#if ENABLE_UART_QUEUE == 1
    #include "FreeRTOS.h"
    #include "semphr.h"
    
    typedef struct uart_buffer_t {
        uint8_t size;
        uint8_t read_head;
        uint8_t write_head;
        SemaphoreHandle_t read_sem;
        SemaphoreHandle_t write_sem;
        SemaphoreHandle_t mutex;
        char** data;
    } uart_buffer_t;
#endif

#define error_log(...) log_error(__VA_ARGS__, __func__)
#define warn_log(...) log_warn(__VA_ARGS__, __func__)
#define info_log(...) log_info(__VA_ARGS__, __func__)
#define debug_log(...) log_debug(__VA_ARGS__, __func__)

/**
 * Sends a message over UART.
 * 
 * @param message The message to be sent
 */
void uart_send(char* message);

/**
 * Initialises the UART Logging for the Tiva.
 *
 * Initialises the Tiva onboard UART controller
 * for logging
 *
 */
void log_init(void);

/**
 * Log Debug, outputs debug log to UART.
 *
 * Outputs logging in the form [DEBUG] $MESSAGE through 
 * the UART connection on the Tiva
 *
 * @param message The char array for the message to be sent
 */ 
void log_debug(char* message, char const *caller);

/**
 * Log Info, outputs info log to UART.
 *
 * Outputs logging in the form [INFO] $MESSAGE through 
 * the UART connection on the Tiva
 *
 * @param message The char array for the message to be sent
 */ 
void log_info(char* message, char const *caller);

/**
 * Log Warning, outputs warning log to UART.
 *
 * Outputs logging in the form [WARN] $MESSAGE through 
 * the UART connection on the Tiva
 *
 * @param message The char array for the message to be sent
 */ 
void log_warn(char* message, char const *caller);

/**
 * Log Error, outputs error log to UART.
 *
 * Outputs logging in the form [ERROR] $MESSAGE through 
 * the UART connection on the Tiva
 *
 * @param message The char array for the message to be sent
 */ 
void log_error(char* message, char const *caller);

#if ENABLE_UART_QUEUE == 1

/**
 * Inits the UART Queue.
 * 
 * Inits the UART Queue to the size set in
 * UART_QUEUE_LENGTH
 */
void init_uart_queue(void);

/**
 * Function to send a message from the UART Queue.
 * 
 * Function to send message from UART queue, to be
 * called from FreeRTOS as task
 */
void send_uart_from_queue(void);

#endif

#endif
