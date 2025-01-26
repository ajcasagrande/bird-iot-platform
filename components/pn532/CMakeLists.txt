idf_component_register(
  SRCS
    "PN532/PN532/emulatetag.cpp"
    "PN532/PN532_I2C/PN532_I2C.cpp"
    "PN532/PN532/llcp.cpp"
    "PN532/PN532/mac_link.cpp"
    "PN532/PN532/PN532.cpp"
    "PN532/PN532/snep.cpp"

  INCLUDE_DIRS
    "."
    "PN532/PN532"
    "PN532/PN532_I2C"

  REQUIRES arduino
)

component_compile_options(
    -Wno-maybe-uninitialized
    -Wno-unused-variable
    -Wno-narrowing
)
