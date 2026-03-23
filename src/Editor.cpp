#include "termedit/Editor.hpp"

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
  const auto [rows, cols] = terminal_.getWindowsSize();

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

  // Ctrl-Q
  if (key == 17) {
    running_ = false;
  }
}

} // namespace termedit
