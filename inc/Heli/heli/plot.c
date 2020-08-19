/**
 * plot.c - Plotting utility for the webpage
 * 
 * Author: Jos Craw 2020
 */
#include <string.h>

#include <utils/ustdlib.h>

#include "plot.h"
#include "logging.h"
#include "heli.h"

char* plot_data;

void init_plot(void) {
    plot_data = (char*)calloc(PLOT_BUFFER_SIZE, sizeof(char));
}

void plot(int value) {
    char* plot_offset = plot_data;
    while (*plot_offset) {
        plot_offset++;
    }

    usprintf(plot_offset, "%d,", value);
}

void send_plot(void) {
    char* plot_offset = plot_data;
    uart_send("\n<script>plotData([");
    uart_send(plot_offset);
    uart_send("])</script>\r\n");
    memset(plot_data, 0, sizeof(char)*PLOT_BUFFER_SIZE);
}