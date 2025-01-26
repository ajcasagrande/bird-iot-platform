#pragma once

// NOTE:
// MCP9808 and LM75A have 3 input pins that control the i2c address
// a0, a1, a2. each one represents one digit 0b001, 0b010, 0b100
// if all are enabled, that is 0b111

// 0x00
#define QMC5883L_COMPASS_ADDRESS (0x0d)

// 0x10
#define MCP9808_BASE_ADDRESS (0x18)
#define MCP9808_MAX_ADDRESS (MCP9808_BASE_ADDRESS + 0b111) // 0x1f

// 0x20
#define NFC_PN532_ADDRESS (0x24)
#define LCD_CHARACTER_DISPLAY_ADDRESS_A (0x27)

// 0x30
#define AXP192_ADDRESS (0x34)
#define OLED_DISPLAY_ADDRESS_A (0x3c)
#define OLED_DISPLAY_ADDRESS_B (0x3d)
#define LCD_CHARACTER_DISPLAY_ADDRESS_B (0x3f)

// 0x40
#define HDC1008_ADDRESS (0x40)
#define HTU21D_ADDRESS (0x40)
#define LM75A_BASE_ADDRESS (0x48)
#define LM75A_MAX_ADDRESS (LM75A_BASE_ADDRESS + 0b111) // 0x4f

// 0x50
#define M5_RTC_ADDRESS (0x51)

// 0x60
#define MPU6886_ADDRESS (0x68)

// 0x70
#define BMP280_MIN_ADDRESS (0x76)
#define BMP280_MAX_ADDRESS (0x77)
