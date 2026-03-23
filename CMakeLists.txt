cmake_minimum_required(VERSION 3.20)

project(TermEdit VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(termed_core
    src/TextBuffer.cpp
    src/Editor.cpp
    src/Renderer.cpp
    src/Terminal.cpp
)

target_include_directories(termed_core
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_executable(termed
    app/main.cpp
)

target_link_libraries(termed
    PRIVATE termed_core
)

target_compile_options(termed_core PRIVATE
    -Wall
    -Wextra
    -Wpedantic
)

# option(TERMED_BUILD_TESTS "Build TermEdit tests" ON)
#
# if(TERMED_BUILD_TESTS)
#   enable_testing()
#   add_subdirectory(tests)
# endif()
