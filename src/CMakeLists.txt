add_library(termedit_core
  Editor.cpp
  Renderer.cpp
  Terminal.cpp
  TextBuffer.cpp
)

target_include_directories( 
  termedit_core
  PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)

target_compile_features(
  termedit_core
  PUBLIC
    cxx_std_20
)
