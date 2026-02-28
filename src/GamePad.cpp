#include "GamePad.hpp"

// Adafruit Seesaw inits
Adafruit_seesaw ss;

gamepad_input last_input;
gamepad_input GamePadRead()
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

void GamePadInit()
{
  // Seesaw init
  Serial.println("\n===Seesaw Init Start");

  ss.begin(0x50);
  uint32_t version = ((ss.getVersion() >> 16) & 0xFFFF);
  // Configure pins and attach IRQ
  ss.pinModeBulk(BUTTON_MASK, INPUT_PULLUP);
  ss.setGPIOInterrupts(BUTTON_MASK, 1);
  pinMode(pGAMEPAD_IRQ, INPUT_PULLDOWN);

  Serial.println("\n===Seesaw Init Done");
}
  
void gamepad_task(void *)
{
  GamePadInit();
  while (true)
  {
    GamePadRead();
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
  vTaskDelete(NULL);
}