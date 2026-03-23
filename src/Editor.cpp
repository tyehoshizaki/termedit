#include "termedit/Editor.hpp"

namespace {

constexpr char ctrlKey(char ch) { return ch & 0x1f; }
} // namespace

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
  const char key = terminal_.readKey();

  switch (key) {
  case ctrlKey('q'):
    running_ = false;
    break;

  default:
    break;
  }
}

} // namespace termedit
