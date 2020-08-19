#ifndef HELI_PLOT_H
#define HELI_PLOT_H

#include <stdint.h>

typedef struct {
    uint8_t num_elements;
    int plot_count;
    int* data;
} plot_t;

void init_plot(void);

void plot(int value, plot_t* plot_data);

void display_plot(plot_t* plot_data, const char* func);

void plot_yaw(int value);

void plot_alt(int value);

void display_plot_alt(void);

void display_plot_yaw(void);

#endif