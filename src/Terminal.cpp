#include "termedit/Terminal.hpp"
#include "termedit/key.hpp"

#include <cctype>
#include <iostream>
#include <stdexcept>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <termios.h>
#include <unistd.h>

namespace {
constexpr char kEscape = '\x1b';
constexpr char kEnterCarriageReturn = '\r';
constexpr char kEnterLineFeed = '\n';
constexpr char kBackspace = 127;

constexpr char kCsiIntroducer = '[';
constexpr char kArrowUpCode = 'A';
constexpr char kArrowDownCode = 'B';
constexpr char kArrowRightCode = 'C';
constexpr char kArrowLeftCode = 'D';

constexpr char kFirstCtrlCode = 1;
constexpr char kLastCtrlCode = 26;

constexpr char kReadByteCount = 1;

[[nodiscard]] bool isCtrlCode(char ch) {
  return ch >= kFirstCtrlCode && ch <= kLastCtrlCode;
}

[[nodiscard]] char ctrlCodeToLetter(char ch) {
  return static_cast<char>('a' + (ch - kFirstCtrlCode));
}
} // namespace

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

KeyPress Terminal::readKey() const {
  char ch = '\0';

  while (true) {
    const ssize_t bytesRead = ::read(STDIN_FILENO, &ch, kReadByteCount);

    if (bytesRead == kReadByteCount) {
      break;
    }
  }

  if (ch == kEscape) {
    char seq[2]{};

    const ssize_t firstRead = ::read(STDIN_FILENO, &seq[0], kReadByteCount);
    const ssize_t secondRead = ::read(STDIN_FILENO, &seq[1], kReadByteCount);

    if (firstRead != kReadByteCount || secondRead != kReadByteCount) {
      return {KeyType::Escape, '\0'};
    }

    if (seq[0] == kCsiIntroducer) {
      switch (seq[1]) {
      case kArrowUpCode:
        return {KeyType::ArrowUp, '\0'};
      case kArrowDownCode:
        return {KeyType::ArrowDown, '\0'};
      case kArrowRightCode:
        return {KeyType::ArrowRight, '\0'};
      case kArrowLeftCode:
        return {KeyType::ArrowLeft, '\0'};
      default:
        return {KeyType::Unknown, '\0'};
      }
    }

    return {KeyType::Escape, '\0'};
  }

  if (ch == kEnterCarriageReturn || ch == kEnterLineFeed) {
    return {KeyType::Enter, '\0'};
  }

  if (ch == kBackspace) {
    return {KeyType::Backspace, '\0'};
  }

  if (isCtrlCode(ch)) {
    return {KeyType::Ctrl, ctrlCodeToLetter(ch)};
  }

  if (std::isprint(static_cast<unsigned char>(ch))) {
    return {KeyType::Character, ch};
  }

  return {KeyType::Unknown, '\0'};
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
