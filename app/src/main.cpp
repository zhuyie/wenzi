#include "wenzi/core/document.h"
#include "wenzi/core/document_io.h"
#include "wenzi/core/layout.h"
#include "wenzi/ui/application_mac.h"

#include <exception>
#include <iostream>

int main(int argc, char** argv) {
  try {
    const wenzi::core::Document document =
        argc > 1 ? wenzi::core::load_document_from_file(argv[1])
                 : wenzi::core::make_mock_document();
    const wenzi::core::LayoutConfig config = {48};
    const wenzi::core::LayoutResult layout =
        wenzi::core::layout_document(document, config);

    return wenzi::ui::run_application(layout);
  } catch (const std::exception& error) {
    std::cerr << "wenzi: " << error.what() << std::endl;
    return 1;
  }
}
