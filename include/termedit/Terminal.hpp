#pragma once

#include "termedit/key.hpp"

#include <string>
#include <termios.h>
#include <utility>

namespace termedit {

class Terminal {
public:
  Terminal();
  ~Terminal();

  Terminal(const Terminal &) = delete;
  Terminal &operator=(const Terminal &) = delete;

  void enableRawMode();
  void disableRawMode();

  [[nodiscard]] KeyPress readKey() const;
  [[nodiscard]] std::pair<int, int> getWindowSize() const;

  void write(const std::string &text) const;
  void clearScreen() const;

private:
  termios orig_termios{};
  bool rawModeEnabled_ = false;
};

} // namespace termedit
