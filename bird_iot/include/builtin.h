#pragma once

#include <Arduino.h>
#include <Streaming.h>

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <soc/soc.h>
#include <soc/rtc_cntl_reg.h>
#include <pins_arduino.h>

#include <string>
#include <functional>

// this is to prevent TFT_eSPI library from defining it as a macro
#ifndef min
#define min min
#endif
