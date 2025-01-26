set(COMPONENT_SRCS
  "arduinoWebSockets/src/SocketIOclient.cpp"
  "arduinoWebSockets/src/WebSocketsClient.cpp"
  "arduinoWebSockets/src/WebSockets.cpp"
  "arduinoWebSockets/src/WebSocketsServer.cpp"
)

set(COMPONENT_ADD_INCLUDEDIRS
  "arduinoWebSockets/src"
  "arduinoWebSockets/src/libb64"
  "arduinoWebSockets/src/libsha1"
)

set(COMPONENT_REQUIRES
  arduino
)

register_component()

component_compile_options(
    -DWEBSOCKETS_TCP_TIMEOUT=\(10000\)

    -Wno-implicit-fallthrough
)
