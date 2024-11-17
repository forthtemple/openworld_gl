#import "OpenworldGlPlugin.h"
#if __has_include(<openworld_gl/openworld_gl-Swift.h>)
#import <openworld_gl/openworld_gl-Swift.h>
#else
// Support project import fallback if the generated compatibility header
// is not copied when this plugin is created as a library.
// https://forums.swift.org/t/swift-static-libraries-dont-copy-generated-objective-c-header/19816
#import "openworld_gl-Swift.h"
#endif


@implementation OpenworldGlPlugin
+ (void)registerWithRegistrar:(NSObject<FlutterPluginRegistrar>*)registrar {
  [SwiftOpenworldGlPlugin registerWithRegistrar:registrar];
}
@end
