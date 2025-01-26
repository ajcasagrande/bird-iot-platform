set(COMPONENT_SRCS
  "Arduino-Temperature-Control-Library/DallasTemperature.cpp"
)

set(COMPONENT_ADD_INCLUDEDIRS
  "Arduino-Temperature-Control-Library"
)

set(COMPONENT_REQUIRES
  arduino
  onewire
)

register_component()
