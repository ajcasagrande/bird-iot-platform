function(add_definitions_pretty)
  set(temp_defs "${ARGN}")
  string(REPLACE "-D;" "-D'" temp_defs "${temp_defs}")
  string(REPLACE "-Wn" "-W'n" temp_defs "${temp_defs}")
  string(REPLACE "-W;" "-W'" temp_defs "${temp_defs}")
  string(REPLACE "-I;" "-I'" temp_defs "${temp_defs}")
  string(REPLACE ";" "' " temp_defs "${temp_defs}")
  message("ADDING DEFINITIONS: ${temp_defs}'")
  add_definitions("${temp_defs}'")
endfunction()

include(${CMAKE_SOURCE_DIR}/../../cmake/project.cmake)
include(${CMAKE_SOURCE_DIR}/../../cmake/arduino.cmake)
include(${CMAKE_SOURCE_DIR}/../../cmake/idf.cmake)

set(COMPONENTS
    ${BASE_IDF_COMPONENTS}
    bird_iot
    ${EXTRA_COMPONENTS}
    )
