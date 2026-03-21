add_executable(
  text_buffer_tests
  TextBufferTests.cpp
)

target_link_libraries(
  text_buffer_tests
  PRIVATE
    termedit_core
)

add_test(
  NAME text_buffer_tests
  COMMAND text_buffer_tests
)
