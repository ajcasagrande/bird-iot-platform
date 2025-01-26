#include "HobbywingTaskPlugin.h"
#if CONFIG_ENABLE_HOBBYWING_TASK_PLUGIN

static const char* TAG = "Hobbywing Task";

HobbywingTaskPlugin HobbywingTask;

static void _execute(HobbywingTaskPlugin *plugin) {
  plugin->execute();
}

HobbywingTaskPlugin::HobbywingTaskPlugin() : IotPlugin("Hobbywing Task") {
  task = new Task<HobbywingTaskPlugin>("Hobbywing Task", this, _execute);
}

bool HobbywingTaskPlugin::setup() {
  hwSerial = new HardwareSerial(1);
  hwSerial->begin(115200, SERIAL_8N1, GPIO_NUM_27, GPIO_NUM_26);
  LOGD(TAG, "after setup Hobbywing serial");
  return task->configure(10, _2p5, MEDIUM_PRIORITY);
}
bool HobbywingTaskPlugin::start() {
  // todo
  return task->start();
}

void printHexArray(uint8_t* array, int length) {
    for (int i = 0; i < length; i++) {
        printf("%02X ", (unsigned char)array[i]);
    }
    printf("\n");
}

//void HobbywingTaskPlugin::execute() {
//    int numBytes = hwSerial->available();
//    if (numBytes == 0) {
//        return;
//    }
//    char* buff = (char*)malloc(sizeof(char)*numBytes);
//    for (int n = 0; n < numBytes; n++) {
//        buff[n] = hwSerial->read();
//    }
//    LOGD(TAG, "read " << numBytes << " bytes");
//    for (int n = 0; n < numBytes; n++) {
//        hwSerial->write(buff[n]);
//    }
//    LOGD(TAG, "wrote " << numBytes << " bytes");
//    printHexArray(buff, numBytes);
//    free(buff);
//}

void HobbywingTaskPlugin::printResult() {
  printHexArray(result, RESULT_SIZE);
}

void HobbywingTaskPlugin::handleBuffer() {
  bool isDupe = 0;
  if (memcmp(buffer, buffer1, BUFFER_SIZE*sizeof(uint8_t)) == 0) {
    // we have a dupe!
    isDupe = 1;
    dupeCount++;
    dupePrevMs = currMs;
    if (dupeCount < MAX_DUPES) {
      return;
    }
  }

    if (dupeCount > 0) {
      uint32_t diff = isDupe ? currMs - prevMs : dupePrevMs - prevMs;
      Serial.print(diff);
      Serial.print(",");
      Serial.println(dupeCount);
      dupeCount = 0;
      prevMs = dupePrevMs;
      if (isDupe) {
        prevMs = currMs;
        // we are still a dupe, but wanted to print out current progress
        return;
      }
    }

    result[0] = buffer[11];  // status: neutral=0, gas=1, brake=2
    result[1] = buffer[9];   // throttle input
    result[2] = buffer[10];  // throttle output
    result[3] = buffer[13];  // rpm low-byte
    result[4] = buffer[14];  // rpm high-byte
    result[5] = buffer[15];  // volt low-byte
    result[6] = buffer[16];  // volt high-byte
    result[7] = buffer[19];  // temperature
    result[8] = buffer[21];  // motorTemp

    uint32_t diff = prevMs == 0 ? 0 : currMs - prevMs;
    Serial.print(diff);
    Serial.print(",0,");
    printResult();

    prevMs = currMs;
    // copy to prev buffer
    memcpy(buffer1, buffer, BUFFER_SIZE*sizeof(uint8_t));
}


// TODO: NEED TO USE A 5V TO 3.3V LOGIC CONVERTER!

void HobbywingTaskPlugin::execute() {
  // Read data from Serial1 and print as hexadecimal
  while (hwSerial->available()) {
    uint8_t receivedByte = hwSerial->read();
    // Print each byte as a two-digit hexadecimal number
    // if (receivedByte < 0x10) {
    //   Serial.print("0"); // Print leading zero for single digit
    // }
    if (receivedByte == (uint8_t)0xFE) {
      // Serial.println();
      bufferIndex = 0;
      bufferFlag = true;
      currMs = micros();
    }
    // Serial.print(receivedByte, HEX);
    // Serial.print(" ");

      if (bufferFlag) {
        buffer[bufferIndex++] = receivedByte;
        if (bufferIndex >= BUFFER_SIZE) {
          // Call callback function to print buffer
          handleBuffer();
          // printBuffer();
          // writeBufferToFile();
          bufferFlag = false;
        }
      }
  }
}

//  void HobbywingTaskPlugin::onWifiConnected() { }
//  void HobbywingTaskPlugin::onWifiDisconnected() { }
//  void HobbywingTaskPlugin::onMqttConnected() { }
//  void HobbywingTaskPlugin::onMqttDisconnected() { }
//  bool HobbywingTaskPlugin::handleMqttMessage(const char *topic, int id, const char *cmd, const JsonDocument& json) {
//    return false; // false means not handled
//  }
//bool HobbywingTaskPlugin::handleCommand(const std::string& cmd) {
//  if (cmd == "Hobbywing Task") {
//    PUTLN("");
//
//  } else {
//    return false; // false means not handled
//  }
//
//  return true;
//}
#if ENABLE_I2C_OLED_DISPLAY_PLUGIN
//  void HobbywingTaskPlugin::addFramesAndOverlays() { }
#endif

#endif // CONFIG_ENABLE_HOBBYWING_TASK_PLUGIN
