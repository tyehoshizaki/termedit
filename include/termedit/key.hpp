#pragma once

namespace termedit {

enum class KeyType {
  Unknown,
  Character,
  ArrowLeft,
  ArrowRight,
  ArrowUp,
  ArrowDown,
  Enter,
  Backspace,
  Escape,
  Ctrl
};

struct KeyPress {
  KeyType type = KeyType::Unknown;
  char character = '\0';
};

} // namespace termedit
