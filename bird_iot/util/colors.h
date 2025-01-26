#pragma once

#include <cstdint>

class RGB {
public:
  RGB(uint8_t _r, uint8_t _g, uint8_t _b) { r=_r; b=_b; g=_g; }
  uint8_t r;
  uint8_t g;
  uint8_t b;
};

//uint32_t rgb(uint8_t r, uint8_t g, uint8_t b);

#define LED_LIME     RGB(0, 255, 0)
#define LED_RED      RGB(255, 0, 0)
#define LED_BLUE     RGB(0, 0, 255)
#define LED_ORANGE   RGB(255, 165, 0)
#define LED_PURPLE   RGB(128, 0, 128)
#define LED_WHITE    RGB(255, 255, 255)
#define LED_BLACK    RGB(0, 0, 0)
#define LED_YELLOW   RGB(255, 255, 0)
#define LED_PINK     RGB(255, 192, 203)
#define LED_CYAN     RGB(0, 255, 255)
#define LED_MAROON   RGB(128, 0, 0)
#define LED_GREEN    RGB(0, 128, 0)
#define LED_NAVY     RGB(0, 0, 128)
#define LED_AQUA     RGB(0, 255, 255)
#define LED_FUCHSIA  RGB(255, 0, 255)
#define LED_TEAL     RGB(0, 128, 128)
#define LED_OLIVE    RGB(128, 128, 0)
#define LED_SILVER   RGB(192, 192, 192)
#define LED_ICE_BLUE RGB(73, 232, 255)

// convert three 8 bit RGB levels to a 16 bit colour value
uint16_t color565(uint8_t r, uint8_t g, uint8_t b);

#define COLOR_BLACK       0x0000      /*   0,   0,   0 */
#define COLOR_NAVY        0x000F      /*   0,   0, 128 */
#define COLOR_DARKGREEN   0x03E0      /*   0, 128,   0 */
#define COLOR_DARKCYAN    0x03EF      /*   0, 128, 128 */
#define COLOR_MAROON      0x7800      /* 128,   0,   0 */
#define COLOR_PURPLE      0x780F      /* 128,   0, 128 */
#define COLOR_OLIVE       0x7BE0      /* 128, 128,   0 */
#define COLOR_LIGHTGREY   0xC618      /* 192, 192, 192 */
#define COLOR_DARKGREY    0x7BEF      /* 128, 128, 128 */
#define COLOR_BLUE        0x001F      /*   0,   0, 255 */
#define COLOR_GREEN       0x07E0      /*   0, 255,   0 */
#define COLOR_CYAN        0x07FF      /*   0, 255, 255 */
#define COLOR_RED         0xF800      /* 255,   0,   0 */
#define COLOR_MAGENTA     0xF81F      /* 255,   0, 255 */
#define COLOR_YELLOW      0xFFE0      /* 255, 255,   0 */
#define COLOR_WHITE       0xFFFF      /* 255, 255, 255 */
#define COLOR_ORANGE      0xFDA0      /* 255, 180,   0 */
#define COLOR_GREENYELLOW 0xB7E0      /* 180, 255,   0 */
#define COLOR_PINK        0xFC9F
