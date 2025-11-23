#include "SDSPI.hpp"

SdFs sd;
FsFile file;
FsFile root;

#define error(s) sd.errorHalt(&Serial, F(s))
void SDCardSetup()
{

  Serial.print("Type any character to start\n");
  while (!Serial.available()) {
    yield();
  }

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