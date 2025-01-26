# Bird IoT

Complete IoT platform for the ESP32 using ESP-IDF and FreeRTOS.

> **Note:** This documentation is very outdated, and the project is not seeing any regular updates.
> The intent of this repo is to share the concepts and code within, and not a fully working production system.

> **Note:** Be sure to configure your authorization headers. Look for _TODO__ in the codebase

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
