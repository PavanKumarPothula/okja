#ifndef SDSPI_HPP
#define SDSPI_HPP

#ifndef DISABLE_FS_H_WARNING
#define DISABLE_FS_H_WARNING  // Disable warning for type File not defined. 
#endif  // DISABLE_FS_H_WARNING 

#include <SdFat.h>
#include "pin_configs.h"
#define SD_FAT_TYPE 3
const uint8_t SD_CS_PIN = pSPI_CS;
#define SPI_CLOCK SD_SCK_MHZ(80)
#define SD_CONFIG SdSpiConfig(SD_CS_PIN, DEDICATED_SPI, SPI_CLOCK)

void SDCardSetup();

#endif // SDSPI_HPP