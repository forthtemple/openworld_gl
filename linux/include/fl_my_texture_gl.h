#ifndef FLUTTER_MY_TEXTURE_H
#define FLUTTER_MY_TEXTURE_H

#include "openworldcommon.h"
/*#include <gtk/gtk.h>
#include <glib-object.h>
#include <GL/glew.h>
#include <EGL/egl.h>
#include <EGL/eglext.h>

#include <glib.h>
#include <GL/gl.h>*/
#include "openworld_gl/openworld_gl_plugin.h"
#include  "customrender.h"
#include <flutter_linux/flutter_linux.h>
#include <map>
//#include <string>
#include <memory>
//#include <sstream>

G_DECLARE_FINAL_TYPE(FlMyTextureGL,
                     fl_my_texture_gl,
                     FL,
                     MY_TEXTURE_GL,
                     FlTextureGL)

struct _FlMyTextureGL
{
   // FlTextureGL
            FlPixelBufferTexture parent_instance;
    uint32_t target;
    uint32_t name;
    uint32_t width;
    uint32_t height;
};


#define OPENWORLD_GL_PLUGIN(obj)                                     \
  (G_TYPE_CHECK_INSTANCE_CAST((obj), openworld_gl_plugin_get_type(), \
                              OpenworldGlPlugin))

struct _OpenworldGlPlugin
{
  GObject parent_instance;
  GdkGLContext *context = nullptr;
  FlTextureRegistrar *texture_registrar = nullptr;
  FlMyTextureGL *myTexture = nullptr;
  unsigned int texture_name = 0;
  FlTexture *texture = nullptr;
  FlView *fl_view = nullptr;
    GdkWindow *window = nullptr; //glenn
    uint32_t width =0; //glenn
    uint32_t height=0; //glenn
     CustomRender *render = nullptr;
   std::map<int64_t, std::unique_ptr<CustomRender>> *renders_ = nullptr;//unique_ptr<CustomRender>> renders_;
   // FlValue *fl_vectoregls= nullptr;
    // std::map<int64_t, std::string> voot;//unique_ptr<CustomRender>> renders_;
};


FlMyTextureGL *fl_my_texture_gl_new(uint32_t target,
                                    uint32_t name,
                                    uint32_t width,
                                    uint32_t height);
#endif // FLUTTER_MY_TEXTURE_H
