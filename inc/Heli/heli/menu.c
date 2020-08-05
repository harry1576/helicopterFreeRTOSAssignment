#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "menu.h"

volatile menu_t* current_menu;

void display_menu_oled(void) {
    return;
}

void display_menu_uart(void) {
    return;
}

menu_t* create_menu(const char* name) {
    menu_t* menu = (menu_t*) malloc(sizeof(menu_t));
    menu->name = name;
    menu->selected = 0;
    menu->num_elements = 0;
    menu->parent = NULL;

    return menu;
}

void add_menu_item(char* name, menu_t* parent, void (*callback)(void)) {
    menu_element_t* menu_element = (menu_element_t*) malloc(sizeof(menu_element_t));
    menu_element->name = name;
    menu_element->parent = parent;
    menu_element->submenu = false;
    menu_element->data = (void*) callback;

    parent->num_elements;
    parent->elements = realloc(parent->elements, (size_t) (sizeof(menu_element_t) * (parent->num_elements+1)));
    *(parent->elements+parent->num_elements) = menu_element;
    parent->num_elements++;
}   

menu_t* add_submenu(char* name, menu_t* parent) {
    menu_element_t* menu_element = (menu_element_t*) malloc(sizeof(menu_element_t));
    menu_t* menu = create_menu(name);

    menu->parent = parent;

    menu_element->name = name;
    menu_element->parent = parent;
    menu_element->submenu = true;
    menu_element->data = (void*) menu;

    parent->num_elements;
    parent->elements = realloc(parent->elements, (size_t) (sizeof(menu_element_t) * (parent->num_elements+1)));
    *(parent->elements+parent->num_elements) = menu_element;
    parent->num_elements++;

    return menu;
}

void set_current_menu(menu_t* menu) {
    current_menu = menu;
}

void update_menu(void) {
    return;
}
