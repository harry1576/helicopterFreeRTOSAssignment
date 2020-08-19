#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <utils/ustdlib.h>
#include <driverlib/sysctl.h>

#include "input.h"
#include "menu.h"
#include "logging.h"
#include "heli.h"

volatile menu_t* current_menu;

void display_menu_oled(void) {
    return; //TODO add OLED functionality
}

void display_menu_uart(void) {
    char line[MAX_LOG_MESSAGE_LENGTH];
    memset(line, '\0', sizeof(line));

    #if UART_COLOUR_ENABLE == 1 && !ENABLE_MENU_GUI
        usprintf(line, "\033[2J%s%s%s\r\n", MENU_TITLE_COLOUR, current_menu->name, LOG_CLEAR);
    #elif ENABLE_MENU_GUI == 1
        uart_send("<script>clearMenu();</script>\n\r");
        usprintf(line, "<script>changeMenuTitle('%s');</script>\r\n", current_menu->name);
    #else
        usprintf(line, "%s\r\n", current_menu->name);
    #endif

    uart_send(line);
    
    for (int i=0; i<current_menu->num_elements; i++) {
        memset(line, '\0', sizeof(line));
        menu_element_t* element = *(current_menu->elements+i);
        #if ENABLE_MENU_GUI == 1
        if (!(element->has_label)) {
            usprintf(line, "<script>addMenuItem(' %s', %s, '', %s);</script>\r\n", element->name, 
                (i == current_menu->selected) ? "true": "false", (element->submenu) ? "true" : "false");
        } else {
            usprintf(line, "<script>addMenuItem(' %s', %s, '%s', %s);</script>\r\n", element->name, 
                (i == current_menu->selected) ? "true": "false", element->label, (element->submenu) ? "true" : "false");
        }
        #else
        if (!(element->has_label)) {
            usprintf(line, "%s%s\r\n", element->name, (i == current_menu->selected) ? "> " : "  ");
        } else {
            usprintf(line, "> %s (%s)\r\n", element->name, element->label, (i == current_menu->selected) ? "> " : "  ");
        }
        #endif 
        uart_send(line);
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

void add_menu_item(const char* name, menu_t* parent, void (*callback)(void), char* label, char* (*label_callback)(void)) {
    menu_element_t* menu_element = (menu_element_t*) malloc(sizeof(menu_element_t));
    if (!label && !label_callback) {
        menu_element->label = NULL;
        menu_element->label_callback = NULL;
        menu_element->has_label = false;
    } else {
        menu_element->label = (char*)calloc('\0', sizeof(char)*MAX_LABEL_LENGTH);
        menu_element->label_callback = (menu_callback_t)label_callback;
        menu_element->has_label = true;
    }
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
        display_menu();
    }
}

void enter_child_menu(void) {
    menu_element_t* child = *(current_menu->elements+current_menu->selected);
    if (child->submenu) {
        set_current_menu(child->menu);
    } else {
        if (child->callback) {
            menu_callback_t callback = child->callback;
            callback();
        }
    }
    display_menu();
}

void update_menu(void) {
    updateButtons();

    if (checkButton(LEFT) == PUSHED) {
        goto_parent_menu();
    }

    if (checkButton(RIGHT) == PUSHED) {
        enter_child_menu();
    }
    
    if (checkButton(UP) == PUSHED) {
        current_menu->selected = (current_menu->selected + (current_menu->num_elements-1)) % current_menu->num_elements;
        display_menu();
    }

    if (checkButton(DOWN) == PUSHED) {
        current_menu->selected = (current_menu->selected+1) % current_menu->num_elements;
        display_menu();
    }
}

void display_menu(void) {
    for (int i=0; i<current_menu->num_elements; i++) {
        menu_element_t* current_element = *(current_menu->elements+i);
        if (!current_element->submenu && current_element->label_callback != NULL) {
            char* new_label = current_element->label_callback();
            memset(current_element->label, '\0', sizeof(char)*MAX_LABEL_LENGTH);
            usprintf(current_element->label, "%s", new_label);
            free(new_label);
        }
    }
    display_menu_uart();
}
