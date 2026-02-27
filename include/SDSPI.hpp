#ifndef SDSPI_HPP
#define SDSPI_HPP

#ifndef DISABLE_FS_H_WARNING
#define DISABLE_FS_H_WARNING // Disable warning for type File not defined.
#endif                       // DISABLE_FS_H_WARNING

#include <SdFat.h>
#include "pin_configs.h"
#define SD_FAT_TYPE 3
#define SPI_CLOCK SD_SCK_MHZ(4)
#define SD_CONFIG SdSpiConfig(pSPI_CS)

void SDCardSetup();
void filesystem_task(void *);
#endif // SDSPI_HPP