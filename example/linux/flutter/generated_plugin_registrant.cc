//
//  Generated file. Do not edit.
//

// clang-format off

#include "generated_plugin_registrant.h"

#include <openworld_gl/openworld_gl_plugin.h>

void fl_register_plugins(FlPluginRegistry* registry) {
  g_autoptr(FlPluginRegistrar) openworld_gl_registrar =
      fl_plugin_registry_get_registrar_for_plugin(registry, "OpenworldGlPlugin");
  openworld_gl_plugin_register_with_registrar(openworld_gl_registrar);
}
