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

void display_plot(void);

#endif