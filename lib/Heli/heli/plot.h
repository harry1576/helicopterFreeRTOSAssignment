#ifndef HELI_PLOT_H
#define HELI_PLOT_H

#include <stdint.h>

typedef struct {
    uint8_t num_elements;
    int plot_count;
    int* data;
} plot_t;

/**
 * Creates the plots to be shown on the WebUI.
 * 
 * Generates the altitude and yaw error plots
 * to be displayed on the WebUI
 */
void init_plot(void);

/**
 * Adds data to be plotted to a plot.
 * 
 * Adds every PLOT_DIVISOR value to the current array of plotting
 * data. This ensures that the UART output is not overloaded with
 * plotting data.
 * 
 * @param value the value to be added
 * @param plot_data the plot to add the data to
 */
void plot(int value, plot_t* plot_data);

/**
 * Displays a given plot.
 * 
 * Displays a given plot by inserting the current plot data over
 * UART to be interpreted by the appropriate JavaScript function
 * this is in the form:
 * <script>$FUNCTION([x,y,z])</script>
 * 
 * @param plot_data the plot to display over UART
 * @param func the name of the JavaScript function to use to interprest the data
 */
void display_plot(plot_t* plot_data, const char* func);

/**
 * Uses the plot function to plot to the yaw plot.
 * 
 * @param value to add to the yaw plot array
 */
void plot_yaw(int value);

/**
 * Uses the plot function to plot to the altitude plot.
 * 
 * @param value to add to the altitude plot array
 */
void plot_alt(int value);

/**
 * Uses the display_plot function to display the yaw plot.
 * 
 * Called regularly to output the current values for the
 * altitude plot.
 */
void display_plot_alt(void);

/**
 * Uses the display_plot function to display the yaw plot.
 * 
 * Called regularly to output the current values for the
 * yaw plot.
 */
void display_plot_yaw(void);

#endif
