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

  // TODO: add a dispatcher for moving cursors, moveCursor()

  // moving cursor
  void moveCursorUp();
  void moveCursorDown(int windowSizeY);
  void moveCursorRight(int windowSizeX, int windowSizeY);
  void moveCursorLeft(int windowSizeX);

  void insertCharacter(char ch);
  void handleCtrlKey(char ch);
  void insertNewLine();
  void backspace();
  Terminal terminal_;
  Renderer renderer_;
  TextBuffer buffer_;

  void quit();
  bool running_ = true;

  int cursorX_ = 0;
  int cursorY_ = 0;
};

} // namespace termedit
