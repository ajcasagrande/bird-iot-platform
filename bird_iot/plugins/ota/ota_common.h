#pragma once

typedef enum {
  IDLE,
  IN_PROGRESS,
  ERROR,
  COMPLETE
} OTAState;

#define SOFTWARE_CHANNEL_DEV 1
#define SOFTWARE_CHANNEL_BETA 2
#define SOFTWARE_CHANNEL_STABLE 3
#define SOFTWARE_CHANNEL_LTS 4

bool otaInProgress();

void setOtaInFlight(bool value);
bool wasOtaInFlight();
