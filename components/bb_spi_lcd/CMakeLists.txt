idf_component_register(
    SRCS "bb_spi_lcd/src/bb_spi_lcd.cpp"
    INCLUDE_DIRS "bb_spi_lcd/src"
    REQUIRES arduino
)

component_compile_options(
    -Wno-unused-variable
)
