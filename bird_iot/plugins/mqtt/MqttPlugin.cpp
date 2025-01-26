#include "MqttPlugin.h"

#include "sdkconfig.h"
#include "include/private.h"
#include "include/certs.h"
#include "include/topics.h"
#include "include/logging.h"
#include "rtos/lock_macros.h"

MqttPlugin Mqtt;

static const char* TAG = "Mqtt";

static void onSubscribeAck(int id);

#if CONFIG_MQTT_PUBLISH_BUFFER_TASK
static void _execute() {
  PublishData *data = nullptr;
  while (!Mqtt.publishQueue.empty()) {
    TRY_LOCK(Mqtt,
        data = Mqtt.publishQueue.back();
        Mqtt.publishQueue.pop_back();
    , return;)

    Mqtt.publishInternal(data);
    delete data;
  }

  if (!Mqtt.subscribeQueue.getData().empty()) {
    Mqtt.subscribeQueue.lock();
    for (auto & sub : Mqtt.subscribeQueue.getData()) {
      LOGD(TAG, "pending subscription: " << sub->topic << " (" << sub->age() << " ms)");
      if (sub->age() > CONFIG_MQTT_SUBSCRIBE_TIMEOUT) {
        Mqtt.subscribeInternal(sub);
      }
    }
    Mqtt.subscribeQueue.unlock();
  }
}

bool MqttPlugin::publishInternal(PublishData* data) {
  return publishInternal(data->topic, data->payload, data->len);
}

#endif

static void _onMqttConnect(esp_mqtt_event_handle_t event) {
  Mqtt.setConnected(true);
  Prefs.resetCounter(PREF_BOOTS_SINCE_MQTT_CONNECTION);

  for (auto & plugin : App.getPlugins()) {
    plugin->onMqttConnected();
  }
}

static void _onMqttDisconnect(esp_mqtt_event_handle_t event) {
  Mqtt.setConnected(false);

  Mqtt.subscribeQueue.lock();
  Mqtt.subscribeQueue.clear();
  Mqtt.subscribeQueue.unlock();

  for (auto & plugin : App.getPlugins()) {
    plugin->onMqttDisconnected();
  }

  Mqtt.connect();
}

static void _onMqttMessage(esp_mqtt_event_handle_t event) {
  NetworkLed.mode(LED_FAST_BLINK);

  // convert into C-style null-terminated string
  event->topic[event->topic_len] = '\0';
  event->data[event->data_len] = '\0';

  LOGI(TAG, "Received: " << event->topic << " " << event->data << " (len: " << event->data_len << ")");

  JsonDocument json = parseJsonMessage(event->data, event->data_len);
  getJsonPropertyOrReturnVoid(const char* cmd, "cmd");
  getJsonPropertyOrReturnVoid(const int id, "id");

  LOGI(TAG, "Received command: " << cmd << ", id: " << id);

  bool handled = false;
  for (auto & plugin : App.getPlugins()) {
    if ((handled = plugin->handleMqttMessage(event->topic, id, cmd, json))) {
      LOGV(TAG, "message handled by plugin: " << plugin->name);
      break;
    }
  }

  if (!handled) {
    LOGW(TAG, "WARNING: message not handled by any plugin!");
    Mqtt.respondFalse(id);
  }

  NetworkLed.reset();
}

static esp_err_t onMqttEvent(esp_mqtt_event_handle_t event) {
  LOGV(TAG, "event id: " << event->event_id);

  switch (event->event_id) {
    case MQTT_EVENT_ERROR:
      LOGE(TAG, "mqtt client error");
      break;

    case MQTT_EVENT_BEFORE_CONNECT:
      LOGD(TAG, "mqtt client before connect");
      break;

    case MQTT_EVENT_PUBLISHED:
      LOGD(TAG, "mqtt publish complete (msg_id=" << event->msg_id << ")");
      break;

    case MQTT_EVENT_SUBSCRIBED:
      LOGD(TAG, "mqtt subscribe ack (msg_id=" << event->msg_id << ")");
      onSubscribeAck(event->msg_id);
      break;

    case MQTT_EVENT_UNSUBSCRIBED:
      LOGD(TAG, "mqtt unsubscribe ack (msg_id=" << event->msg_id << ")");
      break;

    case MQTT_EVENT_CONNECTED:
      LOGI(TAG, "esp32 mqtt connected");
      _onMqttConnect(event);
      break;

    case MQTT_EVENT_DATA:
      _onMqttMessage(event);
      break;

    case MQTT_EVENT_DISCONNECTED:
      LOGD(TAG, "mqtt broker disconnected");
      _onMqttDisconnect(event);
      break;

    default:
      LOGW(TAG, "event type " << event->event_id << " not handled yet");
      break;
  }

  return ESP_OK;
}

static void onSubscribeAck(int id) {
  SubscribeData *sub;
  Mqtt.subscribeQueue.lock();

  if (!Mqtt.subscribeQueue.getData().empty()) {
    auto it = Mqtt.subscribeQueue.getData().begin();

    while (it != Mqtt.subscribeQueue.getData().end()) {
      sub = *it;

      if (sub->messageId == id) {
        LOGD(TAG, "successfully subscribed to " << sub->topic);
        it = Mqtt.subscribeQueue.getData().erase(it);
        delete sub;
        LOGD(TAG, Mqtt.subscribeQueue.getData().size() << " pending subscriptions");
        break;
      }

      it++;
    }
  }

  Mqtt.subscribeQueue.unlock();
}

bool MqttPlugin::setup() {
  if (cfg == nullptr) {
    LOGI(TAG, "setup esp32 mqtt driver");
    Mqtt.startLockTrace();
    cfg = new esp_mqtt_client_config_t();
    memset(cfg, 0, sizeof(*cfg));
    cfg->client_id = deviceId();
    cfg->host = MQTT_HOST;
    cfg->username = MQTT_USER;
    cfg->password = MQTT_PASS;
    cfg->cert_pem = MQTT_CA_CERTIFICATE;
    cfg->transport = MQTT_TRANSPORT_OVER_SSL;
    cfg->port = MQTT_PORT;
    cfg->lwt_msg = deviceId();
    cfg->lwt_qos = CONFIG_MQTT_QOS;
    cfg->lwt_retain = 0;
    cfg->lwt_topic = topics.status_lost.c_str();
    cfg->keepalive = CONFIG_MQTT_KEEPALIVE;
    cfg->event_handle = onMqttEvent;
  }

  return true;
}

bool MqttPlugin::start() {
#if CONFIG_MQTT_PUBLISH_BUFFER_TASK
  task = new VoidTask("Mqtt Publish", _execute);
  return task->configure(10, _3k, MEDIUM_HIGH_PRIORITY, tskNO_AFFINITY, false, true)
         && task->start();
#endif
}

void MqttPlugin::onWifiConnected() {
  connect();
}

bool MqttPlugin::disconnect() {
  if (client == nullptr) {
    return true;
  }
  return esp_mqtt_client_stop(client) != ESP_OK;
}

bool MqttPlugin::connect() {
  // todo
  setup();

  if (client == nullptr) {
    LOGD(TAG, "esp32 mqtt client init");
    client = esp_mqtt_client_init(cfg);
    LOGI(TAG, "esp32 mqtt driver connect call");
    if (esp_mqtt_client_start(client) != ESP_OK) {
      return false;
    }
  }

  return true;
}

bool MqttPlugin::publish(const std::string& topic, const JsonDocument& json) {
  return publish(topic.c_str(), json);
}

bool MqttPlugin::publish(const std::string& topic, const char* payload, size_t len) {
  return publishInternal(topic.c_str(), payload, len);
}

bool MqttPlugin::publish(const char *topic, const JsonDocument& json) {
  size_t len = measureJson(json) + 1;
  char *payload = (char*)malloc(len * sizeof(char));
  serializeJson(json, payload, len);
#if CONFIG_MQTT_PUBLISH_BUFFER_TASK
  bool res;
  TRY_LOCK(Mqtt,
      Mqtt.publishQueue.push_back(new PublishData{topic, payload, len-1});
          res = true;
  , res = false;);
  return res;
#else
  bool result = publishInternal(topic, (const char*)payload, len-1);
  free(payload);
  return result;
#endif
}

bool MqttPlugin::publishInternal(const char* topic, const char* payload, size_t len) {
  if (len == 0) {
    len = strlen(payload);
  }
  
  if (SafeMode.isActive() && !SafeMode.isMqttEnabled()) {
    LOGW(TAG, "Refusing to send message due to being in safe mode: " << topic << " " << payload << " (len: " << len << ")");
    return false;
  }

  if (client == nullptr) {
    if (WifiDriver::connected()) {
      connect();
    }
    LOGW(TAG, "Refusing to send message because client is not initialized: " << topic << " " << payload << " (len: " << len << ")");
    return false;
  }

  if (!connected()) {
    LOGW(TAG, "Refusing to send message because client is not connected: " << topic << " " << payload << " (len: " << len << ")");
    return false;
  }

  NetworkLed.mode(LED_FAST_BLINK);

  LOGI(TAG, "Publish: " << topic << " " << payload << " (len: " << len << ")");
  bool success = esp_mqtt_client_publish(client, topic, payload, len, CONFIG_MQTT_QOS, false) != 0;

  if (!success) {
    LOGE(TAG, "**** Publish Failed! ****");
  }

  NetworkLed.reset();
  return success;
}

bool MqttPlugin::subscribeInternal(SubscribeData* sub) {
  LOGI(TAG, "Subscription: " << sub->topic);

  // update the last time we tried to subscribe
  sub->ms = millis();
  sub->messageId = esp_mqtt_client_subscribe(client, sub->topic, CONFIG_MQTT_QOS);
  if (sub->messageId == -1) {
    LOGE(TAG, "Unable to subscribe to topic: " << sub->topic);
    LOGE(TAG, "**** Subscribe Failed! ****");
    return false;
  }

  return true;
}

bool MqttPlugin::subscribe(const char* topic) {
  auto sub = new SubscribeData(topic);
  subscribeQueue.push_back(sub);
  return subscribeInternal(sub);
}

template<class T>
bool MqttPlugin::respondResult(const int id, T result) {
  const size_t capacity = JSON_OBJECT_SIZE(2);
  DynamicJsonDocument doc(capacity);
  doc["id"] = id;
  doc["result"] = result;
  return publish(topics.response, doc);
}

bool MqttPlugin::respondWith(const int id, const char* key, size_t extraCapacity, const std::function<void(JsonObject)>& lambda) {
  const size_t capacity = JSON_OBJECT_SIZE(2) + extraCapacity;
  DynamicJsonDocument doc(capacity);
  doc["id"] = id;
  lambda(doc.createNestedObject(key));
  return publish(topics.response, doc);
}

bool MqttPlugin::respondError(const int id, const char* error) {
  const size_t capacity = JSON_OBJECT_SIZE(2);
  DynamicJsonDocument doc(capacity);
  doc["id"] = id;
  doc["error"] = error;
  return publish(topics.response, doc);
}

bool MqttPlugin::respondTrue(const int id) {
  return respondResult<bool>(id, true);
}

// todo: should have a respond error
bool MqttPlugin::respondFalse(const int id) {
  return respondResult<bool>(id, false);
}
