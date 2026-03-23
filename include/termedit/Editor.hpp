#pragma once

#include "Renderer.hpp"
#include "Terminal.hpp"
#include "TextBuffer.hpp"

namespace termedit {
class Editor {
public:
  Editor();

  void run();

private:
  void refreshScreen();
  void processKeyPress();

  Terminal terminal_;
  Renderer renderer_;
  TextBuffer buffer_;

  bool running_ = true;

  int cursorX_ = 0;
  int cursorY_ = 0;
};

} // namespace termedit
