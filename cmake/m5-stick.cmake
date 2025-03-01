add_definitions_pretty(
    -D BUTTON_A=37
    -D BUTTON_B=39

    # TFT-eSPI setup
    -D USER_SETUP_LOADED=1
    -D ST7735_DRIVER=1
    -D TFT_DRIVER=0x7735
    -D ST7735_GREENTAB160x80=1
    -D INITR_GREENTAB160x80=0x6
    -D TAB_COLOUR=INITR_GREENTAB160x80

    -D TFT_WIDTH=80
    -D TFT_HEIGHT=160

    -D TFT_MISO=-1
    -D TFT_MOSI=15
    -D TFT_SCLK=13
    -D TFT_CS=5
    -D TFT_DC=23
    -D TFT_RST=18

    -D LOAD_GFXFF=1
    -D SPI_FREQUENCY=27000000
    -D SPI_READ_FREQUENCY=20000000
    -D SPI_TOUCH_FREQUENCY=2500000
)
