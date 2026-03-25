#pragma once

#include "Renderer.hpp"
#include "Terminal.hpp"
#include "TextBuffer.hpp"

namespace termedit {
class Editor {
public:
  Editor();

  void run();
  void quit();

private:
  void refreshScreen();
  void processKeyPress();

  // moving cursor
  void moveCursorUp();
  void moveCursorDown(int windowSizeY);
  void moveCursorRight(int windowSizeX, int windowSizeY);
  void moveCursorLeft(int windowSizeX);

  Terminal terminal_;
  Renderer renderer_;
  TextBuffer buffer_;

  bool running_ = true;

  int cursorX_ = 0;
  int cursorY_ = 0;
};

} // namespace termedit
