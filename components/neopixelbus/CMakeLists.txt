idf_component_register(
    SRCS
        "NeoPixelBus/src/internal/HsbColor.cpp"
        "NeoPixelBus/src/internal/HslColor.cpp"
        "NeoPixelBus/src/internal/HtmlColor.cpp"
        "NeoPixelBus/src/internal/HtmlColorNames.cpp"
        "NeoPixelBus/src/internal/HtmlColorNameStrings.cpp"
        "NeoPixelBus/src/internal/HtmlColorShortNames.cpp"
        "NeoPixelBus/src/internal/NeoEsp8266UartMethod.cpp"
        "NeoPixelBus/src/internal/NeoGamma.cpp"
        "NeoPixelBus/src/internal/NeoPixelAnimator.cpp"
        "NeoPixelBus/src/internal/RgbColor.cpp"
        "NeoPixelBus/src/internal/RgbwColor.cpp"
        "NeoPixelBus/src/internal/SegmentDigit.cpp"

    INCLUDE_DIRS
      "NeoPixelBus/src"
      "NeoPixelBus/src/internal"

    REQUIRES
      arduino
)

component_compile_options(
    -Wno-ignored-qualifiers
)
