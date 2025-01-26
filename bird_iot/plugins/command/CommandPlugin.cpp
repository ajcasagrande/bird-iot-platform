#include "CommandPlugin.h"

#if CONFIG_ENABLE_COMMANDS_PLUGIN
#include "WifiScanPlugin.h"
#include "WebsocketWrapper.h"
#include "include/version.h"
#include "rtos/lock_macros.h"

static const char* TAG = "Command";

CommandPlugin Commands;

CommandPlugin::CommandPlugin() : IotPlugin("Command Plugin") {
}

void CommandPlugin::registerCommands() {
}

int CommandPlugin::printHelp(int argc, char **argv) {
  TRY_LOCK(BufferedStreamJoiner,
  put(DIM("-- Command Help --"));

  putHelp("id", "print device id");
  putHelp("i2c scan", "scan for i2c devices");
  putHelp("wifi scan", "scan for wifi networks (passive)");
  putHelp("ip", "print ip address");
  putHelp("plugins", "list all enabled plugins");
  putHelp("tasks, ps", "list all registered tasks");
  putHelp("heap, mem", "print out statistics about the heap");
  putHelp("vcc", "print current Vcc voltage");
  putHelp("v, version", "print version info");
  putHelp("uptime, up", "print system uptime");
  putHelp("millis, ms", "print system uptime in millis");
  putHelp("ls", "list contents of SPIFFS"); // todo
  putHelp("bist", "Built-In Self Test");
  putHelp("reset, restart", "Restart the device");
  putHelp("hard reset", "Hard Reset the device");
  putHelp("rtos", "RTOS Information");
  putHelp("cpu", "CPU Usage");
  putHelp("conn", "print connection drops and information");
  putHelp("date, time", "print date and time based on Sntp");

  putHelp("help", "print this help");
  put(DIM("-- End Command Help --"));
  ,);
  return ESP_OK;
}

bool CommandPlugin::handleCommand(const std::string& cmd) {
  if (cmd == "help" || cmd == "h") {
    printHelp(0, nullptr);

  } else if (cmd == "plugins") {
    listPlugins(0, nullptr);

  } else if (cmd == "v" || cmd == "version") {
    printVersion(0, nullptr);

  } else if (cmd == "rtos" || cmd == "top") {
    printRTOS(0, nullptr);

  } else if (cmd == "tasks" || cmd == "ps") {
    listTasks(0, nullptr);

  } else if (cmd == "heap" || cmd == "mem") {
    printHeapStats(0, nullptr);

  } else if (cmd == "ip") {
    TRY_LOCK(BufferedStreamJoiner,
      putStringVal(10, "IP Address", Wifi.getIpAddress().c_str());
    ,);

  } else if (cmd == "vcc") {
    TRY_LOCK(BufferedStreamJoiner,
      putValf(7, "Voltage", "%f", readVcc());
    ,);

  } else if (cmd == "uptime" || cmd == "up") {
    TRY_LOCK(BufferedStreamJoiner,
      std::string uptime = prettyDuration(millis64());
      putStringVal(7, "Uptime", uptime.c_str());
    ,);

  } else if (cmd == "millis" || cmd == "ms") {
    TRY_LOCK(BufferedStreamJoiner,
      put(BOLD("Millis  | ") << millis());
    ,);

  } else if (cmd == "bist") {
    App.bist();

#if CONFIG_ENABLE_WIFI_SCAN_PLUGIN
  } else if (cmd == "wifi scan") {
    doWifiScan(0, nullptr);
#endif

  } else if (cmd == "id") {
    TRY_LOCK(BufferedStreamJoiner,
      put(deviceId());
    ,);

  } else if (cmd == "reset" || cmd == "restart" || cmd == "reboot") {
    Device.die("Device reset requested", RST_RESET_BY_COMMAND, 750);

  } else if (cmd == "hard reset") {
    DevicePlugin::hard_reset(RST_RESET_BY_COMMAND);

  } else if (cmd == "cpu") {
    printCpuStats(0, nullptr);

  } else if (cmd == "profile") {
    TRY_LOCK(BufferedStreamJoiner,
             put(StreamProfile(App.profile));
    ,);

  } else if (cmd == "find profile") {
    TRY_LOCK(BufferedStreamJoiner,
             findProfile();
             put(StreamProfile(App.profile));
    ,);

  } else {
    return false;
  }

  return true;
}

int CommandPlugin::printCpuStats(int argc, char **argv) {
  BufferedStreamJoiner.lock();
  TaskStatus_t *pxTaskStatusArray;
  volatile UBaseType_t uxArraySize, x;
  BaseType_t xCoreID;
  uint32_t ulTotalRunTime;
  double flTotalRunTime;
  double flStatsAsPercentage;

  // Take a snapshot of the number of tasks in case it changes while this
  // function is executing.
  uxArraySize = uxTaskGetNumberOfTasks();
  putValf(16, "Task Count", "%u", uxArraySize);

  // Allocate a TaskStatus_t structure for each task.  An array could be
  // allocated statically at compile time.
  pxTaskStatusArray = (TaskStatus_t *) pvPortMalloc(uxArraySize * sizeof(TaskStatus_t));

  if (pxTaskStatusArray != nullptr) {
    // Generate raw status information about each task.
    uxArraySize = uxTaskGetSystemState(pxTaskStatusArray, uxArraySize, &ulTotalRunTime);

    putValf(16, "Total Runtime", "%10u", ulTotalRunTime);
    // For percentage calculations.
    flTotalRunTime = (double) (ulTotalRunTime / 100UL);
    // Avoid divide by zero errors.
    if (flTotalRunTime > 0) {
      // For each populated position in the pxTaskStatusArray array,
      // format the raw data as human readable ASCII data
      put(DIM("┌────────────────┬────────────┬──────┬─────────────┐"));
      putf(DIV_S BOLD("%14s") DIV BOLD("%10s") DIV BOLD("%4s") DIV BOLD("%11s") DIV_E,
          "Name", "Ticks", "Core", "Utilization");
      for (x = 0; x < uxArraySize; ++x) {
        if (pxTaskStatusArray[x].uxCurrentPriority > 0) {
          // idle tasks have priority 0
          continue;
        }
        // What percentage of the total run time has the task used?
        // This will always be rounded down to the nearest integer.
        // ulTotalRunTimeDiv100 has already been divided by 100.
        flStatsAsPercentage = (double) pxTaskStatusArray[x].ulRunTimeCounter / flTotalRunTime;
        xCoreID = pxTaskStatusArray[x].xCoreID;
        put(DIM("├────────────────┼────────────┼──────┼─────────────┤"));
        putf(DIV_S
        BOLD("%14s")
        DIV
        "%10u"
        DIV
        "%4s"
        DIV
        "%9.2f %%"
        DIV_E,
            pxTaskStatusArray[x].pcTaskName,
            pxTaskStatusArray[x].ulRunTimeCounter,
            xCoreID == CORE_0 ? "0" : "1",
            100.0 - flStatsAsPercentage);
      }
      put(DIM("└────────────────┴────────────┴──────┴─────────────┘"));
    }
    // The array is no longer needed, free the memory it consumes.
    vPortFree(pxTaskStatusArray);
  } else {
    putErr("pxTaskStatusArray is nullptr!");
  }
  BufferedStreamJoiner.unlock();
  return ESP_OK;
}

int CommandPlugin::printRTOS(int argc, char **argv) {
  BufferedStreamJoiner.lock();
  TaskStatus_t *pxTaskStatusArray;
  volatile UBaseType_t uxArraySize, x;
  BaseType_t xCoreID;
  uint32_t ulTotalRunTime;
  double flTotalRunTime;
  double flStatsAsPercentage;

  // Take a snapshot of the number of tasks in case it changes while this
  // function is executing.
  uxArraySize = uxTaskGetNumberOfTasks();
  putValf(16, "Task Count", "%u", uxArraySize);

  // Allocate a TaskStatus_t structure for each task.  An array could be
  // allocated statically at compile time.
  pxTaskStatusArray = (TaskStatus_t*)pvPortMalloc(uxArraySize * sizeof(TaskStatus_t));

  if (pxTaskStatusArray != nullptr) {
    // Generate raw status information about each task.
    uxArraySize = uxTaskGetSystemState(pxTaskStatusArray, uxArraySize, &ulTotalRunTime);

    putValf(16, "Total Runtime", "%10u", ulTotalRunTime);
    // For percentage calculations.
    flTotalRunTime = (double)(ulTotalRunTime / 100UL);
    // Avoid divide by zero errors.
    if (flTotalRunTime > 0) {
      // For each populated position in the pxTaskStatusArray array,
      // format the raw data as human readable ASCII data
      put(DIM("┌────────────────────┬────────────┬──────┬──────────┬────────────┬──────────┬─────────────┐"));
      putf(DIV_S BOLD("%18s") DIV BOLD("%10s") DIV BOLD("%4s") DIV BOLD("%8s") DIV BOLD("%10s") DIV BOLD("%8s") DIV BOLD("%11s") DIV_E,
          "Name", "Ticks", "Core", "Priority", "State", "Free", "Utilization");
      for (x = 0; x < uxArraySize; x++) {
        // What percentage of the total run time has the task used?
        // This will always be rounded down to the nearest integer.
        // ulTotalRunTimeDiv100 has already been divided by 100.
        flStatsAsPercentage = (double)pxTaskStatusArray[x].ulRunTimeCounter / flTotalRunTime;
        xCoreID = pxTaskStatusArray[x].xCoreID;
        put(DIM("├────────────────────┼────────────┼──────┼──────────┼────────────┼──────────┼─────────────┤"));
        putf(DIV_S BOLD("%18s") DIV "%10u" DIV "%4s" DIV "%8u" DIV "%10s" DIV "%5.2f KB" DIV "%9.2f %%" DIV_E,
            pxTaskStatusArray[x].pcTaskName,
            pxTaskStatusArray[x].ulRunTimeCounter,
            xCoreID == tskNO_AFFINITY ? "-" : xCoreID == CORE_0 ? "0" : "1",
            pxTaskStatusArray[x].uxCurrentPriority,
            taskStateString(pxTaskStatusArray[x].eCurrentState),
            pxTaskStatusArray[x].usStackHighWaterMark / 1024.0,
            flStatsAsPercentage);
      }
      put(DIM("└────────────────────┴────────────┴──────┴──────────┴────────────┴──────────┴─────────────┘"));
    }
    // The array is no longer needed, free the memory it consumes.
    vPortFree(pxTaskStatusArray);
  } else {
    putErr("pxTaskStatusArray is nullptr!");
  }
  BufferedStreamJoiner.unlock();
  return ESP_OK;
}

int CommandPlugin::printVersion(int argc, char **argv) {
  TRY_LOCK(BufferedStreamJoiner,
    putStringVal(17, "Software version", SOFTWARE_VERSION);
    putStringVal(17, "Software revision", SOFTWARE_REVISION);
  ,);
  return ESP_OK;
}

#if CONFIG_ENABLE_WIFI_SCAN_PLUGIN
int CommandPlugin::doWifiScan(int argc, char **argv) {
  put("Scanning for wifi networks on all channels...");
  WifiScanner.scanChannel(0, false);
  return ESP_OK;
}
#endif

int CommandPlugin::printHeapStats(int argc, char **argv) {
  TRY_LOCK(BufferedStreamJoiner,
    put(heap_caps_get_free_size(MALLOC_CAP_INTERNAL));
    bool valid = heap_caps_check_integrity(MALLOC_CAP_INTERNAL, true);
    put((valid ? "valid heap" : "heap errors found!"));
    if (valid) {
      multi_heap_info_t info;
      heap_caps_get_info(&info, MALLOC_CAP_INTERNAL);
      size_t total = info.total_free_bytes + info.total_allocated_bytes;

      put(DIM("-- Heap Stats --"));
      putValf(12, "Free Bytes", "%3.2f KB (%.1f %%)", info.total_free_bytes / 1024.0, info.total_free_bytes / (float)total * 100.0);
      putValf(12, "Used Bytes", "%3.2f KB (%.1f %%)", info.total_allocated_bytes / 1024.0, info.total_allocated_bytes / (float)total * 100.0);
      putValf(12, "Total Bytes", "%3.2f KB", total / 1024.0);
      putln();
      putValf(12, "Min Free", "%3.2f KB", info.minimum_free_bytes / 1024.0);
      putValf(12, "Max Alloc", "%3.2f KB", info.largest_free_block / 1024.0);
      put(DIM("-- End Heap Stats --"));
    }
  ,);
  return ESP_OK;
}

int CommandPlugin::listPlugins(int argc, char **argv) {
  TRY_LOCK(BufferedStreamJoiner,
    put(DIM("-- Plugins :: " << App.getPlugins().size()  << " Total Plugins --"));
    for (auto & plugin : App.getPlugins()) {
      put(plugin->name);
    }
    put(DIM("-- End Plugins --"));
  ,);
  return ESP_OK;
}

int CommandPlugin::listTasks(int argc, char **argv) {
  TRY_LOCK(BufferedStreamJoiner,
    put(DIM("┌────────────────────┬──────────────────┬──────────────────┬───────────┬────────────┬──────────┐"));
    putf(DIV_S BOLD("%18s") DIV BOLD("%16s") DIV BOLD("%16s") DIV BOLD("%9s") DIV BOLD("%10s") DIV BOLD("%8s") DIV_E,
        "Name", "Free", "Used", "Interval", "Iterations", "Priority");

    for (auto &task : App.getTasks()) {
      if (task->_deleted) {
        continue;
      }
      UBaseType_t hw = uxTaskGetStackHighWaterMark(task->_handle);
      put(DIM("├────────────────────┼──────────────────┼──────────────────┼───────────┼────────────┼──────────┤"));
      putf(DIV_S BOLD("%18s") DIV "%4.2f KB" DIM(" (%4.1f %%)") DIV "%4.2f KB" DIM(" (%4.1f %%)") DIV "%6d ms" DIV "%10d" DIV "%8d" DIV_E,
          task->getName().c_str(),
          hw / 1024.0,
          hw * 100.0 / task->getStackSize(),
          (task->getStackSize() - hw) / 1024.0,
          (task->getStackSize() - hw) * 100.0 / task->getStackSize(),
          task->getInterval(),
          task->getIterations(),
          task->_priority);
    }
    put(DIM("└────────────────────┴──────────────────┴──────────────────┴───────────┴────────────┴──────────┘"));
  ,);
  return ESP_OK;
}

bool CommandPlugin::handleMqttMessage(const char *topic, int id, const char *cmd, const JsonDocument& json) {
  if (Mqtt.topics.command == topic) {
    for (auto & plugin : App.getPlugins()) {
      if (plugin->handleCommand(cmd)) {
        LOGV(TAG, "command was handled by " << plugin->name);
        Mqtt.respondTrue(id);
        return true;
      }
    }

    LOGW(TAG, "command was unhandled: '" << cmd << "'");
  }

  return false;
}

void CommandPlugin::onMqttConnected() {
  Mqtt.subscribe(Mqtt.topics.command.c_str());
}

#endif // CONFIG_ENABLE_COMMANDS_PLUGIN
