#include "util/helpers.h"

#include <esp32/rom/rtc.h>
#include <esp_adc_cal.h>
#include <sstream>
#include "include/times.h"
#include "colors.h"
#include "AXP192Sensor.h"

#include "include/common.h"

static const char* TAG = "helpers";

bool verifyHeap() {
  bool valid = heap_caps_check_integrity(MALLOC_CAP_INTERNAL, true);
  if (!valid) {
    LOGE(TAG, "heap integrity check failed!");
  }
  return valid;
}

const char* taskStateString(eTaskState state) {
  switch (state) {
    case eRunning:    return "Running";
    case eReady:      return "Active";
    case eBlocked:    return "Idle";
    case eSuspended:  return "Suspended";
    case eDeleted:    return "Deleted";
    default:          return "Unknown";
  }
}

double roundTo(double val, int places) {
  return round(val * pow(10, places)) / pow(10.0, places);
}

const char* deviceId() {
  static const char* devId = nullptr;
  if (devId == nullptr) {
    size_t len = strlen(CONFIG_DEVICE_ID_PREFIX) + 8;
    char* tempId = (char*) malloc(len * sizeof(char));
    uint32_t mac = (ESP.getEfuseMac() >> 24) & 0xffffff;
    xsnprintf(tempId, len, "%s-%02x%02x%02x", CONFIG_DEVICE_ID_PREFIX, (mac & 0xff), ((mac >> 8) & 0xff),
              ((mac >> 16) & 0xff));
    devId = tempId;
  }
  return devId;
}

uint64_t millis64() {
  static uint32_t low32, high32;
  
  uint32_t now = millis();
  if (now < low32) {
    high32++;
  }
  low32 = now;
  
  return ((uint64_t)high32 << 32) | low32;
}

bool isPin(pin_t p) {
  return p != NOT_A_PIN;
}

bool isPin(gpio_num_t g) {
  return GPIO_IS_VALID_GPIO(g);
}

// convert sizes in bytes to KB and MB
String formatBytes(size_t bytes) {
  if (bytes < 1024) {
    return String(bytes) + " B";
  } else if (bytes < (1024 * 1024)) {
    return String(bytes / 1024.0) + " KB";
  } else {
    return String(bytes / 1024.0 / 1024.0) + " MB";
  }
}

// convert sizes in bytes to KB and MB
char formatBytesStream(size_t bytes) {
  if (bytes < 1024) {
    Serial << bytes << " B";
  } else if (bytes < (1024 * 1024)) {
    Serial << bytes / 1024.0 << " KB";
  } else {
    Serial << bytes / 1024.0 / 1024.0 << " MB";
  }
  return ' ';
}

double readVcc() {
#if CONFIG_ADC_PIN > 0
  static uint32_t vref = 0;
  if (vref == 0) {
    vref = readVref();
  }
  uint16_t v = analogRead(CONFIG_ADC_PIN);
  double vbat = (v / 4095.0) * 2.0 * 3.3 * (vref / 1000.0);
  LOGV(TAG, "voltage: " << vbat);
  return vbat;
#elif CONFIG_ENABLE_AXP192_SENSOR
  if (AXP192Sensor.present()) {
    return AXP192Sensor.getVcc();
  }
#endif
  LOGW(TAG, "CONFIG_ADC_PIN and CONFIG_ENABLE_AXP192_SENSOR are not defined, unable to read voltage");
  return 0.0;
}

uint32_t readVref() {
  const static uint32_t defaultVref = 1100;

  esp_adc_cal_characteristics_t adc_chars;
  esp_adc_cal_value_t val_type = esp_adc_cal_characterize((adc_unit_t)ADC_UNIT_1, (adc_atten_t)ADC1_CHANNEL_6, (adc_bits_width_t)ADC_WIDTH_BIT_12, 1100, &adc_chars);
  // Check type of calibration value used to characterize ADC
  if (val_type == ESP_ADC_CAL_VAL_EFUSE_VREF) {
    LOGI(TAG, "eFuse Vref: " << adc_chars.vref << " mV");
    return adc_chars.vref;
  } else if (val_type == ESP_ADC_CAL_VAL_EFUSE_TP) {
    LOGI(TAG, "Two Point --> coeff_a: " << adc_chars.coeff_a << " mV coeff_b: " << adc_chars.coeff_b << " mV");
    return defaultVref;
  } else {
    LOGI(TAG, "Default Vref: 1100mV");
    return defaultVref;
  }
}

uint32_t since(uint32_t ms) {
  return millis() - ms;
}

uint64_t since64(uint64_t ms) {
  return millis64() - ms;
}

float ctof(float c) {
  return c * 1.8 + 32.0;
}

JsonDocument parseJsonMessage(char* message, int len) {
  // Use DynamicJsonDocument because we want to pass it around
  DynamicJsonDocument json(len * 10);

  auto error = deserializeJson(json, message);
  if (error) {
    LOGE(TAG, "deserializeJson() failed with code " << error.c_str());
  }

  return std::move(json);
}

const char* getWakeupReason() {
  switch (rtc_get_wakeup_cause()) {
    case NO_SLEEP:        return "No Sleep";
    case EXT_EVENT0_TRIG: return "External Event 0";
    case EXT_EVENT1_TRIG: return "External Event 1";
    case GPIO_TRIG:       return "GPIO";
    case TIMER_EXPIRE:    return "Wakeup Timer";
    case SDIO_TRIG:       return "SDIO";
    case MAC_TRIG:        return "MAC";
    case UART0_TRIG:      return "UART0";
    case UART1_TRIG:      return "UART1";
    case TOUCH_TRIG:      return "Touch";
    case SAR_TRIG:        return "SAR";
    case BT_TRIG:         return "BT";
    default:              return "Unknown";
  }
}

const char* getResetReason(int cpuCore) {
  switch (rtc_get_reset_reason(cpuCore)) {
    case POWERON_RESET:           return "Power On Reset";
    case SW_RESET:                return "Software Reset Digital Core";
    case OWDT_RESET:              return "Watch Dog Reset Digital Core";
    case DEEPSLEEP_RESET:         return "Deep Sleep Reset Digital Core";
    case SDIO_RESET:              return "SLC Module Reset Digital Core";
    case TG0WDT_SYS_RESET:        return "Timer Group 0 Watch Dog Reset Digital Core";
    case TG1WDT_SYS_RESET:        return "Timer Group 1 Watch Dog Reset Digital Core";
    case RTCWDT_SYS_RESET:        return "RTC Watch Dog Reset Digital Core";
    case INTRUSION_RESET:         return "Intrusion Reset CPU";
    case TGWDT_CPU_RESET:         return "Timer Group Reset CPU";
    case SW_CPU_RESET:            return "Software Reset CPU";
    case RTCWDT_CPU_RESET:        return "RTC Watch Dog Reset CPU";
    case EXT_CPU_RESET:           return "External CPU Reset";
    case RTCWDT_BROWN_OUT_RESET:  return "Voltage Unstable Reset";
    case RTCWDT_RTC_RESET:        return "RTC Watch Dog Reset Digital Core And RTC Module";
    default:                      return "Unknown Reset Reason";
  }
}

const char* getEspResetReason() {
  auto ownReason = (birdiot_reset_reason_t)Prefs.getAndClearResetReason();
  switch (ownReason) {
    case RST_RESET_BY_COMMAND:    return "Reset by user command";
    case RST_OTA_RTOS_TASK:       return "Unable to start OTA RTOS task";
    case RST_OTA_FAILURE:         return "Reset due to OTA Failure";
    case RST_OTA_DEADMANS_SWITCH: return "Reset by OTA Deadman's Switch";
    case RST_OTA_COMPLETE:        return "Reset due to Successful OTA";
    case RST_WIFI_WATCHDOG:       return "Reset due to WiFi watchdog timeout";
    case RST_MQTT_WATCHDOG:       return "Reset due to MQTT watchdog timeout";
    case RST_MQTT_SUB_WATCHDOG:   return "Reset due to MQTT subscription watchdog timeout";

    case RST_UNKNOWN:
    default:                      break;
  }
  switch (esp_reset_reason()) {
    case ESP_RST_POWERON:     return "Reset due to power-on event";
    case ESP_RST_EXT:         return "Reset by external pin (not applicable for ESP32)";
    case ESP_RST_SW:          return "Generic Software reset";
    case ESP_RST_PANIC:       return "Software reset due to exception/panic";
    case ESP_RST_INT_WDT:     return "Reset (software or hardware) due to interrupt watchdog";
    case ESP_RST_TASK_WDT:    return "Reset due to task watchdog";
    case ESP_RST_WDT:         return "Reset due to other watchdogs";
    case ESP_RST_DEEPSLEEP:   return "Reset after exiting deep sleep mode";
    case ESP_RST_BROWNOUT:    return "Brownout reset (software or hardware)";
    case ESP_RST_SDIO:        return "Reset over SDIO";

    case ESP_RST_UNKNOWN:
    default:                  return "Reset reason can not be determined";
  }
}

String chipFeaturesToString(uint32_t features) {
  String f;
  if (features & CHIP_FEATURE_EMB_FLASH) {
    f += "EMB_FLASH,";
  }
  if (features & CHIP_FEATURE_WIFI_BGN) {
    f += "WIFI_BGN,";
  }
  if (features & CHIP_FEATURE_BLE) {
    f += "BLE,";
  }
  if (features & CHIP_FEATURE_BT) {
    f += "BT,";
  }
  f.remove(f.length() - 1);

  return f;
}

void disableBrownoutDetector() {
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0);
}

void enableBrownoutDetector() {
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 1);
}

void simpleHexFormat(char* buff, uint32_t val, uint8_t bits, bool prefix, bool uppercase) {
  static const char* _digitsLower = "0123456789abcdef";
  static const char* _digitsUpper = "0123456789ABCDEF";

  char *ptr = buff;
  if (prefix) {
    buff[0] = '0';
    buff[1] = 'x';
    ptr += 2;
  }

  const char* digits = uppercase ? _digitsUpper : _digitsLower;

  uint32_t divisor, rem = 0;

  for (int i = bits-1; i > 0; --i) {
    divisor = 1 << (4 * i);
    if (divisor == 0) {
      LOGE(TAG, "divisor was 0! " << i << " " << bits << " " << divisor << " " << rem << " " << val);
      return;
    }
    rem = val % divisor;
    if (rem == val) {
      *ptr++ = '0';
    } else {
      *ptr++ = digits[val / divisor];
      val = rem;
    }
  }
  *ptr++ = digits[val];
  *ptr = '\0';
}

uint16_t randomColor() {
  return color565(random(255), random(255), random(255));
}

std::string prettyDuration(uint64_t ms) {
  std::ostringstream sbuf;
  uint64_t _ms = ms;

  if (_ms == 0) {
    sbuf << 0 << "ms";
  }

  int days = (int)(_ms / MS_PER_DAY);
  if (days > 0) {
    sbuf << days << "d ";
    _ms = _ms % MS_PER_DAY;
  }

  int hours = (int)(_ms / MS_PER_HOUR);
  if (hours > 0) {
    sbuf << hours << "h ";
    _ms = _ms % MS_PER_HOUR;
  }

  int minutes = (int)(_ms / MS_PER_MINUTE);
  if (minutes > 0) {
    sbuf << minutes << "m ";
    _ms = _ms % MS_PER_MINUTE;
  }

  int seconds = (int)(_ms / MS_PER_SECOND);
  if (seconds > 0) {
    sbuf << seconds << "s ";
    _ms = _ms % MS_PER_SECOND;
  }

  if (_ms > 0) {
    sbuf << _ms << "ms";
  }

  return sbuf.str();
}

const char *authModeStr(wifi_auth_mode_t authMode) {
  switch (authMode) {
    case WIFI_AUTH_OPEN:            return "OPEN";
    case WIFI_AUTH_WEP:             return "WEP";
    case WIFI_AUTH_WPA_PSK:         return "WPA_PSK";
    case WIFI_AUTH_WPA2_PSK:        return "WPA2_PSK";
    case WIFI_AUTH_WPA_WPA2_PSK:    return "WPA_WPA2_PSK";
    case WIFI_AUTH_WPA2_ENTERPRISE: return "WPA2_ENTERPRISE";
    default:                        return "UNKNOWN";
  }
}

const char *cipherTypeStr(wifi_cipher_type_t cipherType) {
  switch (cipherType) {
    case WIFI_CIPHER_TYPE_NONE:       return "NONE";
    case WIFI_CIPHER_TYPE_WEP40:      return "WEP40";
    case WIFI_CIPHER_TYPE_WEP104:     return "WEP104";
    case WIFI_CIPHER_TYPE_TKIP:       return "TKIP";
    case WIFI_CIPHER_TYPE_CCMP:       return "CCMP";
    case WIFI_CIPHER_TYPE_TKIP_CCMP:  return "TKIP_CCMP";
    case WIFI_CIPHER_TYPE_UNKNOWN:    return "UNKNOWN";
    default:                          return "UNKNOWN";
  }
}


const char *channelWidthStr(wifi_second_chan_t chan) {
  switch (chan) {
    case WIFI_SECOND_CHAN_NONE:       return "HT20";
    case WIFI_SECOND_CHAN_ABOVE:      return "HT40";
    case WIFI_SECOND_CHAN_BELOW:      return "HT40";
    default:                          return "UNKNOWN";
  }
}

void tokenize(std::string const &str, const char delimiter, std::vector<std::string> &out) {
  size_t start;
  size_t end = 0;

  while ((start = str.find_first_not_of(delimiter, end)) != std::string::npos)
  {
    end = str.find(delimiter, start);
    out.push_back(str.substr(start, end - start));
  }
}
