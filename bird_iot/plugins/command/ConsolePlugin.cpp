#include "ConsolePlugin.h"

#if CONFIG_ENABLE_CONSOLE_PLUGIN
#include "esp_log.h"
#include "esp_err.h"
#include "ConsoleHelper.h"
#include "esp_console.h"
#include "linenoise/linenoise.h"
#include "CommandPlugin.h"

#define CONSOLE_PROMPT_COLOR LOG_BOLD(LOG_COLOR_PURPLE)

#define REGISTER_COMMAND(name, help, ptr) \
  do { \
    const esp_console_cmd_t __cmd = {name, help, nullptr, ptr, nullptr}; \
    ESP_ERROR_CHECK_WITHOUT_ABORT(esp_console_cmd_register(&__cmd)); \
  } while (0)

static const char* TAG = "Console";

ConsolePlugin Console;

static std::string prompt;

static void _setupConsole() {
  bool dumbTerminal =
#if CONFIG_ENABLE_ADVANCED_PROMPT
      linenoiseProbe() != 0;
#else
      true;
#endif
  if (dumbTerminal) {
    prompt = deviceId();
    prompt += "> ";
    linenoiseSetDumbMode(1);
  } else {
    prompt = CONSOLE_PROMPT_COLOR;
    prompt += deviceId();
    prompt += "> " LOG_RESET_COLOR;
  }
}

static bool _handleCommand(const char* cmd) {
  int ret_code;
  esp_err_t err = esp_console_run(cmd, &ret_code);

  if (err == ESP_ERR_NOT_FOUND) {
    // pass
  } else if (err == ESP_ERR_INVALID_ARG) {
    // blank command
  } else if (err != ESP_OK) {
    LOGW(TAG, "Internal error: " << esp_err_to_name(err));
  } else if (ret_code != ESP_OK) {
    LOGW(TAG, "Command returned non-zero error code: 0x" << _HEX(ret_code) << " (" << esp_err_to_name(err) << ")");
  }

  return err == ESP_OK && ret_code == ESP_OK;
}

static void _consoleTask() {
  // Get a line using linenoise. The line is returned when ENTER is pressed.
  char* line = linenoise(prompt.c_str());
  if (line == nullptr) {
    // ignore empty lines
    return;
  }
  // Add the command to the history
  linenoiseHistoryAdd(line);
#if CONFIG_STORE_HISTORY
  // Save command history to filesystem
  linenoiseHistorySave(HISTORY_PATH);
#endif

  // try to run the command
  bool res = false;
  for (auto & plugin : App.getPlugins()) {
    if (plugin->handleCommand(line)) {
      res = true;
      break;
    }
  }

  if (!res) {
    LOGW(TAG, "Unrecognized command");
  }
  
  // linenoise allocates line buffer on the heap, so need to free it
  linenoiseFree(line);
}

ConsolePlugin::ConsolePlugin() : IotPlugin("Console Plugin") {
  task = new VoidTask("Console", _consoleTask);
}

static void registerBirdIoTCommands() {
  REGISTER_COMMAND("meminfo", "Print heap stats", &CommandPlugin::printHeapStats);
  REGISTER_COMMAND("cpu", "Print cpu usage stats", &CommandPlugin::printCpuStats);
  REGISTER_COMMAND("rtos", "Print rtos stats", &CommandPlugin::printRTOS);
  REGISTER_COMMAND("ps", "Print task stats", &CommandPlugin::listTasks);
}

bool ConsolePlugin::setup() {
  initialize_console();

  if (esp_console_register_help_command() != ESP_OK) {
    return false;
  }

  registerBirdIoTCommands();

  _setupConsole();

  return task->configure(0, _2p5, HIGH_PRIORITY, CORE_1, false, false, 0);
}

bool ConsolePlugin::start() {
  return task->start();
}

//  void ConsolePlugin::onWifiConnected() { }
//  void ConsolePlugin::onWifiDisconnected() { }
//  void ConsolePlugin::onMqttConnected() { }
//  void ConsolePlugin::onMqttDisconnected() { }
//  bool ConsolePlugin::handleMqttMessage(const char *topic, int id, const char *cmd, const JsonDocument& json) {
//   return false; // false means not handled 
// }

// NOTE: Need to disable this, otherwise it causes recursion
bool ConsolePlugin::handleCommand(const std::string& cmd) {
  return _handleCommand(cmd.c_str());
}

#if ENABLE_I2C_OLED_DISPLAY_PLUGIN
//  void ConsolePlugin::addFramesAndOverlays() { }
#endif

#endif // CONFIG_ENABLE_CONSOLE_PLUGIN
