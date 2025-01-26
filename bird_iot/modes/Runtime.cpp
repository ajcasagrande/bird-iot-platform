#include "Runtime.h"

#include "sdkconfig.h"
#include "IotApp.h"
#include "include/plugins_inc.h"

static const char* TAG = "Runtime";

RuntimeClass Runtime;

#if CONFIG_ENABLE_EMPTY_DEBUG_TASK
void _emptyTask() { }
#endif

bool RuntimeClass::activate() {

  App.setup();
  Profile *p = &App.profile;
  verifyHeap();

  App.registerPlugin(&BufferedStreamJoiner);
  App.registerPlugin(&Wifi);
  App.registerPlugin(&Mqtt);

#if CONFIG_ENABLE_SECURE_OTA_PLUGIN
  App.registerPlugin(&SecureOTA);
#endif

#if CONFIG_ENABLE_SPIFFS_PLUGIN
  App.registerPlugin(&Spiffs);
#endif

  App.registerPlugin(&Device);

#if CONFIG_ENABLE_I2C_DRIVER
  if (p->i2cEnabled()) {
    i2cDriver.setPins(p->sda, p->scl);
    App.registerPlugin(&i2cDriver);
  }
#endif

#if CONFIG_ENABLE_ONE_WIRE_DRIVER
  if (p->oneWireEnabled()) {
    OneWireDriver.setPin(p->oneWirePin);
    App.registerPlugin(&OneWireDriver);
  }
#endif

#if CONFIG_ENABLE_CONNECTION_STATS_PLUGIN
  App.registerPlugin(&ConnectionInfo);
#endif

#if CONFIG_ENABLE_STATUS_LED_DRIVER
  App.registerPlugin(new StatusLedDriver());
#endif

#if CONFIG_ENABLE_MDNS_PLUGIN
  App.registerPlugin(&mDNS);
#endif

#if CONFIG_ENABLE_CONSOLE_PLUGIN
  App.registerPlugin(&Console);
#endif

#if CONFIG_ENABLE_WEBSOCKET_SERVER_PLUGIN
  App.registerPlugin(&WebSocketServer);
#endif

#if CONFIG_ENABLE_WEBSOCKET_CLIENT_PLUGIN
  App.registerPlugin(&WebsocketClient);
#endif

#if CONFIG_ENABLE_COMMANDS_PLUGIN
  App.registerPlugin(&Commands);
#endif

#if CONFIG_ENABLE_ESP32_INTERNAL_TEMP_SENSOR
  App.registerPlugin(new ESP32TempSensor());
#endif

#if CONFIG_ENABLE_HTTPS_SERVER_PLUGIN
  App.registerPlugin(&WebServer);
#endif

#if CONFIG_ENABLE_RSSI_STATS_PLUGIN
  App.registerPlugin(&RssiStats);
#endif

#if CONFIG_ENABLE_TFT_DISPLAY
  App.registerPlugin(&TFTDisplay);
#endif

#if CONFIG_ENABLE_GPS_PLUGIN
  registerIf(p->gpsEnabled(), new GpsPlugin());
#endif

#if CONFIG_ENABLE_RF_SNIFFER_PLUGIN
  registerIfPin(p->rf433Receive, new RFSnifferPlugin(433, p->rf433Receive));
  registerIfPin(p->rf315Receive, new RFSnifferPlugin(315, p->rf315Receive));
#endif

#if CONFIG_ENABLE_RF_TRANSMIT_PLUGIN
  registerIfPin(p->rf433Transmit, new RFTransmitPlugin(433, p->rf433Transmit, p->rf433TxRepeat));
  registerIfPin(p->rf315Transmit, new RFTransmitPlugin(315, p->rf315Transmit, p->rf315TxRepeat));
#endif

#if CONFIG_ENABLE_HUNTER_FAN_PLUGIN
  registerIfPin(p->hunterFanTx, new HunterFanPlugin(p->hunterFanTx, p->hunterFanRepeat));
#endif

#if CONFIG_ENABLE_IR_PLGUIN
  registerIfPin(p->irTransmitPin, new IRPlugin(p->irTransmitPin));
#endif

#if CONFIG_ENABLE_REED_SWITCH_DRIVER
  registerIf(p->dualReedEnabled(), new DualReedSwitchDriver(GARAGE_MQTT_TOPIC, Mqtt.topics.garage.c_str()));
  registerIf(!p->reedSwitches.empty(), new ReedSwitchDriver());
#endif

#if CONFIG_ENABLE_DS18B20_SENSOR_PLUGIN
  registerIf(p->ds18b20Enabled(), new DS18B20Sensor(p->ds18b20Index));
#endif

#if CONFIG_ENABLE_DHT_TEMP_SENSOR_PLUGIN
  registerIf(p->dhtEnabled(), new DHTSensor(p->dhtPin, p->dhtModel));
#endif

#if CONFIG_ENABLE_GARAGE_PLUGIN
  registerIfPin(p->garageRelayPin, new GaragePlugin(p->garageRelayPin));
#endif

#if CONFIG_ENABLE_NEOPIXEL_DRIVER
  if (p->neoPixelEnabled()) {
    auto *np = new NeoPixelDriver(p->neoPixelPin, p->neoPixelCount);
    App.registerNeoPixel(np);

#if CONFIG_ENABLE_RC_LIGHTS_PLUGIN
    App.registerPlugin(new RcLightsPlugin(np));
#endif

  }
#endif

#if CONFIG_ENABLE_BLE_BEACON
  App.registerPlugin(&Beacon);
#endif

#if CONFIG_ENABLE_WIFI_SCAN_PLUGIN
  registerIf(p->wifiScanEnabled(), &WifiScanner);
#endif

#if CONFIG_ENABLE_NIMBLE_PLUGIN
  App.registerPlugin(&NimBLE);
#endif

#if CONFIG_ENABLE_CAMERA_SERVER_PLUGIN
  App.registerPlugin(new CameraServerPlugin());
#endif

#if CONFIG_ENABLE_SNTP_PLUGIN
  App.registerPlugin(&Sntp);
#endif

#if CONFIG_ENABLE_SPI_DISPLAY_PLUGIN
  App.registerPlugin(&SPIDisplay);
#endif

#if CONFIG_ENABLE_HEARTBEAT_TASK
  App.registerPlugin(&Heartbeat);
#endif

#if CONFIG_ENABLE_SECURE_WEBSOCKET_PLUGIN
  App.registerPlugin(&SecureWebsocket);
#endif

#if CONFIG_ENABLE_BUTTON_PLUGIN
  App.registerPlugin(&ButtonPlugin);
#endif

#if CONFIG_ENABLE_BLE_KEYBOARD_PLUGIN
  App.registerPlugin(&BLEKeyboard);
#endif

#if CONFIG_ENABLE_WEBSOCKET_COMMAND_PLUGIN
  App.registerPlugin(&WebSocketCommand);
#endif

#if CONFIG_ENABLE_ACURITE_SENSOR_PLUGIN
  App.registerPlugin(&AcuriteSensor);
#endif

#if CONFIG_ENABLE_SOIL_SENSOR
  registerIfPin(p->soilSensorPin, new SoilSensor(p->soilSensorPin));
#endif

#if CONFIG_ENABLE_SERVO_INPUT_PLUGIN
  registerIf(ServoInput.enabled(), &ServoInput);
#endif

#if CONFIG_ENABLE_I2C_SLAVE
  registerIf(p->i2cSlaveEnabled(), new I2CSlave(p->sdaSlave, p->sclSlave, p->i2cSlaveAddr));
#endif

#if CONFIG_ENABLE_RF_RAW_PLUGIN
  registerIfPin(p->rfRawPin, new RFRawPlugin(p->rfRawPin));
#endif

#if CONFIG_ENABLE_HOBBYWING_PLUGIN
  App.registerPlugin(&Hobbywing);
#endif

#if CONFIG_ENABLE_HOBBYWING_TASK_PLUGIN
  App.registerPlugin(&HobbywingTask);
#endif

  bool result = App.setupPlugins();
  result = App.startPlugins() && result;

#if CONFIG_ENABLE_EMPTY_DEBUG_TASK
  auto *t = new VoidTask("Empty Task", _emptyTask);
  t->configure(1000, _2k, MIN_PRIORITY);
  t->start();
#endif

  LOGI(TAG, "Device Id: " << deviceId());
  LOGI(TAG, "Setup complete!");

  return result;
}
