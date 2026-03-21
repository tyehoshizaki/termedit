add_executable(
  termedit
  PRIVATE
    termedit_core
)

target_link_libraries(
  termedit
  PRIVATE
    termedit_core
)

set_target_properties(
  termedit PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
