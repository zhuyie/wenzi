#include "wenzi/core/document.h"
#include "wenzi/core/document_io.h"

#include <cassert>
#include <cstdio>
#include <fstream>
#include <stdexcept>
#include <string>

namespace {

void write_file(const std::string& path, const std::string& bytes) {
  std::ofstream stream(path.c_str(), std::ios::binary);
  assert(stream && "failed to create test file");
  stream.write(bytes.data(), static_cast<std::streamsize>(bytes.size()));
  assert(stream.good() && "failed to write test file");
}

void test_document_editing() {
  wenzi::core::Document document("hello");
  assert(document.size_bytes() == 5);
  assert(!document.empty());

  document.insert(5, " world");
  assert(document.text() == "hello world");

  document.erase(5, 1);
  assert(document.text() == "helloworld");

  bool threw = false;
  try {
    document.insert(64, "x");
  } catch (const std::out_of_range&) {
    threw = true;
  }
  assert(threw);
}

void test_load_utf8_file() {
  const std::string path = "wenzi_test_utf8.txt";
  write_file(path, "plain utf8 text\nsecond line");

  const wenzi::core::Document document =
      wenzi::core::load_document_from_file(path);
  assert(document.text() == "plain utf8 text\nsecond line");

  std::remove(path.c_str());
}

void test_load_utf8_bom_file() {
  const std::string path = "wenzi_test_utf8_bom.txt";
  const std::string bom_text("\xEF\xBB\xBF", 3);
  write_file(path, bom_text + "bom text");

  const wenzi::core::Document document =
      wenzi::core::load_document_from_file(path);
  assert(document.text() == "bom text");

  std::remove(path.c_str());
}

void test_reject_invalid_encoding() {
  const std::string path = "wenzi_test_invalid.txt";
  write_file(path, "\xFF\xFE\x00\x00");

  bool threw = false;
  try {
    (void)wenzi::core::load_document_from_file(path);
  } catch (const std::runtime_error&) {
    threw = true;
  }

  std::remove(path.c_str());
  assert(threw);
}

}  // namespace

int main() {
  test_document_editing();
  test_load_utf8_file();
  test_load_utf8_bom_file();
  test_reject_invalid_encoding();
  return 0;
}
