add_library(wenzi_core
  src/document.cpp
  src/document_io.cpp
  src/layout.cpp
)

target_include_directories(wenzi_core
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_executable(wenzi_core_tests
  tests/document_test.cpp
)

target_link_libraries(wenzi_core_tests
  PRIVATE
    wenzi_core
)

add_test(
  NAME wenzi_core_tests
  COMMAND wenzi_core_tests
)
