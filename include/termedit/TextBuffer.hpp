#pragma once

#include <cstddef>
#include <string>
#include <vector>

namespace termedit {
class TextBuffer {

public:
  TextBuffer();

  [[nodiscard]] std::size_t lineCount() const;
  [[nodiscard]] const std::string &getLine(std::size_t row) const;

  void insertChar(std::size_t row, std::size_t col, char ch);
  void eraseChar(std::size_t row, std::size_t col);
  void insertNewline(std::size_t row, std::size_t col);
  void deleteLine(std::size_t row);

private:
  std::vector<std::string> lines_;
};
} // namespace termedit
