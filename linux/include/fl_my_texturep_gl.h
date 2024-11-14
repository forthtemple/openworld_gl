#ifndef FLUTTER_MY_TEXTUREP_H
#define FLUTTER_MY_TEXTUREP_H
/*
#include <gtk/gtk.h>
#include <glib-object.h>
#include <GL/glew.h>
#include <EGL/egl.h>
#include <EGL/eglext.h>

#include <glib.h>
#include <GL/gl.h>*/
#include "openworldcommon.h"
#include "openworld_gl/openworld_gl_plugin.h"
//#include  "customrender.h"
#include <flutter_linux/flutter_linux.h>
//#include <map>
//#include <string>
//#include <memory>
//#include <sstream>

G_DECLARE_FINAL_TYPE(FlMyTexturePGL,
                     fl_my_texturep_gl,
                     FL,
                     MY_TEXTUREP_GL,
                     FlPixelBufferTexture)

struct _FlMyTexturePGL
{
    FlPixelBufferTexture parent_instance;

    uint8_t *buffer;
    uint32_t width;// = self->width;
    uint32_t height;;// = self->height;
};


FlMyTexturePGL *fl_my_texturep_gl_new(uint32_t width,
                                      uint32_t height);//uint8_t *buffer
                                 //   );
#endif // FLUTTER_MY_TEXTUREP_H
