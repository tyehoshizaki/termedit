# TermEdit

A terminal-based text editor written in C++.

TermEdit is a project built to learn how Vim-like editors work under the hood. It focuses on terminal rendering, cursor movement, text-buffer management, viewport scrolling, and modular C++ design. The goal is to build a small but well-structured editor that demonstrates both systems programming concepts and software engineering practices.

## Goals

This project is meant to:

- learn practical C++ through a real project
- understand how terminal applications control the screen
- implement a text buffer and screen buffer
- explore cursor movement, scrolling, and rendering
- build a project that is useful as a portfolio and resume piece

## Current Features

- terminal-based interface
- modular C++ project structure
- CMake build system
- text buffer foundation
- planned support for cursor movement, editing, scrolling, and file I/O

## Planned Features

- cursor movement with keyboard controls
- character insertion and deletion
- multi-line text editing
- viewport scrolling
- status bar
- file open and save
- screen-buffer-based redraw system
- search
- syntax highlighting
- undo and redo

## Project Structure

```text
TermEdit/
├── CMakeLists.txt
├── CMakePresets.json
├── .gitignore
├── README.md
├── docs/
│   └── architecture.md
├── include/
│   └── termedit/
│       ├── Editor.hpp
│       ├── Renderer.hpp
│       ├── Terminal.hpp
│       └── TextBuffer.hpp
├── src/
│   ├── CMakeLists.txt
│   ├── Editor.cpp
│   ├── Renderer.cpp
│   ├── Terminal.cpp
│   └── TextBuffer.cpp
├── app/
│   ├── CMakeLists.txt
│   └── main.cpp
└── tests/
    ├── CMakeLists.txt
    └── TextBufferTests.cpp
