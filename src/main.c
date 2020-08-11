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
    while(1) {;
        sample_height();
        vTaskDelay(100);
    }
}

void get_average_sample(void* pvParameters) {
    while(1) {
        uint16_t average = adc_buffer_get_average(g_adc_buffer);
        vTaskDelay(2000);
    }
}

void update_control_loop(void* pvParamers) {
    while(1) {
        update_controllers();
        vTaskDelay(500);
    }
}

void refresh_uart(void* pvParameters) {
    while(1) {
        send_uart_from_queue();
        vTaskDelay(100);
    }
}

int main(void)
{
    heli_init();
    init_controllers();

    set_adc_callback(receive_adc_sample);
    g_adc_buffer = init_adc_buffer(10);

    if (pdTRUE != xTaskCreate(sampleHeight, "Height", 64, (void *)1, 5, NULL)) {
        while(1);   // Oh no! Must not have had enough memory to create the task.
    }

    if (pdTRUE != xTaskCreate(get_average_sample, "Average Height", 64, (void *)1, 5, NULL)) {
        while(1);   // Oh no! Must not have had enough memory to create the task.
    }

    if (pdTRUE != xTaskCreate(update_control_loop, "Update Controller", 64, (void *)1, 5, NULL)) {
        while(1);   // Oh no! Must not have had enough memory to create the task.
    }
    
    vTaskStartScheduler();  // Start FreeRTOS!!

    // Should never get here since the RTOS should never "exit".
    while(1) {

    }
}
