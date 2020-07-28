#ifndef LOGGING_H
#define LOGGING_H

#define error_log(...) log_error(__VA_ARGS__, __func__)
#define warn_log(...) log_warn(__VA_ARGS__, __func__)
#define info_log(...) log_info(__VA_ARGS__, __func__)
#define debug_log(...) log_debug(__VA_ARGS__, __func__)

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

#endif
