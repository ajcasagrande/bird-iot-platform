#pragma once

#include "RunMode.h"

class SpektrumDeviceModeClass : public RunMode {
public:
  bool activate() override;
};

extern SpektrumDeviceModeClass SpektrumDeviceMode;
