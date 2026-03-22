#include "wenzi/core/document.h"

namespace wenzi {
namespace core {

Document::Document(std::string text) : text_(text) {}

const std::string& Document::text() const {
  return text_;
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
