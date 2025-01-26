idf_component_register(
    SRCS "TinyGPSPlus/src/TinyGPS++.cpp"
    INCLUDE_DIRS "TinyGPSPlus/src"
    REQUIRES arduino
)

component_compile_options(
  -Wno-implicit-fallthrough
)
