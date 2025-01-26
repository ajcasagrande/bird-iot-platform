set(COMPONENT_SRCS
  "M5StickC/src/AXP192.cpp"
#  "M5StickC/src/Fonts/Font16.c"
#  "M5StickC/src/Fonts/Font32rle.c"
#  "M5StickC/src/Fonts/Font64rle.c"
#  "M5StickC/src/Fonts/Font72rle.c"
#  "M5StickC/src/Fonts/Font7srle.c"
#  "M5StickC/src/Fonts/glcdfont.c"
  "M5StickC/src/IMU.cpp"
#  "M5StickC/src/M5Display.cpp"
#  "M5StickC/src/M5StickC.cpp"
  "M5StickC/src/RTC.cpp"
#  "M5StickC/src/utility/Button.cpp"
  "M5StickC/src/utility/CommUtil.cpp"
#  "M5StickC/src/utility/In_eSPI.cpp"
  "M5StickC/src/utility/MahonyAHRS.cpp"
  "M5StickC/src/utility/MPU6886.cpp"
  "M5StickC/src/utility/qrcode.c"
  "M5StickC/src/utility/SH200Q.cpp"
#  "M5StickC/src/utility/Sprite.cpp"
)

set(COMPONENT_ADD_INCLUDEDIRS
  "M5StickC/src"
#  "M5StickC/src/Fonts"
#  "M5StickC/src/Fonts/Custom"
#  "M5StickC/src/Fonts/GFXFF"
  "M5StickC/src/utility"
)

set(COMPONENT_REQUIRES
  arduino
)

register_component()
