#pragma once
#include "sdkconfig.h"

#if CONFIG_ENABLE_SECURE_OTA_PLUGIN

#include "include/common.h"
#include <WiFi.h>
#include "esp_partition.h"
#include "esp_ota_ops.h"
#include "esp_https_ota.h"
#include <WiFiClientSecure.h>
#include "Lockable.h"

#if CONFIG_SECURE_OTA_NATIVE_IMPL
class OTAContext : public ExclusiveLockable {
public:
  OTAContext(const esp_partition_t *partition_, const char* expectedSha256_) : partition(partition_), expectedSha256(expectedSha256_) {
    mbedtls_md_init(&digest);
    mbedtls_md_setup(&digest, mbedtls_md_info_from_type(MBEDTLS_MD_SHA256), 0);
    mbedtls_md_starts(&digest);
  }

  bool ok = true;
  mbedtls_md_context_t digest;
  esp_ota_handle_t handle = 0;
  size_t size = 0;
  size_t written = 0;
  const esp_partition_t *partition = nullptr;
  uint8_t sha256Bytes[SHA256_LENGTH] = { 0 };
  char sha256[2 * SHA256_LENGTH + 1];
  const char *expectedSha256;
};
#endif

class SecureOTAPlugin : public IotPlugin {
public:
  SecureOTAPlugin();
  void execute();
  bool setup() override;
//  bool start() override;
  void onMqttConnected() override;
  bool handleMqttMessage(const char *topic, int id, const char *cmd, const JsonDocument& json) override;
  void setState(OTAState otaState) { state = otaState; }
  OTAState getState() { return state; }
  // We are "in progress" if we are not idle, because we do not want to resume threads after a successful update
  bool isInProgress() { return state == IN_PROGRESS || state == COMPLETE; }

protected:
  WiFiClient *client;
  std::string _topic;
  std::string _broadcastTopic;
  OTAState state = IDLE;
  uint32_t _beginTimestamp = 0;
  uint32_t _endTimestamp = 0;

  const char * _scheme;
  const char * _host;
  int _port;
  const char* _path;
  const char* _token;
#if CONFIG_SECURE_OTA_NATIVE_IMPL
  const char* _sha256;
  bool otaExecute();
#else
  const char* _md5;
  bool doFirmwareUpgrade();
#endif

  int _size;

  VoidTask *otaTask;
  VoidTask *progressTask;
};

extern SecureOTAPlugin SecureOTA;

#endif // CONFIG_ENABLE_SECURE_OTA_PLUGIN
