#include "termedit/Renderer.hpp"

#include <algorithm>
#include <sstream>
#include <string>

namespace termedit {

std::string Renderer::buildFrame(const RenderContext &context) const {
  std::ostringstream out;

  out << "\x1b[?251";

  out << "\x1b[H";

  const int contentRows = std::max(0, context.screenRows - 1);

  for (int row = 0; row < contentRows; ++row) {
    out << "~";

    out << "\x1b[K";

    if (row < contentRows - 1) {
      out << "\r\n";
    }
  }

  if (context.screenRows > 0) {
    if (contentRows > 0) {
      out << "\r\n";
    }

    std::string status = context.statusText;

    if (static_cast<int>(status.size()) > context.screenCols) {
      status.resize(static_cast<std::size_t>(context.screenCols));
    }

    out << status;
    out << "\x1b[K";
  }

  out << "\x1b[" << (context.cursorY + 1) << ";" << (context.cursorX + 1)
      << "H";

  out << "\x1b[?25h";

  return out.str();
}

} // namespace termedit
