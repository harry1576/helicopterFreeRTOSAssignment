#include <stdint.h>
#include <stdbool.h>

#include "OrbitOled.h"
#include "delay.h"
#include "FillPat.h"
#include "LaunchPad.h"
#include "OrbitBoosterPackDefs.h"
#include "OrbitOled.h"
#include "OrbitOledChar.h"
#include "OrbitOledGrph.h"

extern char rgbOledBmp[];

int put_image_to_oled(const char img[], uint8_t width, uint8_t height, uint8_t char_x_pos, uint8_t char_y_pos) {
    if (width > 128 && width % 8 != 0) {
        return 1;
    } else if (height > 32 && height % 8 != 0) {
        return 1;
    }

    uint8_t char_height = height / 8;
    uint8_t char_width = width / 8;

    uint16_t curr_val = 0;
    uint16_t curr_offset = 0;

    for (int i=0; i<char_height; i++) {
        for (int j=0; j<width; j++) {
            curr_offset = j + char_x_pos * 8 + char_y_pos * 8 + i * ccolOledMax;
            *(rgbOledBmp+curr_offset) = *(img+curr_val);
            curr_val++;
        }
    }
    OrbitOledUpdate();

    return 0;
}