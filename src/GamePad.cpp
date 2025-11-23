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
#define BUTTON_MASK ((uint32_t)(1UL << BUTTON_X) | (1UL << BUTTON_Y) | (1UL << BUTTON_START) | (1UL << BUTTON_A) | (1UL << BUTTON_B) | (1UL << BUTTON_SELECT))
#define X_REF 524
#define Y_REF 521

// Adafruit Seesaw inits
Adafruit_seesaw ss;
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

gamepad_input last_input;
gamepad_input gamepad_read()
{
  // Reverse x/y values to match joystick orientation
  gamepad_input current_input;
  uint16_t x = X_REF - ss.analogRead(14);
  uint16_t y = Y_REF - ss.analogRead(15);

  if ((abs(x - last_input.x_pos) > 3) || (abs(y - last_input.y_pos) > 3))
  {
    Serial.print("x: ");
    Serial.print(x);
    Serial.print(", ");
    Serial.print("y: ");
    Serial.println(y);
    last_input.x_pos = x;
    last_input.y_pos = y;
  }
  current_input.x_pos = last_input.x_pos;
  current_input.y_pos = last_input.y_pos;

  if (digitalRead(pGAMEPAD_IRQ))
  {
    uint32_t buttons = ss.digitalReadBulk(BUTTON_MASK);

    Serial.println(buttons, BIN);

    if (!(buttons & (1UL << BUTTON_A)))
    {
      current_input.button_A = true;
      Serial.println("\n Button A pressed");
    }
    if (!(buttons & (1UL << BUTTON_B)))
    {
      current_input.button_B = true;
      Serial.println("\n Button B pressed");
    }
    if (!(buttons & (1UL << BUTTON_Y)))
    {
      current_input.button_Y = true;
      Serial.println("\n Button Y pressed");
    }
    if (!(buttons & (1UL << BUTTON_X)))
    {
      current_input.button_X = true;
      Serial.println("\n Button X pressed");
    }
    if (!(buttons & (1UL << BUTTON_SELECT)))
    {
      current_input.button_SEL = true;
      Serial.println("\n Button SELECT pressed");
    }
    if (!(buttons & (1UL << BUTTON_START)))
    {
      current_input.button_SRT = true;
      Serial.println("\n Button START pressed");
    }
  }
  return current_input;
}

void init()
{
  // Seesaw init
  Serial.println("\n===Seesaw Init Start");

  ss.begin(0x50);
  uint32_t version = ((ss.getVersion() >> 16) & 0xFFFF);
  // Configure pins and attach IRQ
  ss.pinModeBulk(BUTTON_MASK, INPUT_PULLUP);
  ss.setGPIOInterrupts(BUTTON_MASK, 1);

  pinMode(pGAMEPAD_IRQ, INPUT);

  Serial.println("\n===Seesaw Init Done");
}