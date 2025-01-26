set(COMPONENT_SRCS
  "ESP32_I2C_Slave/src/WirePacker.cpp"
  "ESP32_I2C_Slave/src/WireSlave.cpp"
  "ESP32_I2C_Slave/src/WireSlaveRequest.cpp"
  "ESP32_I2C_Slave/src/WireUnpacker.cpp"
)

set(COMPONENT_ADD_INCLUDEDIRS
  "ESP32_I2C_Slave/src"
)

set(COMPONENT_REQUIRES
  arduino
)

register_component()
