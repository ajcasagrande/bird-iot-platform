#include "ConnectionStats.h"

#include "include/logging.h"

//static const char* TAG = "ConnectionStats";

void ConnectionStats::onConnect() {
  uint64_t ms = millis64();
  connected = true;
  ++connects;
  if (firstConnection == 0) {
    firstConnection = ms;
  }
  lastConnection = ms;
  if (lastDrop > 0) {
    _downtime += (ms - lastDrop);
  }
  printStats();
  // publish();
}

void ConnectionStats::onDisconnect() {
  uint64_t ms = millis64();
  ++drops;
  connected = false;
  lastDrop = ms;
  _uptime += (ms - lastConnection);
  printStats();
}

uint64_t ConnectionStats::downtime() {
  return connected ? _downtime : _downtime + since64(lastDrop);
}

uint64_t ConnectionStats::uptime() {
  return connected ? _uptime + since64(lastConnection) : _uptime;
}

bool ConnectionStats::publishStats(const char* topic) {
  // todo
  return false;
}

void ConnectionStats::printStats() {
  LOGD(name, "drops: " << drops << ", uptime: " << prettyDuration(uptime()) << ", downtime: " << prettyDuration(downtime()));
  LOGD(name, "connects: " << connects << ", avg_uptime: " << prettyDuration(averageUptime()) << ", avg_downtime: " << prettyDuration(averageDowntime()));
}

uint64_t ConnectionStats::averageUptime() {
  return connects == 0 ? 0 : uptime() / connects;
}

uint64_t ConnectionStats::averageDowntime() {
  return drops == 0 ? 0 : downtime() / drops;
}
