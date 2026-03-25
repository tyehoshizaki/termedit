#include "termedit/Editor.hpp"
#include "termedit/key.hpp"
#include <sys/types.h>

namespace termedit {

Editor::Editor() = default;

void Editor::run() {
  terminal_.enableRawMode();

  while (running_) {
    refreshScreen();
    processKeyPress();
  }

  terminal_.clearScreen();
}

void Editor::quit() {
  if (running_) {
    running_ = false;
  }
}

void Editor::refreshScreen() {
  const auto [rows, cols] = terminal_.getWindowSize();

  RenderContext context;
  context.screenRows = rows;
  context.screenCols = cols;
  context.cursorX = cursorX_;
  context.cursorY = cursorY_;
  context.statusText = "TermEdit - Ctrl-Q to quit";

  terminal_.write(renderer_.buildFrame(context));
}

void Editor::processKeyPress() {
  const KeyPress key = terminal_.readKey();
  const auto [windowSizeY, windowSizeX] = terminal_.getWindowSize();

  switch (key.type) {
  case KeyType::Ctrl:
    if (key.character == 'q') {
      quit();
    }
    break;

  case KeyType::ArrowLeft:
    moveCursorLeft(windowSizeX);
    break;
  case KeyType::ArrowRight:
    moveCursorRight(windowSizeX, windowSizeY);
    break;
  case KeyType::ArrowUp:
    moveCursorUp();
    break;
  case KeyType::ArrowDown:
    moveCursorDown(windowSizeY);
    break;

  default:
    break;
  }
}

void Editor::moveCursorUp() {
  if (cursorY_ > 0) {
    --cursorY_;
  }
}
void Editor::moveCursorDown(int windowSizeY) {
  const int windowTextSizeY = windowSizeY - 1;
  if (cursorY_ < windowTextSizeY - 1) {
    ++cursorY_;
  }
}
void Editor::moveCursorRight(int windowSizeX, int windowSizeY) {
  const int windowTextSizeY = windowSizeY - 1;
  if (cursorX_ < windowSizeX - 1) {
    ++cursorX_;
  } else if (cursorX_ == windowSizeX - 1) {
    if (cursorY_ == windowTextSizeY - 1) {
      return;
    } else {
      cursorX_ = 0;
      moveCursorDown(windowSizeY);
    }
  }
}
void Editor::moveCursorLeft(int windowSizeX) {
  if (cursorX_ > 0) {
    --cursorX_;
  } else if (cursorX_ == 0) {
    if (cursorY_ == 0) {
      return;
    } else {
      cursorX_ = windowSizeX;
      moveCursorUp();
    }
  }
}

} // namespace termedit
