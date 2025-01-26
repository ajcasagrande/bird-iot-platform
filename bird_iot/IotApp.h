#pragma once

#include "sdkconfig.h"
#include <tasks/TaskClass.h>
#include "include/builtin.h"
#include "colors.h"
#include "LedModes.h"
#include "util/Profile.h"
#include "include/rtos.h"

#include "IotPlugin.h"
#include "LcdDriver.h"
#include "OledDisplayPlugin.h"
#include "NeoPixelDriver.h"

class IotApp {
private:
  bool _setupComplete = false;
  bool _pluginsSetup = false;
#if CONFIG_ENABLE_I2C_LCD_CHARACTER_DISPLAY
  LcdDriver *lcdDriver = nullptr;
#endif
#if CONFIG_ENABLE_NEOPIXEL_DRIVER
  NeoPixelDriver *neoPixel = nullptr;
#endif
#if CONFIG_ENABLE_I2C_OLED_DISPLAY_PLUGIN
  OledDisplayPlugin* oled = nullptr;
#endif
  std::vector<IotPlugin*> plugins;
  std::vector<TaskClass*> tasks;
  const char* name = "IotApp";

public:
  IotApp() = default;

  Profile profile;
#if CONFIG_ENABLE_I2C_OLED_DISPLAY_PLUGIN
  OledDisplayPlugin* getOled() { return oled; };
#endif
  std::vector<IotPlugin*>& getPlugins() { return plugins; }
  std::vector<TaskClass*>& getTasks() { return tasks; }
  void registerTask(TaskClass *task) { tasks.push_back(task); }

  bool setup();
  bool setupPlugins();
  bool startPlugins();
  static bool bist();
  void registerPlugin(IotPlugin *plugin);

#ifdef CONFIG_APP_ROLLBACK_ENABLE
  static void performRollback();
#endif

#if CONFIG_ENABLE_I2C_LCD_CHARACTER_DISPLAY
  void registerLcd(LcdDriver *lcdDriver);
#endif

#if CONFIG_ENABLE_NEOPIXEL_DRIVER
  void registerNeoPixel(NeoPixelDriver* neoPixelDriver);
#endif

#if CONFIG_ENABLE_I2C_OLED_DISPLAY_PLUGIN
  void registerOledDisplay(OledDisplayPlugin* oledDisplayPlugin);
#endif

  void setStatusColor(RGB color);

  void drawProgress(uint8_t percent, const String& strTop, const String& strBottom);
  void updateProgress(uint8_t percent, char* strTop, char* strBottom, char* prev);

#if CONFIG_ENABLE_I2C_LCD_CHARACTER_DISPLAY
  void lcdClear();
  void lcdClearLine(int line);
  void lcdPrint(int x, int y, const char* message);
  void lcdPrintLine(int line, const char* message, bool isLoop=false);
  void lcdPrint(const char* message);
#endif

  bool isSetupComplete() { return _setupComplete; }

  void suspendAllTasks(bool keepOTATasks);
  void resumeAllTasks();
  void removeAllTasks(bool keepOTATasks);
};

extern IotApp App;
