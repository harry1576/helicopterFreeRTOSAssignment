#ifndef HELI_PLOT_H
#define HELI_PLOT_H

#include <stdint.h>

typedef struct {
    uint8_t num_elements;
    int* data;
} plot_t;

void init_plot(void);

void plot(int value);

void send_plot(void);

#endif