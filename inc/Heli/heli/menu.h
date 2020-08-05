#ifndef HELI_MENU_H
#define HELI_MENU_H

#include <stdint.h>
#include <stdbool.h>

typedef struct {
    const char* name;
    menu_t* parent;
    bool submenu;
    void* data;
} menu_element_t;

typedef struct {
    const char* name;
    int8_t selected;
    menu_t* parent;
    int8_t num_elements;
    menu_element_t** elements;
} menu_t;

void display_menu_oled(void);

void display_menu_uart(void);

menu_t* create_menu(char* name);

void add_menu_item(char* name, menu_t* parent, void (*callback)(void));

menu_t* add_submenu(char* name, menu_t* parent);

void set_current_menu(menu_t* menu);

void update_menu(void);

#endif // !HELI_MENU_H