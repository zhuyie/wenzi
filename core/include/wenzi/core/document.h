#ifndef WENZI_CORE_DOCUMENT_H
#define WENZI_CORE_DOCUMENT_H

#include <cstddef>
#include <string>

namespace wenzi {
namespace core {

class Document {
public:
  Document();
  explicit Document(std::string text);

  const std::string& text() const;
  std::size_t size_bytes() const;
  bool empty() const;

  void insert(std::size_t byte_offset, const std::string& text);
  void erase(std::size_t byte_offset, std::size_t byte_count);

private:
  std::string text_;
};

Document make_mock_document();

}  // namespace core
}  // namespace wenzi

#endif
