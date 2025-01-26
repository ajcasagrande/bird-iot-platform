#include "LcdDriver.h"

#if CONFIG_ENABLE_I2C_LCD_CHARACTER_DISPLAY


#include "I2CDriver.h"
#include "rtos/lock_macros.h"

static void _execute(LcdDriver *driver) {
  driver->execute();
}

LcdDriver::LcdDriver(uint8_t address, uint8_t charsPerLine, uint8_t numLines) : IotPlugin("LCD Driver") {
  this->address = address;
  this->charsPerLine = charsPerLine;
  this->numLines = numLines;
  this->lcd = new LiquidCrystal_I2C(address, charsPerLine, numLines);
  task = new Task<LcdDriver>("LCD", this, _execute);
}

bool LcdDriver::setup() {
  TRY_LOCK(i2cDriver,
      lcd->begin();
  , return false;)

  return task->configure(50, _2k, MEDIUM_PRIORITY);
}

bool LcdDriver::start() {
  return task->start();
}

void LcdDriver::execute() {
  TRY_LOCK(i2cDriver,
    lcd->loop();
  ,)
}

void LcdDriver::clear() {
  TRY_LOCK(i2cDriver,
    if (lcd->isReady()) {
      lcd->clear();
    }
  ,)
}

void LcdDriver::clearLine(int line) {
  TRY_LOCK(i2cDriver,
    if (lcd->isReady()) {
      lcd->setCursor(0, line);
      lcd->print(LINE);
    }
  ,)
}

void LcdDriver::print(int x, int y, const char* message) {
  TRY_LOCK(i2cDriver,
    if (lcd->isReady()) {
      // Serial.println(message);
      lcd->setCursor(x, y);
      lcd->print(message);
    }
  ,)
}

void LcdDriver::printLine(int line, const char* message, bool isLoop) {
  TRY_LOCK(i2cDriver,
    if (lcd->isReady()) {
      if ((!isLoop || loopsSinceChange[line] >= 5) && strcmp(message, lines[line]) != 0) {
        loopsSinceChange[line] = 0;
        clearLine(line);
        print(0, line, message);
        lines[line] = message;
      } else {
        loopsSinceChange[line]++;
      }
    }
  ,)
}

void LcdDriver::print(const char* message) {
  TRY_LOCK(i2cDriver,
    if (lcd->isReady()) {
      // Serial.println(message);
      lcd->print(message);
    }
  ,)
}

void LcdDriver::scrollDisplayLeft() {
  TRY_LOCK(i2cDriver,
    if (lcd->isReady()) {
      lcd->scrollDisplayLeft();
    }
  ,)
}

void LcdDriver::scrollDisplayRight() {
  TRY_LOCK(i2cDriver,
    if (lcd->isReady()) {
      lcd->scrollDisplayRight();
    }
  ,)
}

#endif // CONFIG_ENABLE_I2C_LCD_CHARACTER_DISPLAY
