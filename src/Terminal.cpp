#include "termedit/Terminal.hpp"

#include <iostream>
#include <stdexcept>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

namespace termedit {

Terminal::Terminal() = default;

Terminal::~Terminal() {
  if (rawModeEnabled_) {
    disableRawMode();
  }
}

void Terminal::enableRawMode() {
  if (rawModeEnabled_) {
    return;
  }

  if (tcgetattr(STDIN_FILENO, &orig_termios) == -1) {
    throw std::runtime_error("tcgetattr failed");
  }

  termios raw = orig_termios;
  // Disable local flags, input flags, and output post-processing
  raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
  raw.c_iflag &= ~(ICRNL | IXON | BRKINT | INPCK | ISTRIP);
  raw.c_oflag &= ~(OPOST);
  raw.c_cflag |= (CS8);

  // Set read timeout
  raw.c_cc[VMIN] = 0;
  raw.c_cc[VTIME] = 1;

  if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1) {
    throw std::runtime_error("tcsetattr failed");
  }

  rawModeEnabled_ = true;
}

void Terminal::disableRawMode() {
  if (!rawModeEnabled_) {
    return;
  }
  if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios) == -1) {
    throw std::runtime_error("tcsetattr restore failed");
  }

  rawModeEnabled_ = false;
}

char Terminal::readKey() const {
  char ch = '\0';
  while (true) {
    const ssize_t bytesRead = ::read(STDIN_FILENO, &ch, 1);

    if (bytesRead == 1) {
      return ch;
    }
  }
}

std::pair<int, int> Terminal::getWindowSize() const {
  winsize w{};

  if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == -1) {
    throw std::runtime_error("ioctl TIOCGWINSZ failed");
  }

  return {w.ws_row, w.ws_col};
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
