add_library(wenzi_ui
  src/application_mac.mm
)

target_include_directories(wenzi_ui
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(wenzi_ui
  PUBLIC
    wenzi_core
  PRIVATE
    "-framework Cocoa"
)
