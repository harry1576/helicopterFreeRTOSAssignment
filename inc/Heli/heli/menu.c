#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <utils/ustdlib.h>

#include "input.h"
#include "menu.h"
#include "logging.h"
#include "heli.h"

#if ENABLE_UART_QUEUE == 1
    #include <FreeRTOS.h>
    #include <semphr.h>

    extern SemaphoreHandle_t uart_send_mutex;
#endif

volatile menu_t* current_menu;

void display_menu_oled(void) {
    return;
}

void display_menu_uart(void) {
    char line[MAX_LOG_MESSAGE_LENGTH];
    memset(line, '\0', sizeof(line));
    #if UART_COLOUR_ENABLE == 1
    usprintf(line, "\033[2J%s%s%s\r\n", LOG_WARN_COLOUR, current_menu->name, LOG_CLEAR);
    #else
    usprintf(line, "%s\r\n", current_menu->name);
    #endif

    #if ENABLE_UART_QUEUE == 1
    if (xSemaphoreTake(uart_send_mutex, UART_QUEUE_TICK_TIME) == pdTRUE) {
        uart_send(line);
        xSemaphoreGive(uart_send_mutex);
    }
    #else
    uart_send(line);
    #endif

    for (int i=0; i<current_menu->num_elements; i++) {
        memset(line, '\0', sizeof(line));
        menu_element_t* element = *(current_menu->elements+i);
        if (i == current_menu->selected) {
            usprintf(line, " >%s\r\n", element->name);
        } else {
            usprintf(line, "  %s\r\n", element->name);
        }

        #if ENABLE_UART_QUEUE == 1
        if (xSemaphoreTake(uart_send_mutex, UART_QUEUE_TICK_TIME) == pdTRUE) {
            uart_send(line);
            xSemaphoreGive(uart_send_mutex);
        }
        #else
        uart_send(line);
        #endif
    }
}

menu_t* create_menu(const char* name) {
    menu_t* menu = (menu_t*) malloc(sizeof(menu_t));
    menu->name = name;
    menu->selected = 0;
    menu->num_elements = 0;
    menu->parent = NULL;
    menu->elements = (menu_element_t**)malloc(sizeof(menu_element_t**));

    return menu;
}

void add_menu_item(const char* name, menu_t* parent, void (*callback)(void)) {
    menu_element_t* menu_element = (menu_element_t*) malloc(sizeof(menu_element_t));
    menu_element->name = name;
    menu_element->parent = parent;
    menu_element->submenu = false;
    menu_element->callback = (menu_callback_t)callback;

    parent->elements = (menu_element_t**)realloc(parent->elements, sizeof(menu_element_t*) * (parent->num_elements+1));

    *(parent->elements+parent->num_elements) = menu_element;
    parent->num_elements++;
}   

menu_t* add_submenu(const char* name, menu_t* parent) {
    menu_element_t* menu_element = (menu_element_t*) malloc(sizeof(menu_element_t));
    menu_t* menu = create_menu(name);

    menu->parent = parent;

    menu_element->name = name;
    menu_element->parent = parent;
    menu_element->submenu = true;
    menu_element->menu = menu;

    parent->elements = (menu_element_t**)realloc(parent->elements, sizeof(menu_element_t*) * (parent->num_elements+1));

    *(parent->elements+parent->num_elements) = menu_element;
    parent->num_elements++;

    return menu;
}

void set_current_menu(menu_t* menu) {
    current_menu = menu;
}

void goto_parent_menu(void) {
    menu_t* parent = current_menu->parent;

    if (parent) {
        set_current_menu(parent);
        display_menu_uart();
    }
}

void enter_child_menu(void) {
    menu_element_t* child = *(current_menu->elements+current_menu->selected);
    if (child->submenu) {
        set_current_menu(child->menu);
    } else {
        menu_callback_t callback = child->callback;
        callback();
    }
    display_menu_uart();
}

void update_menu(void) {
    updateButtons();

    uint8_t button_state = checkButton(LEFT);

    switch (button_state) {
        case PUSHED:
            goto_parent_menu();
            break;
        case RELEASED:
            break;
    }

    button_state = checkButton(RIGHT);

    switch (button_state) {
        case PUSHED:
            enter_child_menu();
            break;
        case RELEASED:
            break;
    }

    button_state = checkButton(UP);

    switch (button_state) {
        case PUSHED:
            current_menu->selected = (current_menu->selected + (current_menu->num_elements-1)) % current_menu->num_elements;
            display_menu_uart();
            break;
        case RELEASED:
            break;
    }

    button_state = checkButton(DOWN);

    switch (button_state) {
        case PUSHED:
            current_menu->selected = (current_menu->selected+1) % current_menu->num_elements;
            display_menu_uart();
            break;
        case RELEASED:
            break;
    }
}

void display_menu(void) {
    display_menu_uart();
}
