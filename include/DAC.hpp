#ifndef AUDIO_HPP
#define AUDIO_HPP
#include <Adafruit_TLV320DAC3100.h>

Adafruit_TLV320DAC3100 setupDAC();
void audioSetup();
void playFile(void *);
#endif // AUDIO_HPP