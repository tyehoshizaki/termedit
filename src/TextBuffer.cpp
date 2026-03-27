#include "termedit/TextBuffer.hpp"

#include <stdexcept>

namespace termedit {
TextBuffer::TextBuffer() : lines_{""} {}

std::size_t TextBuffer::lineCount() const { return lines_.size(); }

const std::string &TextBuffer::getLine(std::size_t row) const {
  if (row >= lines_.size()) {
    throw std::out_of_range("TextBuffer::getLine row out of range");
  }

  return lines_[row];
}

void TextBuffer::insertChar(std::size_t row, std::size_t col, char ch) {
  if (row >= lines_.size()) {
    throw std::out_of_range("TextBuffer::insertChar row out of range");
  }

  std::string &line = lines_[row];

  if (col > line.size()) {
    throw std::out_of_range("TextBuffer::insertChar col out of range");
  }

  line.insert(line.begin() + static_cast<std::string::difference_type>(col),
              ch);
}

void TextBuffer::eraseChar(std::size_t row, std::size_t col) {
  if (row >= lines_.size()) {
    throw std::out_of_range("TextBuffer::eraseChar row out of range");
  }

  std::string &line = lines_[row];

  if (col >= line.size()) {
    throw std::out_of_range("TextBuffer::eraseChar col out of range");
  }

  line.erase(line.begin() + static_cast<std::string::difference_type>(col));
}

void TextBuffer::insertNewline(std::size_t row, std::size_t col) {
  if (row >= lines_.size()) {
    throw std::out_of_range("TextBuffer::insertNewline row out of range");
  }

  std::string &line = lines_[row];

  if (col > line.size()) {
    throw std::out_of_range("TextBuffer::insertNewline col out of range");
  }

  std::string rightside = line.substr(col);
  line.erase(col);

  lines_.insert(
      lines_.begin() +
          static_cast<std::vector<std::string>::difference_type>(row + 1),
      rightside);
}

void TextBuffer::deleteLine(std::size_t row) {
  if (row >= lines_.size()) {
    throw std::out_of_range("TextBuffer::deleteLine row out of range");
  }

  if (row == 0) {
    return;
  }

  std::string line = lines_[row];

  lines_[row - 1].append(line);
  lines_.erase(lines_.begin() + row);
}

} // namespace termedit
