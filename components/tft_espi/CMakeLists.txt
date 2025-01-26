idf_component_register(
  SRCS "TFT_eSPI/TFT_eSPI.cpp"
  INCLUDE_DIRS "TFT_eSPI"
  REQUIRES arduino
)

component_compile_options(
    -Wno-unused-variable
)
