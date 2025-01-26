set(COMPONENT_SRCS
  "OneWire/OneWire.cpp"
)

set(COMPONENT_ADD_INCLUDEDIRS
  "OneWire"
  "OneWire/util"
)

set(COMPONENT_REQUIRES
  arduino
)

register_component()

component_compile_options(
    -Wno-unused-variable
)
