add_executable(wenzi
  src/main.cpp
)

target_link_libraries(wenzi
  PRIVATE
    wenzi_ui
)
