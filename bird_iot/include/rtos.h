#pragma once
#include "sdkconfig.h"

#if CONFIG_FREERTOS_HZ == 1000
#define uxTicks(ms) (ms)
#define uxSecondsTicks(sec) ((sec) * 1000)
#else
#define uxTicks(ms) ((ms) / CONFIG_FREERTOS_HZ * 1000)
#define uxSecondsTicks(sec) ((sec) / CONFIG_FREERTOS_HZ)
#endif

#define CORE_0 (0)
#if portNUM_PROCESSORS > 1
#define CORE_1 (1)
#else
#define CORE_1 (0)
#endif

#define taskDELAY(ms) vTaskDelay(uxTicks(ms))

