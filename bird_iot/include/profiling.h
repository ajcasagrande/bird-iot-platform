#pragma once

#include "include/logging.h"
#include "util/helpers.h"

#define PROFILER "Profiler"

//#define PROFILE_MILLIS(name, fn)  { unsigned long _ms = millis(); fn; unsigned long _diff = millis() - _ms; if (_diff > 1) { LOGD(PROFILER, "%s took %lu millis", name, _diff); } }

#define PROFILE_MILLIS(code)  { unsigned long _ms = millis(); code; Serial.print(millis() - _ms); Serial.println(" ms"); }

//#define PROFILE_HEAP_USAGE()
