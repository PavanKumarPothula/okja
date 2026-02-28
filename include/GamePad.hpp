#ifndef GAMEPAD_HPP
#define GAMEPAD_HPP

/* GamePad Library */
#include <Adafruit_seesaw.h>
#include "pin_configs.h"

// Origin for Image disp
#define IMAGE_XPOS ((uint16_t)0)
#define IMAGE_YPOS ((uint16_t)20)
#define MAX_IMAGE_WIDTH 240

// Button Maps
#define BUTTON_START 16
#define BUTTON_SELECT 0
#define BUTTON_X 6
#define BUTTON_Y 2
#define BUTTON_A 5
#define BUTTON_B 1

// Joystick Maps
#define X_AXIS 14
#define Y_AXIS 15

// For pull up of bulk pins
#define BUTTON_MASK ((uint32_t) \
     (1UL << BUTTON_X)      | \
     (1UL << BUTTON_Y)      | \
     (1UL << BUTTON_START)  | \
     (1UL << BUTTON_A)      | \
     (1UL << BUTTON_B)      | \
     (1UL << BUTTON_SELECT))
#define X_REF 524
#define Y_REF 521

typedef struct
{
    int16_t x_pos = X_REF;
    int16_t y_pos = X_REF;
    bool button_A = false;
    bool button_B = false;
    bool button_X = false;
    bool button_Y = false;
    bool button_SRT = false;
    bool button_SEL = false;
} gamepad_input;

// Function Definations
gamepad_input GamePadRead();
void GamePadInit();
void gamepad_task(void *);
#endif