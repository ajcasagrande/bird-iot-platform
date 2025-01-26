set(COMPONENT_SRCS
  "DHT-sensor-library/DHT.cpp"
  "DHT-sensor-library/DHT_U.cpp"
)

set(COMPONENT_ADD_INCLUDEDIRS
  "DHT-sensor-library"
)

set(COMPONENT_REQUIRES
  arduino
  adafruit_sensor
)

register_component()
