#pragma once
#include "sdkconfig.h"
#include "loglevels.h"

#include <Arduino.h>
#include <Esp.h>
#include <Streaming.h>

#include "util/helpers.h"
#include "esp_log.h"

#include "streams/BufferedStreamJoiner.h"
#include "rtos/lock_macros.h"

#define LOG_COLOR_GRAY    "37"
#define LOG_COLOR_WHITE   "38"

#undef LOG_COLOR_D
#undef LOG_COLOR_V
#define LOG_COLOR_D  LOG_COLOR(LOG_COLOR_GRAY)
#define LOG_COLOR_V  LOG_COLOR(LOG_COLOR_GRAY)

#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

#define _errorLine "********************************************************************************************************************************************************************"

#define DIM_COLOR LOG_COLOR(LOG_COLOR_BLACK)
#define BOLD_STYLE "\033[1m"
#define DIM_STYLE "\033[2m"
#define NORMAL_STYLE "\033[22;24m"

#define BOLD(str) BOLD_STYLE str NORMAL_STYLE
#define DIM(str) DIM_STYLE str NORMAL_STYLE

#define DIV_S DIM("│ ")
#define DIV   DIM(" │ ")
#define DIV_E DIM(" │")

#define _doStreamLog(StreamObject, VerboseStream, level, color, tag, stream) \
  StreamObject << color << \
  DIM_STYLE "[" << level << "]" << \
  " | " << millis(); \
  VerboseStream << \
  " | " << deviceId() << \
  " | Core " << xPortGetCoreID() << \
  " | " << heap_caps_get_free_size(MALLOC_CAP_INTERNAL); \
  StreamObject << \
  " | " NORMAL_STYLE << color << tag << \
  DIM(" | ") << color << stream << LOG_RESET_COLOR << endl

#if CONFIG_ENABLE_WEBSOCKET_SERVER_PLUGIN && CONFIG_FORWARD_APP_LOGS_TO_WEBSOCKET
#include "WebSocketServerPlugin.h"
#define _streamLog(level, color, tag, stream) \
  TRY_LOCK(BufferedStreamJoiner, \
    _doStreamLog(BufferedStreamJoiner, Serial, level, color, tag, stream),)
#define PUTLN(streamMsg) TRY_LOCK(BufferedStreamJoiner, BufferedStreamJoiner << streamMsg << LOG_RESET_COLOR << endl,)
#define PUTS(streamMsg) TRY_LOCK(BufferedStreamJoiner, BufferedStreamJoiner << streamMsg,)
#else
#define _streamLog(level, color, tag, stream) _doStreamLog(Serial, Serial, level, color, tag, stream)
#define PUTLN(stream) Serial << stream << LOG_RESET_COLOR << endl
#define PUTS(stream) Serial << stream
#endif

#if CONFIG_BIRD_IOT_LOG_LEVEL >= LOG_LEVEL_VERBOSE
#define LOGV(tag, stream) _streamLog("V", LOG_COLOR_V, tag, stream)
#else
#define LOGV(tag, stream)
#endif

#if CONFIG_BIRD_IOT_LOG_LEVEL >= LOG_LEVEL_DEBUG
#define LOGD(tag, stream) _streamLog("D", LOG_COLOR_D, tag, stream)
#else
#define LOGD(tag, stream)
#endif

#if CONFIG_BIRD_IOT_LOG_LEVEL >= LOG_LEVEL_INFO
#define LOGI(tag, stream) _streamLog("I", LOG_COLOR_I, tag, stream)
#else
#define LOGI(tag, stream)
#endif

#if CONFIG_BIRD_IOT_LOG_LEVEL >= LOG_LEVEL_WARN
#define LOGW(tag, stream) _streamLog("W", LOG_COLOR_W, tag, stream)
#else
#define LOGW(tag, stream)
#endif

#if CONFIG_BIRD_IOT_LOG_LEVEL >= LOG_LEVEL_ERROR
#define LOGE(tag, stream) _streamLog("E", LOG_COLOR_E, tag, stream)
#else
#define LOGE(tag, stream)
#endif

#if CONFIG_BIRD_IOT_LOG_LEVEL > LOG_LEVEL_NONE
#define LOGA(tag, stream) _streamLog("A", LOG_COLOR(LOG_COLOR_WHITE), tag, stream)
#else
#define LOGA(tag, stream)
#endif