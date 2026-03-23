#include "termedit/Terminal.hpp"

#include <iostream>

namespace termedit {

Terminal::Terminal() = default;

Terminal::~Terminal() {
  if (rawModeEnabled_) {
    disableRawMode();
  }
}

void Terminal::enableRawMode() {
  // TODO: replace this stub with a real termios-based raw mode stepup
  rawModeEnabled_ = true;
}

void Terminal::disableRawMode() {
  // TODO: restore the original terminal state here later
  rawModeEnabled_ = false;
}

char Terminal::readKey() const {
  char ch = '\0';
  std::cin.get(ch);
  return ch;
}

std::pair<int, int> Terminal::getWindowsSize() const {
  // TODO: replace this placeholder wiht a real terminal-size query
  return {24, 80};
}

void Terminal::write(const std::string &text) const {
  std::cout << text;
  std::cout.flush();
}

void Terminal::clearScreen() const {
  write("\x1b[2J");
  write("\x1b[H");
}

} // namespace termedit
