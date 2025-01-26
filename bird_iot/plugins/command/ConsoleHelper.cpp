#include "ConsoleHelper.h"
#include "sdkconfig.h"

#if CONFIG_ENABLE_CONSOLE_PLUGIN

#include "esp_console.h"
#include "esp_vfs_dev.h"
#include "driver/uart.h"
#include "linenoise/linenoise.h"
#include "argtable3/argtable3.h"
#if CONFIG_STORE_HISTORY
#include "esp_spiffs.h"
#endif

// hack to get it to not warn about re-defined macros
#define Binary_h
#include "include/logging.h"

static const char* TAG = "Console";

/* Console command history can be stored to and loaded from a file.
 * The easiest way to do this is to use FATFS filesystem on top of
 * wear_levelling library.
 */
#if CONFIG_STORE_HISTORY

esp_err_t initialize_filesystem() {
    esp_vfs_spiffs_conf_t mount_config;
    memset(&mount_config, 0, sizeof(mount_config));
    mount_config.max_files = 4;
    mount_config.format_if_mount_failed = true;
    mount_config.base_path = MOUNT_PATH;
    esp_err_t err = esp_vfs_spiffs_register(&mount_config);
    if (err != ESP_OK) {
        LOGE(TAG, "Failed to mount SPIFFS: " << esp_err_to_name(err));
        return err;
    }
    return ESP_OK;
}
#else
esp_err_t initialize_filesystem() { return ESP_OK; }
#endif // CONFIG_STORE_HISTORY

esp_err_t initialize_uart() {
  /* Disable buffering on stdin */
  setvbuf(stdin, NULL, _IONBF, 0);

  /* Minicom, screen, idf_monitor send CR when ENTER key is pressed */
  esp_vfs_dev_uart_set_rx_line_endings(ESP_LINE_ENDINGS_CR);
  /* Move the caret to the beginning of the next line on '\n' */
  esp_vfs_dev_uart_set_tx_line_endings(ESP_LINE_ENDINGS_CRLF);

  /* Configure UART. Note that REF_TICK is used so that the baud rate remains
    * correct while APB frequency is changing in light sleep mode.
    */
  const uart_config_t uart_config = {
    .baud_rate = CONFIG_ESP_CONSOLE_UART_BAUDRATE,
    .data_bits = UART_DATA_8_BITS,
    .parity = UART_PARITY_DISABLE,
    .stop_bits = UART_STOP_BITS_1,
    .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
    .rx_flow_ctrl_thresh = 0,
    .use_ref_tick = true
  };
  esp_err_t err = uart_param_config((uart_port_t)CONFIG_ESP_CONSOLE_UART_NUM, &uart_config);
  if (err != ESP_OK) {
    LOGE(TAG, "uart_param_config failed: " << esp_err_to_name(err));
    return err;
  }

  /* Install UART driver for interrupt-driven reads and writes */
  err = uart_driver_install((uart_port_t)CONFIG_ESP_CONSOLE_UART_NUM, 256, 0, 0, NULL, 0);
  if (err != ESP_OK) {
    LOGE(TAG, "uart_driver_install failed: " << esp_err_to_name(err));
    return err;
  }

  /* Tell VFS to use UART driver */
  esp_vfs_dev_uart_use_driver(CONFIG_ESP_CONSOLE_UART_NUM);

  return ESP_OK;
}

esp_err_t initialize_console() {
  /* Initialize the console */
  esp_console_config_t console_config;
  memset(&console_config, 0, sizeof(console_config));
  console_config.max_cmdline_args = 8;
  console_config.max_cmdline_length = 256;
#if CONFIG_LOG_COLORS
  console_config.hint_color = atoi(LOG_COLOR_CYAN);
#endif

  esp_err_t err = esp_console_init(&console_config);
  if (err != ESP_OK) {
    ESP_LOGE(TAG, "esp_console_init failed (%s)", esp_err_to_name(err));
    return err;
  }

  /* Configure linenoise line completion library */
  /* Enable multiline editing. If not set, long commands will scroll within
    * single line.
    */
  linenoiseSetMultiLine(1);

  /* Tell linenoise where to get command completions and hints */
  linenoiseSetCompletionCallback(&esp_console_get_completion);
  linenoiseSetHintsCallback((linenoiseHintsCallback*) &esp_console_get_hint);

  /* Set command history size */
  linenoiseHistorySetMaxLen(100);

#if CONFIG_STORE_HISTORY
  /* Load command history from filesystem */
  linenoiseHistoryLoad(HISTORY_PATH);
#endif

  return ESP_OK;
}

#endif // CONFIG_ENABLE_CONSOLE_PLUGIN
