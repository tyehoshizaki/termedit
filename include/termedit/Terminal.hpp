#pragma once

#include <string>
#include <sys/ioctl.h>
#include <unistd.h>
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

  [[nodiscard]] char readKey() const;
  [[nodiscard]] std::pair<int, int> getWindowsSize() const;

  void write(const std::string &text) const;
  void clearScreen() const;

private:
  bool rawModeEnabled_ = false;
};

} // namespace termedit
