#include "SDSPI.hpp"

SdFs sd;
FsFile file;
FsFile root;

#define error(s) sd.errorHalt(&Serial, F(s))
void SDCardSetup()
{

  while (!Serial)
  {
    yield();
  }
  Serial.println("Type any character to start");
  while (!Serial.available()) {
    yield();
  }

  pinMode(pSD_GND, OUTPUT);
  digitalWrite(pSD_GND,LOW);
  pinMode(pSPI_CS, OUTPUT);
  SPI.begin(pSPI_SCK, pSPI_MISO, pSPI_MOSI, pSPI_CS);
  // Initialize the SD card.
  if (!sd.begin(SD_CONFIG)) {
    sd.initErrorHalt(&Serial);
  }

  Serial.print("\nList of files on the SD.\n");
  sd.ls("/",LS_R);

  // spi.begin(pSPI_SCK, pSPI_MISO, pSPI_MOSI, pSPI_CS);
  // pinMode(spi.pinSS(), OUTPUT);
  // if(!SD.begin(CS, spi, SPI_SPEED)){
  //     Serial.println("Card mount failed!");
  // }
}