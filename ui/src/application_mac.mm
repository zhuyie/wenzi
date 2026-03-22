#include "wenzi/ui/application_mac.h"

#import <Cocoa/Cocoa.h>

#include <vector>

@interface WenziContentView : NSView
- (instancetype)initWithFrame:(NSRect)frame
                        lines:(const std::vector<wenzi::core::LayoutLine>&)lines;
@end

@interface WenziAppDelegate : NSObject <NSApplicationDelegate, NSWindowDelegate>
- (instancetype)initWithLayout:(const wenzi::core::LayoutResult&)layout;
@end

@implementation WenziContentView {
  std::vector<wenzi::core::LayoutLine> _lines;
}

- (instancetype)initWithFrame:(NSRect)frame
                        lines:(const std::vector<wenzi::core::LayoutLine>&)lines {
  self = [super initWithFrame:frame];
  if (self) {
    _lines = lines;
  }
  return self;
}

- (BOOL)isFlipped {
  return YES;
}

- (void)drawRect:(NSRect)dirtyRect {
  [super drawRect:dirtyRect];

  [[NSColor colorWithCalibratedWhite:0.97 alpha:1.0] setFill];
  NSRectFill(dirtyRect);

  NSDictionary* attributes = @{
    NSFontAttributeName: [NSFont monospacedSystemFontOfSize:16 weight:NSFontWeightRegular],
    NSForegroundColorAttributeName: [NSColor colorWithCalibratedWhite:0.1 alpha:1.0]
  };

  const CGFloat left_padding = 24.0;
  const CGFloat top_padding = 24.0;
  const CGFloat line_height = 24.0;

  for (std::size_t i = 0; i < _lines.size(); ++i) {
    NSString* line = [NSString stringWithUTF8String:_lines[i].text.c_str()];
    NSPoint point =
        NSMakePoint(left_padding, top_padding + static_cast<CGFloat>(i) * line_height);
    [line drawAtPoint:point withAttributes:attributes];
  }
}

@end

@implementation WenziAppDelegate {
  wenzi::core::LayoutResult _layout;
  NSWindow* _window;
}

- (instancetype)initWithLayout:(const wenzi::core::LayoutResult&)layout {
  self = [super init];
  if (self) {
    _layout = layout;
  }
  return self;
}

- (void)applicationDidFinishLaunching:(NSNotification*)notification {
  (void)notification;

  NSRect frame = NSMakeRect(0.0, 0.0, 860.0, 520.0);
  NSUInteger style_mask = NSWindowStyleMaskTitled |
                          NSWindowStyleMaskClosable |
                          NSWindowStyleMaskMiniaturizable |
                          NSWindowStyleMaskResizable;

  _window = [[NSWindow alloc] initWithContentRect:frame
                                        styleMask:style_mask
                                          backing:NSBackingStoreBuffered
                                            defer:NO];
  [_window setTitle:@"wenzi"];
  [_window center];
  [_window setDelegate:self];

  WenziContentView* content_view =
      [[WenziContentView alloc] initWithFrame:frame lines:_layout.lines];
  [_window setContentView:content_view];
  [_window makeKeyAndOrderFront:nil];

  [NSApp activateIgnoringOtherApps:YES];
}

- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication*)sender {
  (void)sender;
  return YES;
}

@end

static void install_menu() {
  NSMenu* main_menu = [[NSMenu alloc] initWithTitle:@""];
  NSMenuItem* app_menu_item = [[NSMenuItem alloc] initWithTitle:@""
                                                         action:nil
                                                  keyEquivalent:@""];
  [main_menu addItem:app_menu_item];

  NSMenu* app_menu = [[NSMenu alloc] initWithTitle:@"wenzi"];
  NSMenuItem* quit_item = [[NSMenuItem alloc] initWithTitle:@"Quit wenzi"
                                                     action:@selector(terminate:)
                                              keyEquivalent:@"q"];
  [app_menu addItem:quit_item];
  [app_menu_item setSubmenu:app_menu];

  [NSApp setMainMenu:main_menu];
}

namespace wenzi {
namespace ui {

int run_application(const wenzi::core::LayoutResult& layout) {
  @autoreleasepool {
    [NSApplication sharedApplication];
    [NSApp setActivationPolicy:NSApplicationActivationPolicyRegular];

    install_menu();

    WenziAppDelegate* delegate =
        [[WenziAppDelegate alloc] initWithLayout:layout];
    [NSApp setDelegate:delegate];
    [NSApp run];
  }

  return 0;
}

}  // namespace ui
}  // namespace wenzi
