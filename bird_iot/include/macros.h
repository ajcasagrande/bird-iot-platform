#pragma once

#include <string>

#define quote(val, ...) #val __VA_ARGS__

#define DBG_FILE_LINE __FILE__ "#" << __func__ << ":" << __LINE__

#define json_lambda(items, context, code) JSON_OBJECT_SIZE(items), [context](JsonObject js) {code;}

#define REQUIRE_VALID_OUTPUT_PIN(pin)  if (!GPIO_IS_VALID_OUTPUT_GPIO(pin)) { LOGE(TAG, #pin " " << pin << " is not a valid output gpio pin!"); return false; }

#define err_check(code, successCode, failCode) { esp_err_t err = code; if (err != ESP_OK) { LOGE(TAG, "Error @ " << DBG_FILE_LINE << " -- " << esp_err_to_name(err)); failCode; } else { successCode; } }

#define err_return_false(code) err_check(code, , return false;)
#define return_err_bool(code) err_check(code, return true;, return false;)
