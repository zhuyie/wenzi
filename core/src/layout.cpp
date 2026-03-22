#include "wenzi/core/layout.h"

#include "wenzi/core/document.h"

#include <algorithm>
#include <stdexcept>

namespace wenzi {
namespace core {

namespace {

void flush_line(std::string* current_line, LayoutResult* result) {
  if (!current_line->empty()) {
    result->lines.push_back(LayoutLine{*current_line});
    current_line->clear();
  }
}

}  // namespace

LayoutResult layout_document(const Document& document, const LayoutConfig& config) {
  if (config.max_columns == 0) {
    throw std::invalid_argument("max_columns must be greater than zero");
  }

  LayoutResult result;
  std::string current_line;
  const std::string& text = document.text();

  for (std::size_t i = 0; i < text.size(); ++i) {
    const char ch = text[i];

    if (ch == '\n') {
      result.lines.push_back(LayoutLine{current_line});
      current_line.clear();
      continue;
    }

    current_line.push_back(ch);
    if (current_line.size() >= config.max_columns) {
      flush_line(&current_line, &result);
    }
  }

  flush_line(&current_line, &result);

  if (result.lines.empty()) {
    result.lines.push_back(LayoutLine{""});
  }

  return result;
}

}  // namespace core
}  // namespace wenzi
