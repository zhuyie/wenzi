#include "wenzi/core/document.h"
#include "wenzi/core/layout.h"
#include "wenzi/ui/application_mac.h"

int main() {
  const wenzi::core::Document document = wenzi::core::make_mock_document();
  const wenzi::core::LayoutConfig config = {48};
  const wenzi::core::LayoutResult layout =
      wenzi::core::layout_document(document, config);

  return wenzi::ui::run_application(layout);
}
