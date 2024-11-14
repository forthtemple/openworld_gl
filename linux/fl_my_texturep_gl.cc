#include "include/fl_my_texturep_gl.h"

// https://github.com/lattice0/external_texture_flutter_linux/tree/master/external_texture/linux

#include <iostream>
G_DEFINE_TYPE(FlMyTexturePGL,
              fl_my_texturep_gl,
        fl_pixel_buffer_texture_get_type())

static gboolean my_texturep_copy_pixels (FlPixelBufferTexture* texture,
                           const uint8_t** out_buffer,
                                  uint32_t* width,
                          uint32_t* height,
                                   GError** error) {
FlMyTexturePGL* f = (FlMyTexturePGL*) texture;
*out_buffer = f->buffer;
*width = f->width;
*height = f->height;
return TRUE;
     // This method is called on Render Thread. Be careful with your
     // cross-thread operation.

     // @width and @height are initially stored the canvas size in Flutter.

     // You must prepare your pixel buffer in RGBA format.
     // So you may do some format conversion first if your original pixel
     // buffer is not in RGBA format.
  /*   manage_your_pixel_buffer_here ();

   if (your_operations_are_successfully_finished) {
       // Directly return pointer to your pixel buffer here.
       // Flutter takes content of your pixel buffer after this function
       // is finished. So you must make the buffer live long enough until
       // next tick of Render Thread.
       // If it is hard to manage lifetime of your pixel buffer, you should
       // take look into #FlTextureGL.

       *out_buffer = buffer;
       *width = real_width_of_buffer;
       *height = real_height_of_buffer;
       return TRUE;
     } else {
       // set @error to report failure.
       return FALSE;
     }*/
   }

FlMyTexturePGL *fl_my_texturep_gl_new( uint32_t width,
uint32_t height) //uint8_t *buffer)
{
  auto r = FL_MY_TEXTUREP_GL(g_object_new(fl_my_texturep_gl_get_type(), nullptr));
  //r->buffer = buffer;
  r->width = width;
  r->height = height;
  printf(".... create flmytexturepgl\n");
  r->buffer = static_cast<uint8_t*>(malloc(r->width * r->height * 8));

return r;
}

static void fl_my_texturep_gl_class_init(
    FlMyTexturePGLClass *klass)
{
   FL_PIXEL_BUFFER_TEXTURE_CLASS(klass)->copy_pixels =
             my_texturep_copy_pixels;
}

static void fl_my_texturep_gl_init(FlMyTexturePGL *self)
{
}