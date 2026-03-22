add_library(wenzi_core
  src/document.cpp
  src/layout.cpp
)

target_include_directories(wenzi_core
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
