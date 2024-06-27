/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

// -----------------------------------------------------
// NOTE: THIS HEADER IS ALSO INCLUDED BY ASSEMBLER SO
//       SHOULD ONLY CONSIST OF PREPROCESSOR DIRECTIVES
// -----------------------------------------------------

#ifndef _BOARDS_PIMORONI_PICOSYSTEM_H
#define _BOARDS_PIMORONI_PICOSYSTEM_H

// For board detection
#define PIMORONI_PICOSYSTEM

// --- BOARD SPECIFIC ---
#define PICOSYSTEM_VBUS_DETECT_PIN 2

#define PICOSYSTEM_LCD_SPI 0
#define PICOSYSTEM_LCD_RESET_PIN 4
#define PICOSYSTEM_LCD_CSN_PIN 5
#define PICOSYSTEM_LCD_SCLK_PIN 6
#define PICOSYSTEM_LCD_MOSI_PIN 7
#define PICOSYSTEM_LCD_VSYNC_PIN 8
#define PICOSYSTEM_LCD_DC_PIN 9

#define PICOSYSTEM_AUDIO_PIN 11

#define PICOSYSTEM_BACKLIGHT_PIN 12

#define PICOSYSTEM_LED_G_PIN 13
#define PICOSYSTEM_LED_R_PIN 14
#define PICOSYSTEM_LED_B_PIN 15

#define PICOSYSTEM_SW_Y_PIN 16
#define PICOSYSTEM_SW_X_PIN 17
#define PICOSYSTEM_SW_A_PIN 18
#define PICOSYSTEM_SW_B_PIN 19
#define PICOSYSTEM_SW_DOWN_PIN 20
#define PICOSYSTEM_SW_RIGHT_PIN 21
#define PICOSYSTEM_SW_LEFT_PIN 22
#define PICOSYSTEM_SW_UP_PIN 23

#define PICOSYSTEM_CHARGE_STAT_PIN 24
#define PICOSYSTEM_BAT_SENSE_PIN 26

// --- UART ---
#ifndef PICO_DEFAULT_UART
#define PICO_DEFAULT_UART 0
#endif

#ifndef PICO_DEFAULT_UART_TX_PIN
#define PICO_DEFAULT_UART_TX_PIN 0
#endif

#ifndef PICO_DEFAULT_UART_RX_PIN
#define PICO_DEFAULT_UART_RX_PIN 1
#endif

// --- LED ---
// Included so basic examples will work, and set it to the green LED
#ifndef PICO_DEFAULT_LED_PIN
#define PICO_DEFAULT_LED_PIN PICOSYSTEM_LED_G_PIN
#endif
// no PICO_DEFAULT_WS2812_PIN

#ifndef PICO_DEFAULT_LED_PIN_INVERTED
#define PICO_DEFAULT_LED_PIN_INVERTED 1
#endif

// --- I2C ---
//no PICO_DEFAULT_I2C
//no PICO_DEFAULT_I2C_SDA_PIN
//no PICO_DEFAULT_I2C_SCL_PIN

// --- SPI ---
// no PICO_DEFAULT_SPI
// no PICO_DEFAULT_SPI_SCK_PIN
// no PICO_DEFAULT_SPI_TX_PIN
// no PICO_DEFAULT_SPI_RX_PIN
// no PICO_DEFAULT_SPI_CSN_PIN

// --- FLASH ---
#define PICO_BOOT_STAGE2_CHOOSE_W25Q080 1

#ifndef PICO_FLASH_SPI_CLKDIV
#define PICO_FLASH_SPI_CLKDIV 2
#endif

#ifndef PICO_FLASH_SIZE_BYTES
#define PICO_FLASH_SIZE_BYTES (16 * 1024 * 1024)
#endif

// All boards have B1 RP2040
#ifndef PICO_RP2040_B0_SUPPORTED
#define PICO_RP2040_B0_SUPPORTED 0
#endif

#endif
