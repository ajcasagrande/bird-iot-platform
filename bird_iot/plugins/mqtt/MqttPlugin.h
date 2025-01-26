#pragma once

#include "include/common.h"
#include "Lockable.h"
#include "LockableQueue.h"

#include <mqtt_client.h>

class PublishData {
public:
  PublishData(const char* topic, char *payload, size_t len) : topic(topic), payload(payload), len(len) { }
  ~PublishData() { free(payload); }

  const char* topic;
  char *payload;
  size_t len;
};

struct SubscribeData {
  const char* topic;
  int messageId;
  uint32_t ms;

  explicit SubscribeData(const char* topic_) : topic(topic_), messageId(-1), ms(millis()) { }

  uint32_t age() {
    return since(ms);
  }
};

class MqttPlugin : public IotPlugin, public ExclusiveLockable {
private:
  esp_mqtt_client_config_t *cfg = nullptr;
  esp_mqtt_client_handle_t client = nullptr;
  bool _connected = false;

public:
  MqttPlugin() : IotPlugin("MQTT Plugin") { }

  TopicsClass topics;

  bool setup() override;
  bool start() override;
  bool connected() { return _connected; }
  void setConnected(bool c) { _connected = c; }
  void onWifiConnected() override;

  bool connect();
  bool disconnect();

  bool subscribe(const char *topic);
  bool subscribeInternal(SubscribeData* sub);

  bool publish(const char *topic, const JsonDocument& json);
  bool publish(const std::string& topic, const JsonDocument& json);
  bool publish(const std::string& topic, const char* payload, size_t len=0);
  bool publishInternal(const char *topic, const char *payload, size_t len=0);

#if CONFIG_MQTT_PUBLISH_BUFFER_TASK
  bool publishInternal(PublishData *data);
  std::vector<PublishData*> publishQueue;
  VoidTask *task;
#endif

  LockableQueue<SubscribeData> subscribeQueue;

  template<class T> bool respondResult(int id, T result);
  bool respondError(int id, const char* error);
  bool respondTrue(int id);
  bool respondFalse(int id);

  bool respondWith(int id, const char* key, size_t extraCapacity, const std::function<void(JsonObject)> &lambda);
};

extern MqttPlugin Mqtt;
