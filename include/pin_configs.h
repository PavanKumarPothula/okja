#pragma once

// Pin Defs
// OnBoard
#define pLED GPIO_NUM_38
#define pUSER_BTN GPIO_NUM_21

// I2C
#define pI2C_SCL GPIO_NUM_16
#define pI2C_SDA GPIO_NUM_21

// I2S
#define pI2S_DOUT GPIO_NUM_17 // DATA - I2S data
#define pI2S_WS GPIO_NUM_18   // LRCLOCK - Word select
#define pI2S_BCLK GPIO_NUM_44 // BITCLOCK - I2S clock

// DAC
#define pDAC_RST GPIO_NUM_43

// GAMEPAD
// We are (re-)using DAC_RST pin
// Once it sends the reset 
// signal to the DAC.
#define pGAMEPAD_IRQ GPIO_NUM_43 

// SDIO pins for SD card
#define pSPI_SCK GPIO_NUM_2
#define pSPI_MISO GPIO_NUM_3
#define pSPI_MOSI GPIO_NUM_10
#define pSPI_CS GPIO_NUM_11

#define pSD_GND GPIO_NUM_1
#define pSD_CLK GPIO_NUM_2
#define pSD_D0 GPIO_NUM_3
#define pSD_CMD GPIO_NUM_10
#define pSD_D3 GPIO_NUM_11
#define pSD_D2 GPIO_NUM_12
#define pSD_D1 GPIO_NUM_13

// DISPLAY Pins
#define PIN_LCD_BL 38
#define PIN_LCD_D0 39
#define PIN_LCD_D1 40
#define PIN_LCD_D2 41
#define PIN_LCD_D3 42
#define PIN_LCD_D4 45
#define PIN_LCD_D5 46
#define PIN_LCD_D6 47
#define PIN_LCD_D7 48
#define PIN_LCD_POWER 15
#define PIN_LCD_RES 5
#define PIN_LCD_CS 6
#define PIN_LCD_DC 7
#define PIN_LCD_WR 8
#define PIN_LCD_RD 9
#define PIN_BUTTON_1 0
#define PIN_BUTTON_2 14
#define PIN_BAT_VOLT 4
#define PIN_TOUCH_INT 16
#define PIN_TOUCH_RES 21

// LCD CONFIG
#define EXAMPLE_LCD_PIXEL_CLOCK_HZ   (6528000) //(10 * 1000 * 1000)
#define LCD_HOR_RES                  320
#define LCD_VER_RES                  170
#define LVGL_LCD_BUF_SIZE            (LCD_HOR_RES * LCD_VER_RES)
#define EXAMPLE_PSRAM_DATA_ALIGNMENT 64
#define LVGL_TICK_PERIOD_MS          2