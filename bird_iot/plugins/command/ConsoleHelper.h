#pragma once

#define MOUNT_PATH "/data"
#define HISTORY_PATH MOUNT_PATH "/history.txt"

#include "esp_err.h"

esp_err_t initialize_filesystem();
esp_err_t initialize_uart();
esp_err_t initialize_console();
