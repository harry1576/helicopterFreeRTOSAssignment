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
#include "heli.h"

extern char rgbOledBmp[];

#if ENABLE_ANIMATIONS == 1
volatile int8_t animation_id;

typedef struct animation {
    int8_t id;
    uint8_t current_frame;
    uint8_t total_frames;
    uint8_t char_x_pos;
    uint8_t char_y_pos;
    uint8_t width;
    uint8_t height;
    const char** frames;
} animation_t;

animation_t* animations[MAX_ANIMATIONS];

void init_animation(void);
int8_t begin_animation(const char* frames[], uint8_t total_frames, uint8_t width, uint8_t height, uint8_t char_x_pos, uint8_t char_y_pos);
int8_t update_animation(int8_t id);

#endif

int put_image_to_oled(const char img[], uint8_t width, uint8_t height, uint8_t char_x_pos, uint8_t char_y_pos);

#if ENABLE_ANIMATIONS == 1
void init_animation(void) {
    animation_id = 0;
}

int8_t begin_animation(const char* frames[], uint8_t total_frames, uint8_t width, uint8_t height, uint8_t char_x_pos, uint8_t char_y_pos) {
    if (animation_id == MAX_ANIMATIONS) {
        return -1;
    }
    animation_t* animation = (animation_t*) malloc(sizeof(animation_t));
    
    animation->id = animation_id;
    animation->current_frame = 0;
    animation->total_frames = total_frames;
    animation->char_x_pos = char_x_pos;
    animation->char_y_pos = char_y_pos;
    animation->width = width;
    animation->height = height;

    animation->frames = frames;

    *(animations+animation_id) = animation;
    animation_id++;

    char* frame = animation->frames[animation->current_frame];
    put_image_to_oled(frame, animation->width, animation->height,
        animation->char_x_pos, animation->char_y_pos);

    return animation->id;
}

int8_t update_animation(int8_t id) {
    int id_int = id;
    animation_t* current_animation = *(animations+id);

    
    current_animation->current_frame = (current_animation->current_frame + 1) % current_animation->total_frames;

    char* frame = *(current_animation->frames+current_animation->current_frame);
    put_image_to_oled(frame, current_animation->width, current_animation->height,
        current_animation->char_x_pos, current_animation->char_y_pos);

    return 0;
}

#endif

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

void clear_oled(void) {
    OrbitOledClear();
}