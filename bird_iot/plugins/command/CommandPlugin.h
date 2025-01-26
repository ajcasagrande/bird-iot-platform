#pragma once
#include "sdkconfig.h"

#if CONFIG_ENABLE_COMMANDS_PLUGIN
#include "include/common.h"

class CommandPlugin : public IotPlugin {
public:
  CommandPlugin();

  void onMqttConnected() override;
  bool handleMqttMessage(const char *topic, int id, const char *cmd, const JsonDocument& json) override;
  bool handleCommand(const std::string& cmd) override;

  static int printHeapStats(int argc, char **argv);
  static int listPlugins(int argc, char **argv);
  static int listTasks(int argc, char **argv);
  static int printHelp(int argc, char **argv);
  static int doWifiScan(int argc, char **argv);
  static int printVersion(int argc, char **argv);
  static int printRTOS(int argc, char **argv);
  static int printCpuStats(int argc, char **argv);

  static void registerCommands();

};

extern CommandPlugin Commands;

#endif // CONFIG_ENABLE_COMMANDS_PLUGIN
