#include "SpektrumDeviceMode.h"

#include "sdkconfig.h"
#include "include/builtin.h"
#include "include/logging.h"
#include "IotApp.h"
#include "include/plugins_inc.h"
#include "include/rtos.h"

static const char* TAG = "SpektrumDeviceMode";

SpektrumDeviceModeClass SpektrumDeviceMode;

bool SpektrumDeviceModeClass::activate() {
  LOGW(TAG, "initializing Spektrum Device Mode");
  active = true;

  disableBrownoutDetector();

  App.profile = *findProfile();
  Profile *p = &App.profile;
  verifyHeap();

//  App.registerPlugin(&BufferedStreamJoiner);

#if CONFIG_ENABLE_I2C_SLAVE
  App.registerPlugin(new I2CSlave(p->sdaSlave, p->sclSlave, p->i2cSlaveAddr));
#endif

  bool result = App.setupPlugins();
  result = App.startPlugins() && result;

  LOGI(TAG, "Spektrum Device Mode initialized");
  taskDELAY(5000);
  LOGI(TAG, "re-enabling brownout detector");
  enableBrownoutDetector();
  return result;
}
