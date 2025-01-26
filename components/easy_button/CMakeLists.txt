set(COMPONENT_SRCS
  "EasyButton/src/EasyButton.cpp"
  "EasyButton/src/EasyButtonTouch.cpp"
)

set(COMPONENT_ADD_INCLUDEDIRS
  "EasyButton/src"
)

set(COMPONENT_REQUIRES
  arduino
)

register_component()

component_compile_options(
    -DEASYBUTTON_FUNCTIONAL_SUPPORT=1
)
