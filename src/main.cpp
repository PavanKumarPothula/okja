#include <Arduino.h>

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include <Adafruit_TLV320DAC3100.h>

#include <AudioOutputI2S.h>
#include <AudioFileSourcePROGMEM.h>
#include <AudioGeneratorFLAC.h>
#include "sample.h"

#define LED_PIN GPIO_NUM_38
#define USER_BUTTON GPIO_NUM_21

AudioOutputI2S *out;
AudioFileSourcePROGMEM *file;
AudioGeneratorFLAC *flac;
volatile bool toPlay = false;

void ARDUINO_ISR_ATTR playPauseState()
{
  toPlay = !toPlay;
  gpio_set_level(LED_PIN, toPlay);
}

void userBtnSetup(void *pvParameters)
{
  Serial.println("Setting up the Pins!");
  gpio_reset_pin(LED_PIN);
  gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);

  gpio_set_direction(USER_BUTTON, GPIO_MODE_INPUT);
  Serial.println("Done up the Pins!");
  attachInterrupt(USER_BUTTON, playPauseState, RISING);
  Serial.println("Attached the interrupt");
  vTaskDelete(NULL);
}

void playFLAC(void *pvParameters)
{
  file = new AudioFileSourcePROGMEM(sample_flac, sample_flac_len);
  out = new AudioOutputI2S();
  flac = new AudioGeneratorFLAC();
  flac->begin(file, out);
}

void setup()
{
  Serial.begin();
  Serial.println("Start!");
  xTaskCreate(userBtnSetup, "userBtnSetup", 4000, NULL, 1, NULL);
  // xTaskCreate(playFLAC, "playFLAC", 1000, NULL, 1, NULL);
  Serial.println("Stop!");
  delay(10000);
}

void loop()
{
  vTaskDelete(NULL);
}
