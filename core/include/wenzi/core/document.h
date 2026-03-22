#ifndef WENZI_CORE_DOCUMENT_H
#define WENZI_CORE_DOCUMENT_H

#include <string>

namespace wenzi {
namespace core {

class Document {
public:
  explicit Document(std::string text);

  const std::string& text() const;

private:
  std::string text_;
};

Document make_mock_document();

}  // namespace core
}  // namespace wenzi

#endif
