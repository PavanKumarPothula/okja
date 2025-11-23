#include <DAC.hpp>
#include "pin_configs.h"
#include <SPIFFS.h>
#include <AudioOutputI2S.h>
#include <AudioFileSourceSPIFFS.h>
#include <AudioFileSourcePROGMEM.h>
#include <AudioGeneratorFLAC.h>
#include <sample.h>
AudioOutputI2S *dacOut;
// AudioFileSourceSPIFFS *sdCardFS;
AudioGeneratorFLAC *flac;
AudioFileSourcePROGMEM *fileP;

Adafruit_TLV320DAC3100 setupDAC()
{
    Serial.begin();
    Adafruit_TLV320DAC3100 codec; // Create codec object
    pinMode(pDAC_RST, OUTPUT);
    digitalWrite(pDAC_RST, LOW);
    delay(100);
    digitalWrite(pDAC_RST, HIGH);

    Serial.println("Init TLV DAC");
    TwoWire *i2c = new TwoWire(1);
    i2c->setPins(pI2C_SDA, pI2C_SCL);
    if (!codec.begin(TLV320DAC3100_I2CADDR_DEFAULT, i2c))
    {
        Serial.println("Failed to initialize codec!");
    }
    delay(10);

    // Interface Control
    if (!codec.setCodecInterface(TLV320DAC3100_FORMAT_I2S, // Format: I2S
                                 TLV320DAC3100_DATA_LEN_16))
    { // Length: 16 bits
        Serial.println("Failed to configure codec interface!");
    }

    // Clock MUX and PLL settings
    if (!codec.setCodecClockInput(TLV320DAC3100_CODEC_CLKIN_PLL) ||
        !codec.setPLLClockInput(TLV320DAC3100_PLL_CLKIN_BCLK))
    {
        Serial.println("Failed to configure codec clocks!");
    }

    if (!codec.setPLLValues(1, 2, 32, 0))
    { // P=2, R=2, J=32, D=0
        Serial.println("Failed to configure PLL values!");
    }

    // DAC/ADC Config
    if (!codec.setNDAC(true, 8) || // Enable NDAC with value 8
        !codec.setMDAC(true, 2))
    { // Enable MDAC with value 2
        Serial.println("Failed to configure DAC dividers!");
    }

    if (!codec.powerPLL(true))
    { // Power up the PLL
        Serial.println("Failed to power up PLL!");
    }

    // DAC Setup
    if (!codec.setDACDataPath(true, true,             // Power up both DACs
                              TLV320_DAC_PATH_NORMAL, // Normal left path
                              TLV320_DAC_PATH_NORMAL, // Normal right path
                              TLV320_VOLUME_STEP_1SAMPLE))
    { // Step: 1 per sample
        Serial.println("Failed to configure DAC data path!");
    }

    if (!codec.configureAnalogInputs(TLV320_DAC_ROUTE_MIXER, // Left DAC to mixer
                                     TLV320_DAC_ROUTE_MIXER, // Right DAC to mixer
                                     false, false, false,    // No AIN routing
                                     false))
    { // No HPL->HPR
        Serial.println("Failed to configure DAC routing!");
    }

    // DAC Volume Control
    if (!codec.setDACVolumeControl(
            false, false, TLV320_VOL_INDEPENDENT) || // Unmute both channels
        !codec.setChannelVolume(false, 18) ||        // Left DAC +0dB
        !codec.setChannelVolume(true, 18))
    { // Right DAC +0dB
        Serial.println("Failed to configure DAC volumes!");
    }

    // Headphone and Speaker Setup
    if (!codec.configureHeadphoneDriver(
            true, true,                     // Power up both drivers
            TLV320_HP_COMMON_1_35V,         // Default common mode
            false) ||                       // Don't power down on SCD
        !codec.configureHPL_PGA(0, true) || // Set HPL gain, unmute
        !codec.configureHPR_PGA(0, true) || // Set HPR gain, unmute
        !codec.setHPLVolume(true, 6) ||     // Enable and set HPL volume
        !codec.setHPRVolume(true, 6))
    { // Enable and set HPR volume
        Serial.println("Failed to configure headphone outputs!");
    }

    if (!codec.enableSpeaker(true) ||                // Dis/Enable speaker amp
        !codec.configureSPK_PGA(TLV320_SPK_GAIN_6DB, // Set gain to 6dB
                                true) ||             // Unmute
        !codec.setSPKVolume(true, 0))
    { // Enable and set volume to 0dB
        Serial.println("Failed to configure speaker output!");
    }

    if (!codec.configMicBias(false, true, TLV320_MICBIAS_AVDD) ||
        !codec.setHeadsetDetect(true) ||
        !codec.setInt1Source(true, true, false, false, false,
                             false) || // GPIO1 is detect headset or button press
        !codec.setGPIO1Mode(TLV320_GPIO1_INT1))
    {
        Serial.println("Failed to configure headset detect");
    }
    Serial.println("TLV config done!");
    return codec;
}

void audioSetup()
{
    Serial.println("Setting up Audio");
    fileP = new AudioFileSourcePROGMEM(sample_flac, sample_flac_len);
    SPIFFS.begin();
    flac = new AudioGeneratorFLAC();
    dacOut = new AudioOutputI2S();
    Serial.println("Setting up DAC Pins");
    dacOut->SetPinout(pI2S_BCLK, pI2S_WS, pI2S_DOUT);
    Serial.println("Done Setting up Audio");
}

void playFile(void *)
{
    flac->begin(fileP, dacOut);
    while (1)
    {
        if (flac->isRunning())
        {
            if (!flac->loop())
                flac->stop();
        }
        else
        {
            Serial.printf("flac done\n");
            vTaskDelay(pdMS_TO_TICKS(2000));
        }
    }
    vTaskDelete(NULL);
}