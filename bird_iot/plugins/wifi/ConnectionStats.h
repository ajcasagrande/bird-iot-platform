#pragma once

#include "include/builtin.h"

class ConnectionStats {
private:
  uint64_t _downtime = 0;
  uint64_t _uptime = 0;

public:
  uint64_t lastConnection = 0;
  uint64_t lastDrop = 0;
  uint32_t firstConnection = 0;
  uint16_t drops = 0;
  uint16_t connects = 0;
  bool connected = false;
  const char* name;

  explicit ConnectionStats(const char* name) : name(name) { }
  void onConnect();
  void onDisconnect();
  uint64_t downtime();
  uint64_t uptime();
  bool publishStats(const char* topic);
  void printStats();
  uint64_t averageUptime();
  uint64_t averageDowntime();

};