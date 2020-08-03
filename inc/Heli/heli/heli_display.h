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
 * @param char_x_pos The offset in the x direction of the image, in char width (8px)
 * @param char_y_pos The offset in the y direction of the image, in char width (8px)
 * 
 * @return rc 1 if image does not meet constraints 
 */
int8_t put_image_to_oled(const char* img, uint8_t width, uint8_t height, uint8_t char_x_pos, uint8_t char_y_pos);

/**
 * Initalises an animation.
 * 
 * Uses a given array of frames, with reference parameters to
 * create an animation and display the first frame
 * 
 * @param frames an array of frames, defined in the auto generated h file
 * @param total_frames The total number of frames, defined in the auto generated h file
 * @param width The width of the image in pixels, defined in the auto generated h file
 * @param height The height of the image in pixels, defined in the auto generated h file
 * @param char_x_pos The offset in the x direction of the image, in char width (8px)
 * @param char_y_pos The offset in the y direction of the image, in char width (8px)
 * 
 * @return id The id of the created animation
 */
int8_t begin_animation(const char* frames[], uint8_t total_frames, uint8_t width, uint8_t height, uint8_t char_x_pos, uint8_t char_y_pos);

/**
 * Updates a given animation.
 * 
 * Updates to the next frame of a given animation
 * 
 * @param id The id of the animation to update
 * 
 * @return rc The return value for the animation 1 is error
 */
int8_t update_animation(int8_t id);

/**
 * Initalises the parameters for animations.
 */
void init_animation(void);

#endif