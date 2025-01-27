# Bird-IoT Platform

Welcome to the **Bird-IoT Platform**! This project is designed to run on ESP32-based devices with a highly modular approach. It provides a system of **plugins** (each derived from a common interface) and a **task** system that allows easy scheduling and concurrency.

> **Note:** This project is not seeing any regular updates.
> The intent of this repo is to share the concepts and code within.

> **Note:** Be sure to configure your authorization headers. Look for _TODO__ in the codebase

---

## Table of Contents

- [Architecture Overview](#architecture-overview)
- [Plugin System](#plugin-system)
- [Task System](#task-system)
- [Supported Plugins and Features](#supported-plugins-and-features)


---

## Architecture Overview

The Bird-IoT Platform is built around a central `IotApp` singleton that:

- Manages **device profiles** (GPIO pin assignments, hardware specifics).
- Initializes **core services** (NVS, Wi-Fi, MQTT, safe mode, etc.).
- Registers **plugins** (each plugin is a self-contained module providing some feature or driver).
- Coordinates **tasks** (each plugin can schedule its own asynchronous task, e.g. for polling hardware or performing repeated actions).

**Key Points**:

- **Safe Mode**: The platform supports a “safe mode” that can limit or bypass certain features if too many failed boots occur.
- **Profiles**: A JSON or struct-based system describes board-specific pins (e.g., SDA, SCL, servo pins, etc.).
- **Startup Flow**:
  1. System initializes
  2. NVS is set up
  3. Boot counters are incremented
  4. Wi-Fi and MQTT connect
  5. Plugins are **setup** (configure) and then **start** (run)
  6. Tasks begin periodic or event-driven execution

---

## Plugin System

**`IotPlugin`** is the base class. Each plugin:

- Has a **name** (e.g. `"Console Plugin"`).
- Implements any of these optional lifecycle hooks:
  - `bool setup()` — configure, allocate resources, and do any required initialization.
  - `bool start()` — start actual execution (e.g. begin tasks, open sockets, etc.).
  - `void onWifiConnected()` / `onWifiDisconnected()`
  - `void onMqttConnected()` / `onMqttDisconnected()`
  - `bool handleMqttMessage(const char *topic, int id, const char *cmd, const JsonDocument& json)`
  - `bool handleCommand(const std::string &cmd)` — for console or remote command handling.
  - `void addFramesAndOverlays()` — for UI-based plugins that draw on a display (OLED, TFT, etc.).

**Plugin Registration**:

- Plugins are registered in `IotApp` via `App.registerPlugin(...)`.
- Once registered, they will be automatically `setup()` and `start()` in the platform’s initialization sequence.
- A plugin can also register or spawn its own tasks for scheduling repeated or event-driven actions.

---

## Task System

Most plugins rely on **`TaskClass`** (or `Task<T>` templated class) to schedule:

- **Periodic tasks** with intervals (e.g. 1 second).
- **Single-shot tasks** that run once after an initial delay.
- **Paused/resume** functionality.
- Pinning to a specific ESP32 core (`coreId`).
- Exact timing vs. yield-based timing.

**Key APIs** in `TaskClass`:

- `configure(interval, stackSize, priority, coreId, useExactTiming, allowDuringOTA, initialDelay)`
- `start() / pause() / resume() / remove()`
- `_executeIfAllowed()` — an internal guard to skip runs if paused or in an OTA update.

Any plugin can:

1. Subclass `TaskClass` (or use `Task<PluginType>`) to create a periodic job.
2. Start the task inside `setup()` or `start()`.
3. Implement the `execute()` routine that is called each time the task fires.

---

## Supported Plugins and Features

Below is a summary of all major plugins/features discovered in this project. Many are **conditioned** by `#if CONFIG_ENABLE_...` macros in `sdkconfig` or Kconfig defaults.

> **Note**: Not all plugins must be enabled at once. Each plugin can be individually toggled via build config to keep firmware lean.

### Console Plugin

- **Macro**: `CONFIG_ENABLE_CONSOLE_PLUGIN`
- **Description**: Provides a **serial console** interface (via UART). It integrates with [linenoise](https://github.com/esp8266/Arduino/tree/master/tools/linenoise) for command history, completion, etc.
- **Features**:
  - Supports live command input on serial
  - Basic console commands (`help`, `meminfo`, etc.)
  - Ties into the `CommandPlugin` for additional commands

### Command Plugin

- **Macro**: `CONFIG_ENABLE_COMMANDS_PLUGIN`
- **Description**: Allows execution of text-based **commands** from multiple sources (serial console, websockets, MQTT messages, etc.).
- **Features**:
  - Provides a unified `handleCommand(const std::string&)`.
  - Built-in commands: `help`, `tasks`, `heap`, `ip`, `vcc`, `reset`, `version`, and more.
  - Simplifies creating new commands in a centralized place.

### Button Plugin

- **Macro**: `CONFIG_ENABLE_BUTTON_PLUGIN`
- **Description**: Manages **button inputs** (GPIO pins). Each button is an instance of `IotButton`.
- **Features**:
  - Schedules a background task to handle debouncing or event polling
  - Allows hooking custom callbacks on button press

### SecureOTA Plugin

- **Macro**: `CONFIG_ENABLE_SECURE_OTA_PLUGIN`
- **Description**: Handles **firmware over-the-air** updates, with optional:
  - HTTPS downloads
  - MD5 or SHA256 checks
  - **Rollback** support and verification
- **Workflow**:
  - On receiving an MQTT message with OTA details, it suspends non-critical tasks, downloads new firmware, and if successful, reboots into the new image.

### Camera Server Plugin

- **Macro**: `CONFIG_ENABLE_CAMERA_SERVER_PLUGIN`
- **Description**: Sets up a minimal **HTTP server** that can serve camera frames or respond to a basic route (`/`).

### HTTPS Server Plugin

- **Macro**: `CONFIG_ENABLE_HTTPS_SERVER_PLUGIN`
- **Description**: Embedded **HTTPS** server built on [httpsserver library](https://github.com/fhessel/esp32_https_server).
- **Features**:
  - Creates a self-signed certificate
  - Serves static or dynamic content over TLS
  - Example handler for root `/` endpoint

### BLE Beacon Plugin

- **Macro**: `CONFIG_ENABLE_BLE_BEACON`
- **Description**: Configures an **iBeacon** on the ESP32 that broadcasts a custom UUID, major/minor, etc.
- **Features**:
  - Use `btStart()` internally
  - Advertise indefinite iBeacon data
  - Optionally releases BT Classic memory

### BLE Keyboard Plugin

- **Macro**: `CONFIG_ENABLE_BLE_KEYBOARD_PLUGIN`
- **Description**: Emulates a **BLE HID keyboard** that can send key presses (including media keys).
- **Features**:
  - Uses NimBLE or Bluedroid under the hood
  - `sendKey()`, `sendMediaKey()` for controlling remote devices from MQTT commands
  - Pairing/bonding optional

### NimBLE Plugin

- **Macro**: `CONFIG_ENABLE_NIMBLE_PLUGIN`
- **Description**: Enables the **NimBLE** stack for BLE operations (lightweight alternative to Classic).
- **Features**:
  - Creates a basic iBeacon advertisement
  - Hooks into the standard NimBLE host tasks

### MDNS Plugin

- **Macro**: `CONFIG_ENABLE_MDNS_PLUGIN`
- **Description**: Registers an **mDNS** service so the device can be discovered locally via `deviceid.local`.
- **Features**:
  - Optionally includes additional mDNS service TXT records (version, environment, etc.)

### OLED Display Plugin

- **Macro**: `CONFIG_ENABLE_I2C_OLED_DISPLAY_PLUGIN`
- **Description**: Manages a **SSD1306/SH1106** or similar small OLED display over I2C.
- **Features**:
  - Uses `OLEDDisplayUi` for frames and overlays
  - Automatic progress bar for e.g. OTA
  - `addFramesAndOverlays()` allows each plugin to draw a portion of the UI

### SPI Display Plugin

- **Macro**: `CONFIG_ENABLE_SPI_DISPLAY_PLUGIN`
- **Description**: Uses **spilcd** driver for ST7789 or similar SPI-based LCD.
- **Features**:
  - Screen saver example
  - Optional backbuffer
  - Rotation settings

### TFT Display Plugin

- **Macro**: `CONFIG_ENABLE_TFT_DISPLAY`
- **Description**: Manages a **TFT_eSPI**-driven display (e.g. ILI9341, ST7735, ST7789).
- **Features**:
  - Basic UI overlays, progress bars, screen saver
  - Adjust backlight brightness
  - Rotation toggles

### Garage Plugin

- **Macro**: `CONFIG_ENABLE_GARAGE_PLUGIN`
- **Description**: Simple **garage door** opener plugin using a relay or GPIO toggle.
- **Features**:
  - MQTT command to `toggle` or `double_toggle`
  - Delays to simulate relay press

### GPS Plugin

- **Macro**: `CONFIG_ENABLE_GPS_PLUGIN`
- **Description**: Reads data from an attached **GPS** (e.g. UART NMEA).
- **Features**:
  - Uses `TinyGPS++`
  - Maintains average speed, max speed, satellite info
  - Can draw overlays on TFT display

### Hobbywing Task Plugin

- **Macro**: `CONFIG_ENABLE_HOBBYWING_TASK_PLUGIN`
- **Description**: Interacts with a **Hobbywing** ESC or car ESC over a UART or TTL signal.
- **Features**:
  - Captures raw data frames from ESC
  - Example logging of data (RPM, voltage, etc.)

### IR Plugin

- **Macro**: `CONFIG_ENABLE_IR_PLUGIN`
- **Description**: Transmits **38kHz IR** signals for devices (e.g. TVs or AC).
- **Features**:
  - `send_nec()` and `send_lg_ac()` examples
  - Mark/space approach at 38kHz using raw GPIO toggling

### RF Raw Plugin

- **Macro**: `CONFIG_ENABLE_RF_RAW_PLUGIN`
- **Description**: Captures raw edges from an **RF** receiver pin, logs timing for further decode.
- **Features**:
  - Attaches interrupt
  - Collects microsecond-level timing for analysis

### RF Sniffer Plugin

- **Macro**: `CONFIG_ENABLE_RF_SNIFFER_PLUGIN`
- **Description**: Uses a 433/315MHz receiving library to decode pulses into recognizable codes (like “RC Switch” style codes).
- **Features**:
  - Publishes discovered codes via MQTT
  - Optional raw capturing

### RF Transmit Plugin

- **Macro**: `CONFIG_ENABLE_RF_TRANSMIT_PLUGIN`
- **Description**: Transmits 433/315MHz codes (like RC Switch).
- **Features**:
  - MQTT command to send a code with a given bit length, pulse length, protocol, sync factors

### Hunter Fan Plugin

- **Macro**: `CONFIG_ENABLE_HUNTER_FAN_PLUGIN`
- **Description**: Sends **Hunter Fan**-style remote codes via a certain timing pattern on a GPIO.
- **Features**:
  - Supports a specific pulse logic for older Hunter fans

### Acurite Sensor Plugin

- **Macro**: `CONFIG_ENABLE_ACURITE_SENSOR_PLUGIN`
- **Description**: Work in progress to decode **Acurite temperature/humidity** sensor signals in the 433MHz band.

### Servo Input Plugin

- **Macro**: `CONFIG_ENABLE_SERVO_INPUT_PLUGIN`
- **Description**: Uses **RMT** to read servo pulses from an RC receiver.
- **Features**:
  - Multiple channels
  - Each channel has a `duty()` or pulse width in microseconds
  - Notifies changes via a background task

### NTP Plugin

- **Macro**: `CONFIG_ENABLE_SNTP_PLUGIN`
- **Description**: Synchronizes system time via **NTP** servers.
- **Features**:
  - Automatic updates after Wi-Fi is connected
  - Timezone support, time sync callback
  - Can show a time overlay on TFT or OLED

### SPIFFS Plugin

- **Macro**: `CONFIG_ENABLE_SPIFFS_PLUGIN`
- **Description**: Initializes **SPIFFS** filesystem.
- **Features**:
  - Formats on failure (if needed)
  - Logs total/used space

### Secure Websocket Plugin

- **Macro**: `CONFIG_ENABLE_SECURE_WEBSOCKET_PLUGIN`
- **Description**: Creates an **HTTPS** server with **websocket** capability on port 443, using a certificate/key stored in the firmware.
- **Features**:
  - 2-way TLS
  - Real-time data over wss

### WebSocketCommand Plugin

- **Macro**: `CONFIG_ENABLE_WEBSOCKET_COMMAND_PLUGIN`
- **Description**: Allows receiving console-like **commands** over a websocket (usually on some port).
- **Features**:
  - Forwards lines to the `CommandPlugin::handleCommand()`

### WebSocketServer Plugin

- **Macro**: `CONFIG_ENABLE_WEBSOCKET_SERVER_PLUGIN`
- **Description**: Similar to above, but might run on a simpler or different port (e.g. `81` or `8081`).
- **Features**:
  - Echo or dispatch commands
  - Maintains a map of connected clients

### WebsocketClient Plugin

- **Macro**: `CONFIG_ENABLE_WEBSOCKET_CLIENT_PLUGIN`
- **Description**: Connects to a remote **wss** server from the device as a **client**.
- **Features**:
  - Periodic keepalive
  - Data exchange in real-time

### ConnectionStats Plugin

- **Macro**: `CONFIG_ENABLE_CONNECTION_STATS_PLUGIN`
- **Description**: Tracks **Wi-Fi** and **MQTT** connect/disconnect events:
  - Number of drops
  - Time of last connect
  - Optionally logs or publishes stats

### RSSI Plugin

- **Macro**: `CONFIG_ENABLE_RSSI_STATS_PLUGIN`
- **Description**: Periodically polls Wi-Fi **RSSI** (signal strength).
- **Features**:
  - Publishes min / max / average RSSI after a configurable interval
  - Optional logs

### WifiScan Plugin

- **Macro**: `CONFIG_ENABLE_WIFI_SCAN_PLUGIN`
- **Description**: Scans for **nearby APs** either on each channel or a single channel, then publishes results over MQTT.
- **Features**:
  - Passive scanning
  - Displays SSID, RSSI, channel, auth mode

### Example Basic Plugin

- **Macro**: `CONFIG_ENABLE_EXAMPLE_BASIC_PLUGIN`
- **Description**: A minimal plugin example with basic `setup()`/`start()` stubs.

### Example Task Plugin

- **Macro**: `CONFIG_ENABLE_EXAMPLE_TASK_PLUGIN`
- **Description**: Demonstrates scheduling an internal `TaskClass` to run periodically.

### Example Sensor Plugin

- **Macro**: `CONFIG_ENABLE_EXAMPLE_SENSOR_PLUGIN`
- **Description**: Illustrates a sensor plugin pattern with periodic polling and publishing (two tasks):
  - `pollTask`
  - `publishTask`

---

## Closing Notes

This platform is highly modular. Each plugin can be toggled on/off via build flags (`CONFIG_ENABLE_*`).  
Most plugins use their own `TaskClass` for concurrency.  
To add a new feature:

1. Subclass `IotPlugin`.
2. Implement `setup()`, `start()`, and any relevant hooks.
3. Optionally create a `Task<YourPlugin>` for periodic or event-based logic.
4. Register the plugin with `App.registerPlugin(new YourPlugin());`.

## Old README.md

Complete IoT platform for the ESP32 using ESP-IDF and FreeRTOS.

## Supported Devices
- IR
- RF 433mhz / 315mhz
- Hunter Fan Remote
- Temp / Humidity
- LG Portable AC
- Garage Opener
- Door Sensor (Reed Switch) x2


## Setup
### Install ESP-IDF
```shell
mkdir -p ~/esp
cd ~/esp
git clone --recurse-submodules --branch v4.0.2 git@github.com:espressif/esp-idf.git
cd esp-idf
./install.sh
```


## Wiring
### Notes
- `D0` appears to control an on board RED led on the NodeMCU boards
- `D4` controls the very bright blue light on the ESP-12E module


### Reed Switch
Plug one wire into `GND` and the other wire into a GPIO pin. `D0` and `D4` are some known working GPIO pins, however not all GPIO pins will work. Typically the reed switches I have are normally open switches, but this can be confirmed by running the software and checking.

### i2c
- Not all GPIO pins are good for i2c. Some known good ones are `D1`, `D2`, `D3`, `D4`, `D5`, `D6`.
- Auto detection is supported, just setup the `SDA_PIN` and `SCL_PIN`

### Relay
Wire into the Normally Open Pins which is the middle pin and the pin not connected by a white line. First and second pins if looking from the front.

### LCD Character Display
- Auto detect using i2c

### RF433 Receiver
- Connect GND, VCC to 5v (Vin), and the Digital Output pin to `D2` on the nodemcu.
  - From left to right it is:
  - `GND, D2, __, Vin, ................. __, __, __, (optional antenna)`

## Development
### Make targets
- Create a new basic plugin
  `make create-plugin name=<...> folder=<...>`
- Create a new Task plugin
  `make create-task-plugin name=<...> folder=<...>`

Note: `name` _should include_ the suffix of Plugin or whatever.
Note: `folder` is the sub-folder within plugins folder the plugin is to be put.

#### Docker
```shell
./docker-make.sh
```

### Serial
```shell
make udev-rules
```
