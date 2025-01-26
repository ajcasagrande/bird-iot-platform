#pragma once

#include <string>
#include <vector>
#include <Arduino.h>
#include <ArduinoJson.h>
#include <esp_wifi_types.h>
#include "include/my_types.h"

#define getOrDefaultJsonProperty(outVal, key, defaultVal) outVal = defaultVal; if (json.containsKey(key)) { outVal = json[key]; }
#define getJsonPropertyOrReturnValue(outVal, key, returnVal) if (!json.containsKey(key)) { LOGE(TAG, "json payload missing required property: " << key); return returnVal; } outVal = json[key]
#define getJsonPropertyOrReturnVoid(outVal, key) getJsonPropertyOrReturnValue(outVal, key,)
// #define getJsonProperty(outVal, key) outVal = json[key]
#define getJsonProperty(outVal, key) getJsonPropertyOrReturnValue(outVal, key, false)
#define tryGetJsonProperty(outVal, key) getJsonPropertyOrReturnValue(outVal, key, false)

bool verifyHeap();
const char* taskStateString(eTaskState state);
double roundTo(double, int);
const char* deviceId();
uint64_t millis64();
bool isPin(pin_t p);
bool isPin(gpio_num_t g);
String formatBytes(size_t bytes);
double readVcc();
uint32_t readVref();
uint32_t since(uint32_t ms);
uint64_t since64(uint64_t ms);
float ctof(float c);
JsonDocument parseJsonMessage(char* message, int len);
String chipFeaturesToString(uint32_t features);
const char* getWakeupReason();
const char* getResetReason(int cpuCore);
const char* getEspResetReason();
void disableBrownoutDetector();
void enableBrownoutDetector();

void simpleHexFormat(char* buff, uint32_t val, uint8_t bits, bool prefix=true, bool uppercase=false);
char formatBytesStream(size_t bytes);
uint16_t randomColor();
std::string prettyDuration(uint64_t ms);

const char* authModeStr(wifi_auth_mode_t authMode);
const char* cipherTypeStr(wifi_cipher_type_t cipherType);
const char *channelWidthStr(wifi_second_chan_t chan);

void tokenize(std::string const &str, char delimiter, std::vector<std::string> &out);
