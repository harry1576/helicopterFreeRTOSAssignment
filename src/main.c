/**
 * Simple LED blinking example for the Tiva Launchpad
 */
#include <stdbool.h>
#include <stdint.h>

#include <heli/heli.h>
#include <heli/yaw.h>
#include <heli/height.h>
#include <heli/logging.h>
#include <heli/rotors.h>
#include <heli/heli_display.h>
#include <heli/menu.h>
#include <heli/heli_display.h>
#include <heli/stickman_image.h>
#include <heli/heli_status.h>
#include <heli/plot.h>
#include <heli/input.h>

#include <FreeRTOSConfig.h>

#include <FreeRTOS.h>
#include <task.h>

#include "controller.h"
#include "adc_buffer.h"

adc_buffer_t* g_adc_buffer;

void receive_adc_sample(uint32_t sample) {
    adc_buffer_insert(g_adc_buffer, (uint16_t)sample);
}

void sampleHeight(void* parameters) {
    while(1) {
        sample_height();
        vTaskDelay(20);
    }
}

void update_control_loop(void* pvParamers) {
    vTaskDelay(2000); // Wait to fill the ADC Buffer
    while(1) {
        update_controllers();
        vTaskDelay(configTICK_RATE_HZ/CONTROLLER_UPDATE);
    }
}

void refresh_uart(void* pvParameters) {
    while(1) {
        send_uart_from_queue();
        vTaskDelay(10);
    }
}

void refresh_menu(void* pvParameters) {
    while(1) {
        update_menu();
        vTaskDelay(25);
    }
}

void refresh_animation(void* pvParameters) {
    while(1) {
        update_animation(0);
        vTaskDelay(75);
    }
}

void alt_plot_update(void* pvParameters) {
    vTaskDelay(3000);
    while(1) {
        display_plot_alt();
        vTaskDelay(1000);
    }
}

void yaw_plot_update(void* pvParameters) {
    vTaskDelay(3000);
    while(1) {
        display_plot_yaw();
        vTaskDelay(1000);
    }
}

void update_inputs(void* pvParameters) {
    while(1) {
        updateButtons();
        vTaskDelay(configTICK_RATE_HZ/CONTROLLER_UPDATE);
    }
}

int main(void)
{
    heli_init();
    init_controllers();

    set_adc_callback(receive_adc_sample);
    g_adc_buffer = init_adc_buffer(10);

    menu_t* main_menu = create_menu("Main Menu");

    menu_t* flight_menu = add_submenu("Flight", main_menu);
    add_menu_item("UP", flight_menu, increment_height, NULL, NULL);
    add_menu_item("DOWN", flight_menu, decrement_height, NULL, NULL);
    add_menu_item("LEFT", flight_menu, increment_angle, NULL, NULL);
    add_menu_item("RIGHT", flight_menu, decrement_angle, NULL, NULL);
    add_menu_item("MID FLIGHT", flight_menu, mid_flight_adjustment, NULL, NULL);
    add_menu_item("180 DEG SPIN", flight_menu, spin_180_deg, NULL, NULL);

    menu_t* status_menu = add_submenu("Status", main_menu);
    add_menu_item("Main PWM", status_menu, NULL, "0", get_main_pwm_output);
    add_menu_item("Tail PWM", status_menu, NULL, "0", get_tail_pwm_output);
    add_menu_item("Current Height", status_menu, NULL, "0", get_height_percent);
    add_menu_item("Current Yaw", status_menu, NULL, "0", get_yaw_slot);

    set_current_menu(main_menu);

    init_animation();
    begin_animation(stickman_image_frames, stickman_image_frame_count, stickman_image_width, stickman_image_height, 12, 0);

    if (pdTRUE != xTaskCreate(refresh_menu, "Update Menu", 128, (void *)1, 3, NULL)) {
        while(1);   // Oh no! Must not have had enough memory to create the task.
    }
    if (pdTRUE != xTaskCreate(sampleHeight, "Sample Height", 32, NULL, 4, NULL)) {
        while(1);
    }
    if (pdTRUE != xTaskCreate(update_control_loop, "Update Controllers", 256, NULL, 4, NULL)) {
        while(1);
    }
    if (pdTRUE != xTaskCreate(refresh_uart, "Update UART", 64, NULL, 1, NULL)) {
        while(1);
    }
    if (pdTRUE != xTaskCreate(refresh_animation, "Update Animation", 128, (void *)1, 2, NULL)) {
        while(1);   // Oh no! Must not have had enough memory to create the task.
    }
    if (pdTRUE != xTaskCreate(yaw_plot_update, "Update Plot", 128, (void *)1, 2, NULL)) {
        while(1);   // Oh no! Must not have had enough memory to create the task.
    }
    if (pdTRUE != xTaskCreate(alt_plot_update, "Update Plot", 128, (void *)1, 2, NULL)) {
        while(1);   // Oh no! Must not have had enough memory to create the task.
    }

    vTaskStartScheduler();  // Start FreeRTOS!!

    // Should never get here since the RTOS should never "exit".
    while(1) {

    }
}
