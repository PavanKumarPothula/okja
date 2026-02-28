#include <Arduino.h>
#include "pin_configs.h"

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include "DAC.hpp"
#include "SDSPI.hpp"
#include "Display.hpp"
#include "GamePad.hpp"

volatile bool toPlay = false;

void ARDUINO_ISR_ATTR playPauseState()
{
  toPlay = !toPlay;
  gpio_set_level(pLED, toPlay);
  // DAC.enableBeep(toPlay);
}

void userBtnSetup(void *pvParameters)
{
  Serial.println("Setting up the Pins!");
  gpio_reset_pin(pLED);
  gpio_set_direction(pLED, GPIO_MODE_OUTPUT);
  gpio_set_direction(pUSER_BTN, GPIO_MODE_INPUT);
  Serial.println("Done up the Pins!");
  attachInterrupt(pUSER_BTN, playPauseState, CHANGE);
  Serial.println("Attached the interrupt");
  vTaskDelete(NULL);
}

void gamepadParsing(void *pvParameters)
{
  Serial.println("Begin the player");

  vTaskDelete(NULL);
}

void setup()
{

  // Serial.setTxTimeoutMs(0);
  Serial.begin(115200);
  while (!Serial)
  {
     // Wait a bit for Serial to become ready. Printing immediately doesn't work
      delay(100);
  }
  Serial.println("Start!");

  // xTaskCreate(player_task, "player_task", 8000, NULL, 1, NULL);
  // xTaskCreate(filesystem_task, "filesystem_task", 8000, NULL, 1, NULL);
  // xTaskCreate(display_task, "display_task", 8000, NULL, 1, NULL);
  xTaskCreate(gamepad_task, "gamepad_task", 8000, NULL, 1, NULL);
  delay(20000);
  Serial.println("Stop!");
}

void loop()
{
  vTaskDelete(NULL);
}
