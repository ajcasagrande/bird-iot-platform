#pragma once
#include "sdkconfig.h"

#if CONFIG_ENABLE_GPS_PLUGIN
#include "include/common.h"
#include "CircularBuffer.h"
#include <TinyGPS++.h>
#include "gps_commands.h"

class GpsPlugin;

#if CONFIG_ENABLE_TFT_DISPLAY
#include "tft_includes.h"
#include <dejavu_sans.h>

extern DisplayManager GpsDisplay;

class SpeedFrame : public StringDrawable<GpsPlugin> {
public:
  explicit SpeedFrame(GpsPlugin *plugin);
  void updateCurrent() override;
  StringRenderInfo getRenderInfo(TFT_eSPI *img, DisplayUI& ui, int16_t textWidth) override;
};

class MaxSpeedOverlay : public StringDrawable<GpsPlugin> {
public:
  explicit MaxSpeedOverlay(GpsPlugin *plugin);
  void updateCurrent() override;
  StringRenderInfo getRenderInfo(TFT_eSPI *img, DisplayUI& ui, int16_t textWidth) override;
};

class SatelliteOverlay : public StringDrawable<GpsPlugin> {
public:
  explicit SatelliteOverlay(GpsPlugin *plugin);
  void updateCurrent() override;
  StringRenderInfo getRenderInfo(TFT_eSPI *img, DisplayUI& ui, int16_t textWidth) override;
};

class LatOverlay : public StringDrawable<GpsPlugin> {
public:
  explicit LatOverlay(GpsPlugin *plugin);
  void updateCurrent() override;
  StringRenderInfo getRenderInfo(TFT_eSPI *img, DisplayUI& ui, int16_t textWidth) override;
};

class LonOverlay : public StringDrawable<GpsPlugin> {
public:
  explicit LonOverlay(GpsPlugin *plugin);
  void updateCurrent() override;
  StringRenderInfo getRenderInfo(TFT_eSPI *img, DisplayUI& ui, int16_t textWidth) override;
};

#endif

class GpsPlugin : public IotPlugin {
private:
  HardwareSerial *gpsSerial;
  Task<GpsPlugin> *pollTask;
  Task<GpsPlugin> *refreshTask;

public:
  GpsPlugin();

  bool setup() override;
  bool start() override;
  void poll();
  void render();

  TinyGPSPlus gps;

  double maxSpeed = -1;
  CircularBuffer<double> speeds = CircularBuffer<double>(CONFIG_GPS_UPDATE_RATE_HZ * 3);

#if CONFIG_ENABLE_TFT_DISPLAY
  SpeedFrame speedFrame;
  MaxSpeedOverlay maxSpeedOverlay;
  SatelliteOverlay satOverlay;
  LatOverlay latOverlay;
  LonOverlay lonOverlay;
#endif

  void sendUBX(const unsigned char *progmemBytes, size_t len);
  void setUpdateRate();

  bool handleCommand(const std::string& cmd) override;
};

#endif
