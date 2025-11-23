#include <Arduino.h>
#include "pin_configs.h"

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include "DAC.hpp"
#include "SDSPI.hpp"
Adafruit_TLV320DAC3100 DAC;
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
  Serial.begin(115200);
  Serial.println("Start!");
  SDCardSetup();
  // DAC = setupDAC();
  // DAC.setChannelVolume(true,-5);
  // DAC.setChannelVolume(false,-5);
  // audioSetup();
  // // xTaskCreate(userBtnSetup, "userBtnSetup", 32000, NULL, 1, NULL);
  // xTaskCreate(playFile, "playFLAC", 8000, NULL, 1, NULL);
  delay(10000);
  Serial.println("Stop!");
}

void loop()
{
  vTaskDelete(NULL);
}
