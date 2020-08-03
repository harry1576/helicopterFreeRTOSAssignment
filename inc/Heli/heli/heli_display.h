#ifndef HELI_DISPLAY_H
#define HELI_DISPLAY_H

#include <stdint.h>

/**
 * Puts a defined img to the OLED.
 * 
 * Puts an image defined by img_t to the OLED
 * at the char postition given by char_x_pos
 * and char_y_pos. Note Image should satisfy
 * width < 128 && width % 8 == 0 and 
 * height < 32 && height % 8 == 0
 * 
 * @param img Image data as an array of char
 * @param width Image width
 * @param height Image height
 * @param char_x_pos the start char (x direction)
 * @param char_y_pos the start char (y direction)
 * 
 * @return rc 1 if image does not meet constraints 
 */
int8_t put_image_to_oled(const char* img, uint8_t width, uint8_t height, uint8_t char_x_pos, uint8_t char_y_pos);

int8_t begin_animation(const char* frames[], uint8_t total_frames, uint8_t width, uint8_t height, uint8_t char_x_pos, uint8_t char_y_pos);

int8_t update_animation(int8_t id);

void init_animation(void);

#endif