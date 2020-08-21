#ifndef HELI_MENU_H
#define HELI_MENU_H

#include <stdint.h>
#include <stdbool.h>

/**
 * Defines the callback type as menu_callback_t
 * and label_callback_t.
 * 
 * menu_callback_t is called when the respective menu_element
 * is clicked
 * 
 * label_callback_t is called when ever the menu is updated
 * with the menu element in it, this updates the value of the
 * label for the menu
 */
typedef void (*menu_callback_t)();
typedef void (*label_callback_t)(char*);

/**
 * Definition of the menu elements.
 * 
 * Elements consist of their name (title),
 * callback (if they are a callable item),
 * submenu (if they are a submenu),
 * menu (if they are a submenu)
 */
typedef struct menu_element_t {
    const char* name;
    char* label;
    struct menu_t* parent;
    bool submenu;
    bool has_label;
    menu_callback_t callback;
    label_callback_t label_callback;
    struct menu_t* menu;
} menu_element_t;

/**
 * Definition of the menu.
 * 
 * Menus consist of names (used a heading),
 * selected (indicates with element is highlighted),
 * parent (if the menu has a parent and which is the parent),
 * num_elements (the total number of menu elements),
 * elements (an array of pointers to the child menu elements)
 */
typedef struct menu_t {
    const char* name;
    int8_t selected;
    struct menu_t* parent;
    int8_t num_elements;
    menu_element_t** elements;
} menu_t;

/**
 * Outputs the current menu to OLED.
 * 
 * Outputs the current set menu to the OLED
 * TODO not implemented.
 */
void display_menu_oled(void);

/**
 * Displays the current menu over UART.
 * 
 * Displays the current menu over UART,
 * colours are supported with UART_COLOUR_ENABLE == 1
 * the UART menu displays all of the menu elements
 * onto the terminal. If MENU_GUI == 1 the menu will
 * use XSS (Cross Side Scripting) to display a menu
 * to the webpage.
 */
void display_menu_uart(void);

/**
 * Creates a new menu.
 * 
 * Creates a menu, can either be used as a
 * sub menu or a top level menu.
 * 
 * Example:
 * menu_t main_menu = create_menu("Main Menu");
 * - This creates a menu named "Main Menu" with the pointer main_menu
 * 
 * @param name The title to be displayed at the top of the menu
 * @return menu A pointer to the created menu
 */
menu_t* create_menu(const char* name);

/**
 * Adds a new menu item to a menu.
 * 
 * Adds a new menu item to a given menu
 * these menu items are given a callback
 * to be called when the option is selected
 * and a name to label the menu item
 * 
 * Example:
 * menu_t main_menu = create_menu("Main Menu");
 * add_menu_item("Awesome", main_menu, super_awesome_function, NULL);
 * - This creates a menu item within main_menu named "Awesome" with the
 *   callback super_awesome_function() when 'clicked'
 * 
 * 
 * @param name The name of the menu item
 * @param parent The parent of the menu item
 * @param callback The callback to be run when the item is selected
 * @param label_callback A callback to update the label info on a menu item NULL for no callback
 */
void add_menu_item(const char* name, menu_t* parent, void (*callback)(void), void (*label_callback)(char*));

/**
 * Adds a submenu to a menu.
 * 
 * Adds a submenu to a given menu,
 * these are used to attach a menu to another
 * menu. This function creates a menu then 
 * returns the pointer to the created menu.
 * 
 * Example:
 * menu_t main_menu = create_menu("Main Menu");
 * menu_t submenu = add_submenu("SubMenu", main_menu);
 * - This creates a submenu item within main_menu named "SubMenu"
 *   items can be added to the created submenu useing the add_menu_item
 *   and add_submenu functions 
 * 
 * @param name The name for the submenu to be shown in the parent menu
 * @param parent The parent to attach the child to
 * @return submenu The pointer to the created menu
 */
menu_t* add_submenu(const char* name, menu_t* parent);

/**
 * Sets the currently active menu.
 * 
 * This must be called after the creations of
 * all of the menus to ensure that parent menu is set 
 * and displayed. eg:
 * 
 * menu_t* main_menu = create_menu("Main Menu");
 * set_current_menu(main_menu);
 * 
 * @param menu The menu to be set to the current menu
 */
void set_current_menu(menu_t* menu);

/**
 * Enters the child node.
 * 
 * Enters the currently selected child node of the
 * current menu and either calls the callback or
 * enters the submenu and set that to the current menu
 */
void enter_child_menu(void);

/**
 * Puts the menus up one layer.
 * 
 * Sets the current menu to the current
 * menu's parent
 */
void goto_parent_menu(void);

/**
 * Updates the current state of the menu.
 * 
 * Uses the current menu and refreshes all contained elements
 * these updates are triggered by a button press.
 * This includes updating the selected menu based on the
 * button press and updateding the elements labels using 
 * the label callbacks.
 */
void update_menu(void);

#endif // !HELI_MENU_H