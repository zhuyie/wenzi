#include "wenzi/core/document_io.h"

#include "wenzi/core/document.h"

#include <fstream>
#include <iterator>
#include <stdexcept>

namespace wenzi {
namespace core {

namespace {

bool is_valid_utf8(const std::string& text) {
  std::size_t i = 0;
  while (i < text.size()) {
    const unsigned char lead = static_cast<unsigned char>(text[i]);
    std::size_t continuation_count = 0;

    if (lead <= 0x7F) {
      ++i;
      continue;
    } else if ((lead >> 5) == 0x6) {
      continuation_count = 1;
      if (lead < 0xC2) {
        return false;
      }
    } else if ((lead >> 4) == 0xE) {
      continuation_count = 2;
    } else if ((lead >> 3) == 0x1E) {
      continuation_count = 3;
      if (lead > 0xF4) {
        return false;
      }
    } else {
      return false;
    }

    if (i + continuation_count >= text.size()) {
      return false;
    }

    for (std::size_t j = 1; j <= continuation_count; ++j) {
      const unsigned char continuation =
          static_cast<unsigned char>(text[i + j]);
      if ((continuation >> 6) != 0x2) {
        return false;
      }
    }

    if (continuation_count == 2) {
      const unsigned char first = static_cast<unsigned char>(text[i + 1]);
      if (lead == 0xE0 && first < 0xA0) {
        return false;
      }
      if (lead == 0xED && first >= 0xA0) {
        return false;
      }
    } else if (continuation_count == 3) {
      const unsigned char first = static_cast<unsigned char>(text[i + 1]);
      if (lead == 0xF0 && first < 0x90) {
        return false;
      }
      if (lead == 0xF4 && first >= 0x90) {
        return false;
      }
    }

    i += continuation_count + 1;
  }

  return true;
}

std::string remove_utf8_bom(const std::string& bytes) {
  if (bytes.size() >= 3 &&
      static_cast<unsigned char>(bytes[0]) == 0xEF &&
      static_cast<unsigned char>(bytes[1]) == 0xBB &&
      static_cast<unsigned char>(bytes[2]) == 0xBF) {
    return bytes.substr(3);
  }

  return bytes;
}

}  // namespace

Document load_document_from_file(const std::string& path) {
  std::ifstream stream(path.c_str(), std::ios::binary);
  if (!stream) {
    throw std::runtime_error("failed to open file: " + path);
  }

  const std::string bytes((std::istreambuf_iterator<char>(stream)),
                          std::istreambuf_iterator<char>());
  if (!stream.good() && !stream.eof()) {
    throw std::runtime_error("failed to read file: " + path);
  }

  const std::string text = remove_utf8_bom(bytes);
  if (!is_valid_utf8(text)) {
    throw std::runtime_error("unsupported or invalid text encoding: " + path);
  }

  return Document(text);
}

}  // namespace core
}  // namespace wenzi
