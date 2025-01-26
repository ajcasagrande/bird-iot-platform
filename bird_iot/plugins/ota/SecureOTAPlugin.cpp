#include "SecureOTAPlugin.h"
#if CONFIG_ENABLE_SECURE_OTA_PLUGIN

#include <Update.h>
#include <esp_ota_ops.h>
#include "include/certs.h"
#include "BLEBeaconPlugin.h"
#include "NimBLEPlugin.h"
#include "BLEKeyboardPlugin.h"
#include <Ticker.h>
#include "include/rtos.h"
#include <esp_task_wdt.h>

SecureOTAPlugin SecureOTA;

static const char* TAG = "Secure OTA";

#define clientStreamLine(stream) *client << stream << endl

static void _executeOTA() {
  SecureOTA.execute();
}

static void _deadmansSwitch(void* _) {
  taskDELAY(CONFIG_SECURE_OTA_TASK_TIMEOUT);
  Device.die("Deadman's switch was triggered! OTA took too long!", RST_OTA_DEADMANS_SWITCH, 500);
}

#if !CONFIG_SECURE_OTA_NATIVE_IMPL
static void _progress() {
  static double percent;
  static uint8_t uPercent;
  // static size_t totalKB;
  static char pctStr[5];
  if (Update.size() > 0) {
    // totalKB = Update.size() / 1024;
    percent = Update.progress() * 100.0 / Update.size();
    uPercent = (uint8_t)percent;
    // LOGD(TAG, "Progress: " << (Update.progress() / 1024) << " / " << totalKB << " KB (" << percent << " %)");
    if (uPercent == 100) {
      strcpy(pctStr, "100%");
    } else if (uPercent < 10) {
      pctStr[0] = uPercent + '0';
      pctStr[1] = '%';
      pctStr[2] = '\0';
    } else {
      pctStr[0] = (uPercent / 10) + '0';
      pctStr[1] = (uPercent % 10) + '0';
      pctStr[2] = '%';
      pctStr[3] = '\0';
    }
    LOGD(TAG, "OTA Progress " << pctStr);
    App.updateProgress(uPercent, pctStr);
  }
}
#endif

#if CONFIG_SECURE_OTA_NATIVE_IMPL
static void _updateProgress(OTAContext *ctx) {
  static double percent;
  static uint8_t uPercent;
  static char pctStr[5];
  static char prev[5];
  if (ctx->size > 0) {
    percent = ctx->written * 100.0 / ctx->size;
    if ((uint8_t)percent > uPercent) {
      uPercent = (uint8_t)percent;
      if (uPercent == 100) {
        strcpy(pctStr, "100%");
      } else if (uPercent < 10) {
        pctStr[0] = uPercent + '0';
        pctStr[1] = '%';
        pctStr[2] = '\0';
      } else {
        pctStr[0] = (uPercent / 10) + '0';
        pctStr[1] = (uPercent % 10) + '0';
        pctStr[2] = '%';
        pctStr[3] = '\0';
      }
      LOGD(TAG, "OTA Progress " << pctStr);
      App.updateProgress(uPercent, nullptr, pctStr, prev);
      strcpy(prev, pctStr);
    }
  }
}
#endif

SecureOTAPlugin::SecureOTAPlugin() : IotPlugin("Secure OTA Plugin") {
  otaTask = new VoidTask("Secure OTA", _executeOTA);
  otaTask->configure(0, _6k, MAX_PRIORITY, CORE_1, false, true);

#if !CONFIG_SECURE_OTA_NATIVE_IMPL
  progressTask = new VoidTask("OTA Progress", _progress);
  progressTask->configure(250, _2k5, LOW_PRIORITY, tskNO_AFFINITY, false, true);
#endif
}

bool SecureOTAPlugin::setup() {
  _topic = OTA_MQTT_TOPIC_BASE;
  _broadcastTopic = OTA_MQTT_TOPIC_BASE;
  _topic += deviceId();
  _broadcastTopic += CONFIG_BIRD_IOT_ENV;
  _broadcastTopic += "/";
  _broadcastTopic += App.profile.updateChannel == SOFTWARE_CHANNEL_STABLE ? "stable" : "dev";
  return true;
}

void SecureOTAPlugin::onMqttConnected() {
  Mqtt.subscribe(_topic.c_str());
  Mqtt.subscribe(_broadcastTopic.c_str());

  // todo: this should probably wait a bit after connecting
  // todo: this should check if app setup is complete
#ifdef CONFIG_APP_ROLLBACK_ENABLE
  LOGD(TAG, "App rollback is enabled");
  const esp_partition_t *running = esp_ota_get_running_partition();
  LOGD(TAG, "running partition: " << running->label);
  esp_ota_img_states_t ota_state;
  if (esp_ota_get_state_partition(running, &ota_state) == ESP_OK) {
    LOGD(TAG, "ota_state: " << _HEX(ota_state));
    if (ota_state == ESP_OTA_IMG_PENDING_VERIFY || ota_state == ESP_OTA_IMG_NEW) {
      LOGD(TAG, "ota pending verification");
      LOGI(TAG, "OTA verification success!");
      setOtaInFlight(false);
      Device.sendAlert(ALERT_OTA_VERIFIED);
      esp_ota_mark_app_valid_cancel_rollback();
    }
  }

  if (wasOtaInFlight()) {
    // an ota was requested on previous boot, but we were unable to verify
    Device.sendAlert(ALERT_OTA_INCOMPLETE);
    setOtaInFlight(false);
  }
#endif
}

bool SecureOTAPlugin::handleMqttMessage(const char *topic, int id, const char *cmd, const JsonDocument& json) {
  if (_topic == topic || _broadcastTopic == topic) {
    if (strcmp(cmd, "firmware_upgrade") == 0) {
      if (isInProgress()) {
        Mqtt.respondError(id, "OTA already in-flight");
        return true;
      }

      LOGD(TAG, "setting OTA_IN_FLIGHT nvs bit");
      setOtaInFlight(true);
      LOGD(TAG, "activating deadman's switch");
      xTaskCreatePinnedToCore(&_deadmansSwitch, "Deadmans Switch", _1p5, nullptr, MEDIUM_HIGH_PRIORITY, nullptr, CORE_0);

      LOGD(TAG, "parsing json message");
      getJsonProperty(_scheme, "scheme");
      getJsonProperty(_host, "host");
      getJsonProperty(_port, "port");
      getJsonProperty(_path, "path");
      LOGD(TAG, "url: " << _scheme << "://" << _host << ":" << _port << _path);
#if CONFIG_SECURE_OTA_NATIVE_IMPL
      getJsonProperty(_sha256, "sha256");
      LOGD(TAG, "sha256: " << _sha256);
#else
      getJsonProperty(_md5, "md5");
      LOGD(TAG, "md5: " << _md5);
#endif
      getJsonProperty(_token, "token");

      Mqtt.respondTrue(id);

#if CONFIG_SECURE_OTA_SUSPEND_ALL_TASKS
      BaseType_t numTasks = uxTaskGetNumberOfTasks();
      LOGD(TAG, numTasks << " currently running tasks");
      LOGD(TAG, "Deleting all non-critical tasks...");
      App.removeAllTasks(true);
      LOGD(TAG, "Waiting for tasks to be deleted...");
      taskDELAY(1000);
      LOGD(TAG, "continue...");
      numTasks = uxTaskGetNumberOfTasks();
      LOGD(TAG, numTasks << " currently running tasks");
#endif

#if CONFIG_ENABLE_BLE_BEACON
      LOGD(TAG, "Destroying BLE Beacon...");
      Beacon.destroy();
      taskDELAY(1000);
#endif

#if CONFIG_ENABLE_BLE_KEYBOARD_PLUGIN
      LOGD(TAG, "Destroying BLE Keyboard Plugin...");
      BLEKeyboard.destroy();
      taskDELAY(1000);
#endif

#if CONFIG_ENABLE_NIMBLE_PLUGIN
      LOGD(TAG, "Destroying NimBLE Plugin...");
      NimBLE.destroy();
      taskDELAY(1000);
#endif

      // LOGD(TAG, "Deregistering mdns services...");
      // mDNS.destroy();

      LOGI(TAG, "Starting OTA task");
      if (otaTask->start()) {
#if !CONFIG_SECURE_OTA_NATIVE_IMPL
        progressTask->start();
#endif
        return true;
      } else {
        state = ERROR;
        Device.sendAlertWithReason(ALERT_OTA_ERROR, "unable to start OTA FreeRTOS task");
        Device.die("Unable to start OTA FreeRTOS task", RST_OTA_RTOS_TASK, 2500);
      }
    }
  }

  return false;
}

void SecureOTAPlugin::execute() {
  state = IN_PROGRESS;
  LOGD(TAG, "FreeRTOS task has started");

#if CONFIG_SECURE_OTA_NATIVE_IMPL
  if (otaExecute()) {
#else
  if (doFirmwareUpgrade()) {
#endif
    state = COMPLETE;
    std::string duration = prettyDuration(_endTimestamp - _beginTimestamp);
    LOGI(TAG, "OTA completed in " << duration);
    Device.sendAlert(ALERT_OTA_COMPLETE, JSON_OBJECT_SIZE(1), [duration](JsonObject optional) {
      optional["duration"] = (const char*)duration.c_str();
    });
    App.updateProgress(100, (char *)"OTA Complete", nullptr, nullptr);
    Device.die("OTA Successful", RST_OTA_COMPLETE, 1000, false);

  } else {
    state = ERROR;
    LOGE(TAG, "OTA Update Failed!");
    Device.sendAlert(ALERT_OTA_ERROR);
    App.updateProgress(0, (char *)"OTA Error", nullptr, nullptr);
    Device.die("OTA failed", RST_OTA_FAILURE, 1000);
  }
}

#if !CONFIG_SECURE_OTA_NATIVE_IMPL
bool SecureOTAPlugin::doFirmwareUpgrade() {
  _beginTimestamp = millis();
  LOGD(TAG, "Sending OTA info alert");
  App.drawProgress(0, "Starting OTA", "");
  Device.sendAlert(ALERT_OTA_STARTED);

  if (strcmp(_scheme, "https") == 0) {
    LOGD(TAG, "Creating HTTPS client");
    client = new WiFiClientSecure();
    ((WiFiClientSecure*)client)->setCACert(OTA_CA_CERTIFICATE);
    //client->setCertificate(test_client_key); // for client verification
    //client->setPrivateKey(test_client_cert);	// for client verification
  } else {
    LOGD(TAG, "Creating HTTP client");
    client = new WiFiClient();
  }

  LOGI(TAG, "Starting connection to server...");
  if (!client->connect(_host, _port)) {
    LOGE(TAG, "Connection failed!");
    return false;
  }

  LOGI(TAG, "Connected to server!");
  // Make a HTTP request:
  clientStreamLine("GET " << _scheme << "://" << _host << ":" << _port << _path << " HTTP/1.0");
  clientStreamLine("Host: " << _host);
  clientStreamLine("Authorization: Bearer " << _token);
  clientStreamLine("Connection: close");
  client->println();

  while (client->connected()) {
    String line = client->readStringUntil('\n');
    // this is essentially a blank line consisting of \r\n but the \n is stripped off because of the read function
    if (line == "\r") {
      LOGI(TAG, "headers received");
      break;
    }

    LOGD(TAG, line);
    line.toLowerCase();

    if (line.startsWith("content-length: ")) {
      _size = line.substring(line.indexOf(' ') + 1).toInt();
      LOGI(TAG, "Update file size: " << _size << " bytes");
    }
  }

  Update.begin(_size, U_FLASH);

  LOGI(TAG, "Starting download of new OTA firmware...");
  uint32_t lastRx = millis();
  while (!Update.isFinished() && client->connected() && (millis() - lastRx <= CONFIG_SECURE_OTA_RX_TIMEOUT)) {
    if (Update.write<WiFiClient>(*client) > 0) {
      lastRx = millis();
    }
  }

  bool success = Update.end();

  client->stop();
  delete client;
  _endTimestamp = millis();

  return success;
}
#endif

#if CONFIG_SECURE_OTA_NATIVE_IMPL
static esp_err_t _http_event_handler(esp_http_client_event_t *evt) {
  static OTAContext *ctx;
  static esp_err_t err;
  switch(evt->event_id) {
    case HTTP_EVENT_ERROR:
      LOGD(TAG, "HTTP_EVENT_ERROR");
      break;

    case HTTP_EVENT_ON_CONNECTED:
      LOGD(TAG, "HTTP_EVENT_ON_CONNECTED");
      App.updateProgress(0, (char *)"OTA Progress", nullptr, nullptr);
      break;

    case HTTP_EVENT_HEADER_SENT:
      LOGD(TAG, "HTTP_EVENT_HEADER_SENT");
      break;

    case HTTP_EVENT_ON_HEADER:
      LOGD(TAG, "HTTP_EVENT_ON_HEADER, key="<< evt->header_key <<", value=" << evt->header_value);
      ctx = (OTAContext *)evt->user_data;

      if (strcasecmp(evt->header_key, "Content-Length") == 0) {
        ctx->size = atoi(evt->header_value);
        LOGI(TAG, "Update file size: " << ctx->size << " bytes");
      }
      break;

    case HTTP_EVENT_ON_DATA:
      LOGV(TAG, "HTTP_EVENT_ON_DATA, len=" << evt->data_len);
      ctx = (OTAContext *)evt->user_data;
      TRY_LOCK(*ctx,
        err = esp_ota_write(ctx->handle, evt->data, evt->data_len);
        if (err != ESP_OK) {
          LOGE(TAG, "OTA write error: " << esp_err_to_name(err));
          ctx->ok = false;
        } else {
          ctx->written += evt->data_len;
          mbedtls_md_update(&ctx->digest, (uint8_t *)evt->data, evt->data_len);
          _updateProgress(ctx);
        }
      ,);
      break;

    case HTTP_EVENT_ON_FINISH:
      LOGD(TAG, "HTTP_EVENT_ON_FINISH");
      ctx = (OTAContext *)evt->user_data;
      TRY_LOCK(*ctx,
        mbedtls_md_finish(&ctx->digest, ctx->sha256Bytes);
        mbedtls_md_free(&ctx->digest);
        for (int i=0; i < SHA256_LENGTH; i++) {
          simpleHexFormat(ctx->sha256 + (2*i), ctx->sha256Bytes[i], 2, false, false);
        }
        // set last bit to nil for c-string
        ctx->sha256[2 * SHA256_LENGTH] = '\0';
        LOGI(TAG, "firmware sha256: " << ctx->sha256);
        LOGI(TAG, "expected sha256: " << ctx->expectedSha256);

        if (strcmp(ctx->expectedSha256, ctx->sha256) == 0) {
          LOGI(TAG, "success! sha256 matches!");
        } else {
          ctx->ok = false;
          LOGE(TAG, "firmware sha256 does not match the expected sha256!");
        }
      ,);
      break;

    case HTTP_EVENT_DISCONNECTED:
      LOGD(TAG, "HTTP_EVENT_DISCONNECTED");
      break;
  }
  return ESP_OK;
}

void _erasePartition(void *param) {
  LOGD(TAG, "inside _erasePartition");
  auto ctx = (OTAContext*)param;
  TRY_LOCK(*ctx,
    LOGI(TAG, "Erasing partition " << ctx->partition->label << " at offset 0x" << _HEX(ctx->partition->address) << ". This may take a few seconds!");
    App.updateProgress(0, (char *)"Erasing...", nullptr, nullptr);
    esp_err_t err = esp_ota_begin(ctx->partition, OTA_SIZE_UNKNOWN, &ctx->handle);
    if (err != ESP_OK) {
      LOGE(TAG, "esp_ota_begin failed: " << esp_err_to_name(err));
      ctx->ok = false;
    } else {
      LOGI(TAG, "esp_ota_begin succeeded");
    }
  ,);
  vTaskDelete(nullptr);
}

bool SecureOTAPlugin::otaExecute() {
  bool ok = false;
  esp_http_client_handle_t _esp_client = nullptr;

  do {
    _beginTimestamp = millis();
    LOGD(TAG, "Sending OTA info alert");
    App.drawProgress(0, "Starting OTA", "");
    Device.sendAlert(ALERT_OTA_STARTED);

    OTAContext ctx = OTAContext(esp_ota_get_next_update_partition(nullptr), _sha256);
    if (ctx.partition == nullptr) {
      LOGE(TAG, "passive ota partition not found");
      break;
    }

    xTaskCreatePinnedToCore(&_erasePartition, "OTA Erase", _2k, &ctx, HIGH_PRIORITY, nullptr, CORE_0);
    // Give the other task a head start
    taskDELAY(100);

    esp_http_client_config_t config;
    memset(&config, 0, sizeof(config));
    config.host = _host;
    config.port = _port;
    config.path = _path;
    if (strcmp(_scheme, "https") == 0) {
      config.transport_type = HTTP_TRANSPORT_OVER_SSL;
      config.cert_pem = (char *) OTA_CA_CERTIFICATE;
    } else {
      config.transport_type = HTTP_TRANSPORT_OVER_TCP;
    }
    config.event_handler = _http_event_handler;
    config.buffer_size = CONFIG_MBEDTLS_SSL_IN_CONTENT_LEN;
    config.method = HTTP_METHOD_GET;
    config.user_data = (void *)&ctx;

    LOGI(TAG, "Initiating OTA Firmware Upgrade via HTTPS");
    LOGD(TAG, "url: " << _scheme << "://" << _host << ":" << _port << _path);

    _esp_client = esp_http_client_init(&config);
    auto bearer = std::string("Bearer ");
    bearer += _token;
    esp_http_client_set_header(_esp_client, "Authorization", bearer.c_str());

    esp_err_t err = esp_http_client_perform(_esp_client);
    if (err == ESP_OK) {
      int status = esp_http_client_get_status_code(_esp_client);
      if (status >= 200 && status < 300 && ctx.ok) {
        err = esp_ota_end(ctx.handle);
        if (err != ESP_OK) {
          LOGE(TAG, "esp_ota_end failed: " << esp_err_to_name(err));
          break;
        }

        err = esp_ota_set_boot_partition(ctx.partition);
        if (err != ESP_OK) {
          LOGE(TAG, "esp_ota_set_boot_partition failed:" << esp_err_to_name(err));
          break;
        }
        LOGI(TAG, "esp_ota_set_boot_partition succeeded");
        ok = true;
      }
    } else {
      LOGE(TAG, "http get request failed: " << esp_err_to_name(err));
      break;
    }

  } while(false);

  esp_http_client_cleanup(_esp_client);
  _endTimestamp = millis();

  return ok;
}
#endif

#endif // CONFIG_ENABLE_SECURE_OTA_PLUGIN

