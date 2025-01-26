set(CORE_SRCS
  arduino-esp32/cores/esp32/base64.cpp
  arduino-esp32/cores/esp32/cbuf.cpp
  arduino-esp32/cores/esp32/esp32-hal-adc.c
  arduino-esp32/cores/esp32/esp32-hal-bt.c
  arduino-esp32/cores/esp32/esp32-hal-cpu.c
  arduino-esp32/cores/esp32/esp32-hal-dac.c
  arduino-esp32/cores/esp32/esp32-hal-gpio.c
  arduino-esp32/cores/esp32/esp32-hal-i2c.c
  arduino-esp32/cores/esp32/esp32-hal-ledc.c
  arduino-esp32/cores/esp32/esp32-hal-matrix.c
  arduino-esp32/cores/esp32/esp32-hal-misc.c
  arduino-esp32/cores/esp32/esp32-hal-psram.c
  arduino-esp32/cores/esp32/esp32-hal-sigmadelta.c
  arduino-esp32/cores/esp32/esp32-hal-spi.c
  arduino-esp32/cores/esp32/esp32-hal-time.c
  arduino-esp32/cores/esp32/esp32-hal-timer.c
  arduino-esp32/cores/esp32/esp32-hal-touch.c
  arduino-esp32/cores/esp32/esp32-hal-uart.c
  arduino-esp32/cores/esp32/esp32-hal-rmt.c
  arduino-esp32/cores/esp32/Esp.cpp
  arduino-esp32/cores/esp32/FunctionalInterrupt.cpp
  arduino-esp32/cores/esp32/HardwareSerial.cpp
  arduino-esp32/cores/esp32/IPAddress.cpp
  arduino-esp32/cores/esp32/IPv6Address.cpp
  arduino-esp32/cores/esp32/libb64/cdecode.c
  arduino-esp32/cores/esp32/libb64/cencode.c
  arduino-esp32/cores/esp32/main.cpp
  arduino-esp32/cores/esp32/MD5Builder.cpp
  arduino-esp32/cores/esp32/Print.cpp
  arduino-esp32/cores/esp32/stdlib_noniso.c
  arduino-esp32/cores/esp32/Stream.cpp
  arduino-esp32/cores/esp32/StreamString.cpp
  arduino-esp32/cores/esp32/wiring_pulse.c
  arduino-esp32/cores/esp32/wiring_shift.c
  arduino-esp32/cores/esp32/WMath.cpp
  arduino-esp32/cores/esp32/WString.cpp
  )

set(LIBRARY_SRCS
  # arduino-esp32/libraries/ArduinoOTA/src/ArduinoOTA.cpp
  # arduino-esp32/libraries/AsyncUDP/src/AsyncUDP.cpp
  # arduino-esp32/libraries/BluetoothSerial/src/BluetoothSerial.cpp
  # arduino-esp32/libraries/DNSServer/src/DNSServer.cpp
  arduino-esp32/libraries/EEPROM/src/EEPROM.cpp
  # arduino-esp32/libraries/ESPmDNS/src/ESPmDNS.cpp
  # arduino-esp32/libraries/FFat/src/FFat.cpp
  arduino-esp32/libraries/FS/src/FS.cpp
  arduino-esp32/libraries/FS/src/vfs_api.cpp
  arduino-esp32/libraries/HTTPClient/src/HTTPClient.cpp
  arduino-esp32/libraries/HTTPUpdate/src/HTTPUpdate.cpp
  # arduino-esp32/libraries/NetBIOS/src/NetBIOS.cpp
  arduino-esp32/libraries/Preferences/src/Preferences.cpp
  # arduino-esp32/libraries/SD_MMC/src/SD_MMC.cpp
  # arduino-esp32/libraries/SD/src/SD.cpp
  # arduino-esp32/libraries/SD/src/sd_diskio.cpp
  # arduino-esp32/libraries/SD/src/sd_diskio_crc.c
  # arduino-esp32/libraries/SimpleBLE/src/SimpleBLE.cpp
  arduino-esp32/libraries/SPIFFS/src/SPIFFS.cpp
  arduino-esp32/libraries/SPI/src/SPI.cpp
  arduino-esp32/libraries/Ticker/src/Ticker.cpp
  arduino-esp32/libraries/Update/src/Updater.cpp
  arduino-esp32/libraries/WebServer/src/WebServer.cpp
  arduino-esp32/libraries/WebServer/src/Parsing.cpp
  arduino-esp32/libraries/WebServer/src/detail/mimetable.cpp
  arduino-esp32/libraries/WiFiClientSecure/src/ssl_client.cpp
  arduino-esp32/libraries/WiFiClientSecure/src/WiFiClientSecure.cpp
  # arduino-esp32/libraries/WiFi/src/ETH.cpp
  arduino-esp32/libraries/WiFi/src/WiFiAP.cpp
  arduino-esp32/libraries/WiFi/src/WiFiClient.cpp
  arduino-esp32/libraries/WiFi/src/WiFi.cpp
  arduino-esp32/libraries/WiFi/src/WiFiGeneric.cpp
  arduino-esp32/libraries/WiFi/src/WiFiMulti.cpp
  arduino-esp32/libraries/WiFi/src/WiFiScan.cpp
  arduino-esp32/libraries/WiFi/src/WiFiServer.cpp
  arduino-esp32/libraries/WiFi/src/WiFiSTA.cpp
  arduino-esp32/libraries/WiFi/src/WiFiUdp.cpp
  arduino-esp32/libraries/Wire/src/Wire.cpp
)

set(COMPONENT_SRCS ${CORE_SRCS} ${LIBRARY_SRCS})

set(COMPONENT_ADD_INCLUDEDIRS
  arduino-esp32/variants/esp32/
  arduino-esp32/cores/esp32/
  arduino-esp32/libraries/AsyncUDP/src
  arduino-esp32/libraries/BluetoothSerial/src
  arduino-esp32/libraries/DNSServer/src
  arduino-esp32/libraries/EEPROM/src
  arduino-esp32/libraries/ESP32/src
  arduino-esp32/libraries/ESPmDNS/src
  arduino-esp32/libraries/FFat/src
  arduino-esp32/libraries/FS/src
  arduino-esp32/libraries/HTTPClient/src
  arduino-esp32/libraries/HTTPUpdate/src
  arduino-esp32/libraries/NetBIOS/src
  arduino-esp32/libraries/Preferences/src
  arduino-esp32/libraries/SD_MMC/src
  arduino-esp32/libraries/SD/src
  arduino-esp32/libraries/SimpleBLE/src
  arduino-esp32/libraries/SPIFFS/src
  arduino-esp32/libraries/SPI/src
  arduino-esp32/libraries/Ticker/src
  arduino-esp32/libraries/Update/src
  arduino-esp32/libraries/WebServer/src
  arduino-esp32/libraries/WiFiClientSecure/src
  arduino-esp32/libraries/WiFi/src
  arduino-esp32/libraries/Wire/src
  
)

set(COMPONENT_PRIV_INCLUDEDIRS arduino-esp32/cores/esp32/libb64)

set(COMPONENT_REQUIRES esp32 spi_flash mbedtls)
set(COMPONENT_PRIV_REQUIRES nvs_flash app_update spiffs bootloader_support openssl bt)

register_component()

component_compile_options(
    -Wno-implicit-fallthrough
)
