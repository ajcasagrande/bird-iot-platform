#include "tasks/TaskClass.h"

#include "sdkconfig.h"
#include "include/builtin.h"
#include "IotApp.h"
#include "SecureOTAPlugin.h"
#include "include/rtos.h"
#include "include/logging.h"

static const char* TAG = "TaskClass";

static void __attribute__ ((noreturn)) _task(void *pvParameter) {
  auto t = reinterpret_cast<TaskClass*>(pvParameter);

  if (t->_initialDelay == -1) {
    // random initial delay to offset tasks
    // randDelay = 2/3 interval + rand( 0 .. 1/3 interval )
    long randMax = (double)(t->_interval) / 3;
    t->_initialDelay = random(randMax) + (t->_interval - randMax);
  }
  if (t->_initialDelay > 0) {
    taskDELAY(t->_initialDelay);
  }

  if (t->useExactTiming()) {
    TickType_t xLastWakeTime = xTaskGetTickCount();

    while(true) {
      t->_executeIfAllowed();

      if (t->_interval > 0) {
        vTaskDelayUntil(&xLastWakeTime, uxTicks(t->_interval));
      } else {
        taskYIELD();
      }
    }
  } else {
    while(true) {
      t->_executeIfAllowed();

      if (t->_interval > 0) {
        taskDELAY(t->_interval);
      } else {
        taskYIELD();
      }
    }
  }
}

void inline TaskClass::_executeIfAllowed() {
  if (!_paused
#if CONFIG_ENABLE_SECURE_OTA_PLUGIN
         && (_allowDuringOTA || !SecureOTA.isInProgress())
#endif
  ) {
    ++_iterations;
    execute();

    if (_singleShot) {
      remove();
    }
  }
}

bool TaskClass::configure(uint32_t interval, uint32_t stackSize, portBASE_TYPE priority, BaseType_t coreId, bool useExact, bool allowDuringOTA, int initialDelay) {
  if (started()) {
    return false;
  }

  setInterval(interval);
  setStackSize(stackSize);
  setPriority(priority);
  setCoreId(coreId);
  setUseExactTiming(useExact);
  setAllowedDuringOTA(allowDuringOTA);
  setInitialDelay(initialDelay);
  return true;
}

bool TaskClass::fireSingleShot(int initialDelay) {
  _initialDelay = initialDelay;
  _singleShot = true;
  _interval = 0;
  return start();
}

bool TaskClass::start() {
  if (started()) {
    return false;
  }

  App.registerTask(this);
  LOGI(TAG, "starting task: " << _name << ", core: " << (_coreId == tskNO_AFFINITY ? -1 : _coreId));
  _started = (xTaskCreatePinnedToCore(&_task, _name.c_str(), _stackSize, this, _priority, &_handle, _coreId) == pdPASS);
  return _started;
}

bool TaskClass::pause() {
  if (_deleted || !_started) {
    return false;
  }
  if (!_paused) {
    _paused = true;
    vTaskSuspend(_handle);
  }
  return true;
}

bool TaskClass::resume() {
  if (_deleted || !_started) {
    return false;
  }
  if (_paused) {
    _paused = false;
    vTaskResume(_handle);
  }
  return true;
}

bool TaskClass::remove() {
  if (_deleted || !_started) {
    return false;
  }
  _deleted = true;
  _started = false;
  _paused = false;
  vTaskDelete(_handle);
  taskYIELD();
  return true;
}

bool TaskClass::setCoreId(BaseType_t coreId) {
  if (started()) {
    return false;
  }
  _coreId = coreId;
  return true;
}

bool TaskClass::setStackSize(uint32_t stackSize) {
  if (started()) {
    return false;
  }
  _stackSize = stackSize;
  return true;
}

bool TaskClass::setPriority(portBASE_TYPE priority) {
  if (started()) {
    vTaskPrioritySet(_handle, priority);
  }
  _priority = priority;
  return true;
}
