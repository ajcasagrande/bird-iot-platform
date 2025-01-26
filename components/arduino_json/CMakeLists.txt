set(COMPONENT_SRCS
  "ArduinoJson.cpp"
)

set(COMPONENT_ADD_INCLUDEDIRS
  "ArduinoJson"
  "ArduinoJson/src"
)

set(COMPONENT_REQUIRES
  arduino
)

register_component()
