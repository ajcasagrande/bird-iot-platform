#include "rtos/Lockable.h"

#include "sdkconfig.h"
#include "rtos/lock_macros.h"
#include <esp_log.h>

bool RecursiveLockable::acquire(TickType_t xTicksToWait) {
#if CONFIG_BIRD_IOT_TRACE_LOCKS
  if (traceLocks) {
    Serial << "  Lock: " << (requestor) << endl;
  }
#endif
  TickType_t tLeft = xTicksToWait;
  TickType_t tLoop;
  while (tLeft > 0) {
    tLoop = xTaskGetTickCount();
    if (xSemaphoreTakeRecursive(mutex, 1) == pdTRUE) {
#if CONFIG_BIRD_IOT_TRACE_LOCKS
      if (traceLocks) {
        tLeft -= (xTaskGetTickCount() - tLoop);
        if (tLeft < xTicksToWait) {
          Serial << "  Lock: " << (requestor) << " acquired in " << (xTicksToWait - tLeft) << " ticks" << endl;
        }
      }
#endif
      return true;
    }
    vTaskDelay(min(tLeft, (TickType_t)uxTicks(CONFIG_BIRD_IOT_LOCK_ACQUIRE_INTERVAL)));
    tLeft -= (xTaskGetTickCount() - tLoop);
  }
  return false;
}

bool RecursiveLockable::unlock() {
#if CONFIG_BIRD_IOT_TRACE_LOCKS
  if (traceLocks) {
    Serial << "Unlock: " << (requestor) << endl;
  }
#endif
  return xSemaphoreGiveRecursive(mutex) == pdTRUE;
}

bool ExclusiveLockable::acquire(TickType_t xTicksToWait) {
#if CONFIG_BIRD_IOT_TRACE_LOCKS
  if (traceLocks) {
    Serial << "  Lock: " << (requestor) << endl;
  }
#endif
  TickType_t tLeft = xTicksToWait;
  TickType_t tLoop;
  while (tLeft > 0) {
    tLoop = xTaskGetTickCount();
    if (xSemaphoreTake(mutex, 0) == pdTRUE) {
#if CONFIG_BIRD_IOT_TRACE_LOCKS
      if (traceLocks) {
        tLeft -= (xTaskGetTickCount() - tLoop);
        if (tLeft < xTicksToWait) {
          Serial << "  Lock: " << (requestor) << " acquired in " << (xTicksToWait - tLeft) << " ticks" << endl;
        }
      }
#endif
      return true;
    }
    vTaskDelay(min(tLeft, (TickType_t)uxTicks(CONFIG_BIRD_IOT_LOCK_ACQUIRE_INTERVAL)));
    tLeft -= (xTaskGetTickCount() - tLoop);
  }
  return false;
}

bool ExclusiveLockable::unlock() {
#if CONFIG_BIRD_IOT_TRACE_LOCKS
  if (traceLocks) {
    Serial << "Unlock: " << (requestor) << endl;
  }
#endif
  return xSemaphoreGive(mutex) == pdTRUE;
}
