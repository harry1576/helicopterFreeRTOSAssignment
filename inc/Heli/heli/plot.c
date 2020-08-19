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

plot_t* plot_data;
int plot_count;

void init_plot(void) {
    plot_data = (plot_t*)calloc(1, sizeof(plot_t));
    plot_data->num_elements = 0;
    plot_data->data = (int*)malloc(sizeof(int)*PLOT_BUFFER_SIZE);

    plot_count = 0;
}

void plot(int value) {
    if (plot_count == PLOT_DIVISOR) {
        *(plot_data->data+plot_data->num_elements) = value;
        plot_data->num_elements++;
        plot_count = 0;
    } else {
        plot_count++;
    }
}

void display_plot(void) {
    if (plot_data->num_elements >= PLOT_BUFFER_SIZE) {
        char line[MAX_PLOT_MESSAGE_LENGTH] = "\n<script>plotData([";
        for (int i=0; i<PLOT_BUFFER_SIZE; i++) {
            char element[6] = "";
            int number = *(plot_data->data+i);
            usprintf(element, "%d,", number);
            strcat(line, element);
        }
        strcat(line, "])</script>\r\n");
        uart_send(line);

        memset(plot_data->data, 0, sizeof(int)*PLOT_BUFFER_SIZE);
        plot_data->num_elements = 0;
    }
}