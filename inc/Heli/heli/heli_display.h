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
int put_image_to_oled(char* img, uint8_t width, uint8_t height, uint8_t char_x_pos, uint8_t char_y_pos);

#endif