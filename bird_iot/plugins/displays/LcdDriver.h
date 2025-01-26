#pragma once

#include "sdkconfig.h"

#if CONFIG_ENABLE_I2C_LCD_CHARACTER_DISPLAY

#include "include/builtin.h"
#include <LiquidCrystal_I2C.h>

#define LINE "                "

#include "IotPlugin.h"
#include "tasks/TaskClass.h"

class LcdDriver : public IotPlugin {
private:
  uint8_t address;
  uint8_t numLines = 2;
  uint8_t charsPerLine = 16;
  const char* lines[4] = {"", "", "", nullptr};
  uint32_t loopsSinceChange[4] = {0, 0, 0, 0};
  LiquidCrystal_I2C* lcd;
  Task<LcdDriver> *task;

public:
  LcdDriver(uint8_t address, uint8_t charsPerLine, uint8_t numLines);
  bool setup() override;
  bool start() override;
  void execute();
  
  void clear();
  void clearLine(int line);
  void print(int x, int y, const char* message);
  void printLine(int line, const char* message, bool isLoop=false);
  void print(const char* message);
  void scrollDisplayLeft();
  void scrollDisplayRight();
};

#endif // CONFIG_ENABLE_I2C_LCD_CHARACTER_DISPLAY
