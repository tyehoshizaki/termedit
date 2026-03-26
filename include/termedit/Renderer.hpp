#pragma once

#include <string>
#include <vector>

namespace termedit {

struct RenderContext {
  int screenRows = 0;
  int screenCols = 0;
  int cursorX = 0;
  int cursorY = 0;
  std::vector<std::string> visableLines;
  std::string statusText;
};

class Renderer {
public:
  [[nodiscard]] std::string buildFrame(const RenderContext &context) const;
};

} // namespace termedit
