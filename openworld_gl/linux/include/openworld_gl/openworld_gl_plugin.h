#ifndef OPENWORLD_PLUGIN_OPENWORLD_GL_PLUGIN_H_
#define OPENWORLD_PLUGIN_OPENWORLD_GL_PLUGIN_H_

#include <flutter_linux/flutter_linux.h>
//#include "../customrender.h"


G_BEGIN_DECLS

#ifdef FLUTTER_PLUGIN_IMPL
#define FLUTTER_PLUGIN_EXPORT __attribute__((visibility("default")))
#else
#define FLUTTER_PLUGIN_EXPORT
#endif

typedef struct _OpenworldGlPlugin OpenworldGlPlugin;
typedef struct {
  GObjectClass parent_class;
} OpenworldGlPluginClass;

FLUTTER_PLUGIN_EXPORT GType openworld_gl_plugin_get_type();

FLUTTER_PLUGIN_EXPORT void openworld_gl_plugin_register_with_registrar(
    FlPluginRegistrar* registrar);

FLUTTER_PLUGIN_EXPORT int makeCurrent(GdkGLContext* window);

G_END_DECLS



#endif  // OPENWORLD_PLUGIN_OPENWORLD_GL_PLUGIN_H_
