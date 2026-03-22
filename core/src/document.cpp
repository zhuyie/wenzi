#include "wenzi/core/document.h"

#include <stdexcept>

namespace wenzi {
namespace core {

Document::Document() {}

Document::Document(std::string text) : text_(text) {}

const std::string& Document::text() const {
  return text_;
}

std::size_t Document::size_bytes() const {
  return text_.size();
}

bool Document::empty() const {
  return text_.empty();
}

void Document::insert(std::size_t byte_offset, const std::string& text) {
  if (byte_offset > text_.size()) {
    throw std::out_of_range("insert offset is out of range");
  }

  text_.insert(byte_offset, text);
}

void Document::erase(std::size_t byte_offset, std::size_t byte_count) {
  if (byte_offset > text_.size()) {
    throw std::out_of_range("erase offset is out of range");
  }

  text_.erase(byte_offset, byte_count);
}

Document make_mock_document() {
  return Document(
      "wenzi MVP document\n"
      "This text is currently hard-coded so we can exercise the initial "
      "document-to-layout-to-render pipeline.\n"
      "Future versions will replace this with file loading, Unicode-aware "
      "segmentation, shaping, and native rendering.");
}

}  // namespace core
}  // namespace wenzi
