/**
 * plot.c - Plotting utility for the HeliViewer WebUI
 * 
 * Author: Jos Craw 2020
 */

#include <string.h>

#include <utils/ustdlib.h>

#include "plot.h"
#include "logging.h"
#include "heli.h"

plot_t* alt_plot;
plot_t* yaw_plot;

void init_plot(void) {
    // Create the Altitude Error Plot
    alt_plot = (plot_t*)calloc(1, sizeof(plot_t));
    alt_plot->num_elements = 0;
    alt_plot->data = (int*)malloc(sizeof(int)*PLOT_BUFFER_SIZE);

    alt_plot->plot_count = 0;

    // Create the Yaw error plot
    yaw_plot = (plot_t*)calloc(1, sizeof(plot_t));
    yaw_plot->num_elements = 0;
    yaw_plot->data = (int*)malloc(sizeof(int)*PLOT_BUFFER_SIZE);

    yaw_plot->plot_count = 0;
}

void plot(int value, plot_t* plot_data) {
    /* 
     * Ensures the UART doesn't get overwhelmed by
     * plot calls by only adding every
     * PLOT_DIVISOR number to the plot
     */
    if (plot_data->plot_count == PLOT_DIVISOR) {
        *(plot_data->data+plot_data->num_elements) = value;
        plot_data->num_elements++;
        plot_data->plot_count = 0;
    } else {
        plot_data->plot_count++;
    }
}

void display_plot(plot_t* plot_data, const char* func) {
    // Ensures there are elements to send
    if (plot_data->num_elements != 0) {
        char line[MAX_PLOT_MESSAGE_LENGTH] = "";
 
        // Generating the appropriate script tagged JavaScript
        usprintf(line, "\n<script>%s([", func);
        for (int i=0; i<plot_data->num_elements; i++) {
            char element[6] = "";
            int number = *(plot_data->data+i);
            usprintf(element, "%d,", number);
            strcat(line, element);
        }
        strcat(line, "])</script>\r\n");
        uart_send(line);

        // Empty the plot
        memset(plot_data->data, 0, sizeof(int)*PLOT_BUFFER_SIZE);
        plot_data->num_elements = 0;
    }
}

void plot_alt(int value) {
    plot(value, alt_plot);
}

void plot_yaw(int value) {
    plot(value, yaw_plot);
}

void display_plot_alt(void) {
    display_plot(alt_plot, "plotAltitude");
}

void display_plot_yaw(void) {
    display_plot(yaw_plot, "plotYaw");
}
