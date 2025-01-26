#include "ServoInputPlugin.h"
#if CONFIG_ENABLE_SERVO_INPUT_PLUGIN

static const char* TAG = "Servo";

ServoInputPlugin ServoInput;

// this file configure the RMT for 2 purposes:
// - Reading the pulse widths of the servo signal from the RC receiver
// - Reading the pulse widths of the hall effect sensors in the motor

static void IRAM_ATTR rmt_isr_handler(void* arg) {
  // with reference to https://www.esp32.com/viewtopic.php?t=7116#p32383
  // but modified so that this ISR only checks chX_rx_end
  uint32_t state = RMT.int_st.val;

  // see declaration of RMT.int_st:
  // takes the form of
  // bit 0: ch0_tx_end
  // bit 1: ch0_rx_end
  // bit 2: ch0_err
  // bit 3: ch1_tx_end
  // bit 4: ch1_rx_end
  // ...
  // thus, check whether bit (channel*3 + 1) is set to identify
  // whether that channel has changed

  bool changed = false;
  for (auto & c : ServoInput.channels) {
    uint8_t channelNum = c->channel;
    uint32_t channel_mask = BIT((channelNum * 3) + 1);

    if (!(state & channel_mask)) {
      continue;
    }

    RMT.conf_ch[channelNum].conf1.rx_en = 0;
    RMT.conf_ch[channelNum].conf1.mem_owner = RMT_MEM_OWNER_TX;
    volatile rmt_item32_t* item = RMTMEM.chan[channelNum].data32;
    if (item) {
      if (c->value != item->duration0) {
        // only set changed state if true, clearing is handled by the checker task
        c->changed = true;
        changed = true;
      }
      c->prevValue = c->value;
      c->value = item->duration0;
    }

    RMT.conf_ch[channelNum].conf1.mem_wr_rst = 1;
    RMT.conf_ch[channelNum].conf1.mem_owner = RMT_MEM_OWNER_RX;
    RMT.conf_ch[channelNum].conf1.rx_en = 1;

    // clear RMT interrupt status.
    RMT.int_clr.val = channel_mask;
  }

  if (changed) {
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    xTaskNotifyFromISR(ServoInput.task->getHandle(),
                       0x1,
                       eSetBits,
                       &xHigherPriorityTaskWoken);

    if (xHigherPriorityTaskWoken == pdTRUE) {
      portYIELD_FROM_ISR();
    }
  }
}

static bool logEnabled = false;

static void _execute() {
  uint32_t ulInterruptStatus;
  xTaskNotifyWait(0x00,               /* Don't clear any bits on entry. */
                  ULONG_MAX,          /* Clear all bits on exit. */
                  &ulInterruptStatus, /* Receives the notification value. */
                  portMAX_DELAY);    /* Block indefinitely. */

  for (auto & c : ServoInput.channels) {
    if (c->changed) {
      c->changed = false;
      if (logEnabled) {
        LOGD(TAG, "Servo: " << c->name << ", channel: " << c->channel << ", value: " << c->value << ", duty: " << c->duty());
      }
    }
  }
}

ServoInputPlugin::ServoInputPlugin()
    : IotPlugin("Servo Input Plugin") {
  task = new VoidTask("Servo Input", _execute);
}

bool ServoInputPlugin::setup() {
  if (ServoInput.numChannels() == 0) {
    LOGE(TAG, "No channels have been configured for servo input");
    return false;
  }

  for (auto & c : ServoInput.channels) {
    rmt_config_t rmtConfig;
    memset(&rmtConfig, 0, sizeof(rmt_config_t));

    rmtConfig.channel = (rmt_channel_t) c->channel;
    rmtConfig.gpio_num = (gpio_num_t) c->pin;
    rmtConfig.clk_div = RMT_RX_CLK_DIV;
    rmtConfig.mem_block_num = 1;
    rmtConfig.rmt_mode = RMT_MODE_RX;
    rmtConfig.rx_config.filter_en = true;
    rmtConfig.rx_config.filter_ticks_thresh = 100;
    rmtConfig.rx_config.idle_threshold = RMT_RX_MAX_US * RMT_TICK_PER_US;

    LOGD(TAG, "Configuring servo channel " << c->name << " (ch " << c->channel << ") on pin " << c->pin);

    err_return_false(rmt_config(&rmtConfig));
    err_return_false(rmt_set_rx_intr_en(rmtConfig.channel, true));
    err_return_false(rmt_rx_start(rmtConfig.channel, 1));
  }

  return task->configure(25, _1p5);
}

bool ServoInputPlugin::start() {
//#if CONFIG_ENABLE_NEOPIXEL_DRIVER
//  rmt_driver_uninstall(RMT_CHANNEL_6);
//#endif

  err_return_false(rmt_isr_register(rmt_isr_handler, nullptr, 0, nullptr));
  return task->start();
}

//  void ServoInputPlugin::onWifiConnected() { }
//  void ServoInputPlugin::onWifiDisconnected() { }
//  void ServoInputPlugin::onMqttConnected() { }
//  void ServoInputPlugin::onMqttDisconnected() { }
//  bool ServoInputPlugin::handleMqttMessage(const char *topic, int id, const char *cmd, const JsonDocument& json) {
//   return false; // false means not handled 
// }
bool ServoInputPlugin::handleCommand(const std::string& cmd) {
  if (cmd == "servos" || cmd == "servo") {
    for (auto &c : ServoInput.channels) {
      PUTLN("Servo: " << c->name << ", channel: " << c->channel << ", value: " << c->value << ", duty: " << c->duty());
    }

  } else if (cmd == "servo log" || cmd == "log servo" || cmd == "log servos") {
    logEnabled = !logEnabled;

  } else {
    return false;
  }
  return true;
}
#if ENABLE_I2C_OLED_DISPLAY_PLUGIN
//  void ServoInputPlugin::addFramesAndOverlays() { }
#endif

#endif // CONFIG_ENABLE_SERVO_INPUT_PLUGIN
