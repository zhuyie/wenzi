#ifndef WENZI_CORE_LAYOUT_H
#define WENZI_CORE_LAYOUT_H

#include <cstddef>
#include <string>
#include <vector>

namespace wenzi {
namespace core {

class Document;

struct LayoutLine {
  std::string text;
};

struct LayoutResult {
  std::vector<LayoutLine> lines;
};

struct LayoutConfig {
  std::size_t max_columns;
};

LayoutResult layout_document(const Document& document, const LayoutConfig& config);

}  // namespace core
}  // namespace wenzi

#endif
