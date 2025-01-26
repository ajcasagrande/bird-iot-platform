#pragma once

#include "include/macros.h"
#include "DirectStreamJoiner.h"

#define _LOCK_ERR_MSG(msg) Serial << LOG_COLOR_E "ERROR: " << DBG_FILE_LINE << " -- " << msg << endl << LOG_RESET_COLOR

#define TRY_LOCK(clz, successCode, failCode) \
if ((clz).lock()) { \
  successCode; \
  if (!(clz).unlock()) { \
    _LOCK_ERR_MSG("Unable to perform UNLOCK on " #clz "!"); \
  } \
} else { \
   _LOCK_ERR_MSG("Failed to obtain LOCK on " #clz "!"); \
   failCode; \
}
