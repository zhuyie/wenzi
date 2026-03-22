#ifndef WENZI_CORE_DOCUMENT_IO_H
#define WENZI_CORE_DOCUMENT_IO_H

#include <string>

namespace wenzi {
namespace core {

class Document;

Document load_document_from_file(const std::string& path);

}  // namespace core
}  // namespace wenzi

#endif
