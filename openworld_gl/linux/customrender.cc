
#include "include/customrender.h"

//#include "include/openworld_gl/openworld_gl_plugin.h"
#include "include/fl_my_texture_gl.h"

//#include "flutter/shell/platform/linux/public/flutter_linux/fl_texture_registrar.h"
#include <flutter_linux/fl_pixel_buffer_texture.h>
#include <flutter_linux/fl_texture_registrar.h>
//#include <flutter_linux/texture_registrar_impl.h>
//                        fl_pixel_buffer_texture.h"
//#include <flutter_linux/fl_pixel_buffer_texture_private.h>

static  FlTextureRegistrar *texture_registrar_ ;
static FlTexture *texture_ ;
//static FlPixelBufferTexture *texturep_;
//static unsigned int texture_name=0;
//static FlMyTextureGL *myTexture;
static FlMyTexturePGL *myTexturep;


CustomRender::CustomRender(uint32_t width_,uint32_t height_,  FlTextureRegistrar* texture_registrar,   GdkWindow *window)

{



    texture_registrar_= texture_registrar;

    // glenn look https://codebrowser.dev/flutter_engine/flutter_engine/flutter/shell/platform/linux/fl_pixel_buffer_texture_test.cc.html
 //   context_=context;
    window_=window;
    width = width_;
    height = height_;
   // printf(".... customrender create %ld %d\n",texture_registrar_,width);
    printf(".... customrender create  %d\n",width);
  //  glGenTextures(1, &texture_name);
  //  glBindTexture(GL_TEXTURE_2D, texture_name);
   // myTexture = fl_my_texture_gl_new(GL_TEXTURE_2D, texture_name, width, height);
  //  uint8_t* buffer;
    //FlMyTexturePGL *
    myTexturep= fl_my_texturep_gl_new(width, height);//pixels_);
    texture_ = FL_TEXTURE(myTexturep);

    fl_texture_registrar_register_texture(texture_registrar_, texture_);
    //gdk_gl_context_clear_current();
   // fl_texture_registrar_mark_texture_frame_available(texture_registrar_,texture_);

    //window=window_;


    texture_id_ =  fl_texture_get_id(texture_);

    initEGL();
   // fl_texture_registrar_register_texture(texture_registrar_, texture_);
}

FlValue *CustomRender::getEgls() {


    g_autoptr(FlValue) fl_vector = fl_value_new_list();
    fl_value_append(fl_vector, fl_value_new_int(0));
    fl_value_append(fl_vector, fl_value_new_int(0));
    //eglEnv.window
    fl_value_append(fl_vector, fl_value_new_int(reinterpret_cast<int64_t>(eglEnv.context_)));//context_)));
    fl_value_append(fl_vector, fl_value_new_int(0));
    fl_value_append(fl_vector, fl_value_new_int(0));
    //dartEglEnv.window
    fl_value_append(fl_vector, fl_value_new_int(reinterpret_cast<int64_t>(dartEglEnv.context_)));//context_)));
//    fl_value_append(fl_vector, fl_value_new_int(reinterpret_cast<int64_t>(context_)));
    return fl_value_ref(fl_vector);
}


void CustomRender::initEGL() {
    printf(".... initEGL\n");
 //   shareEglEnv = EglEnv();//context_);//window_);//m_hWnd );
    eglEnv = EglEnv();// context_);//window_);//m_hWnd );
    dartEglEnv = EglEnv();// window_);//m_hWnd );

   // shareEglEnv.setupRender(NULL);

    printf(".... initegl eglenv setup\n");
    eglEnv.setupRender(window_);//&shareEglEnv);
    printf(".... initegl darteglenv setup\n");
    dartEglEnv.setupRender(window_);//&shareEglEnv);
    eglEnv.makeCurrent();

    // glad: load all OpenGL function pointers

    initGL();
    renderWorker = RenderWorker();
    renderWorker.setup();
}

void CustomRender::initGL() {
    printf(".... initGL %d\n", width);
    glViewport(0, 0, GLsizei(width), GLsizei(height));


    glGenFramebuffers(1, &frameBuffer);
    glBindFramebuffer(GLenum(GL_FRAMEBUFFER), frameBuffer);

    GLuint texture = 0;
    glGenTextures(1, &texture);

    glBindTexture(GLenum(GL_TEXTURE_2D), texture);
    glTexParameteri(GLenum(GL_TEXTURE_2D), GLenum(GL_TEXTURE_MAG_FILTER), GL_LINEAR);
    glTexParameteri(GLenum(GL_TEXTURE_2D), GLenum(GL_TEXTURE_MIN_FILTER), GL_LINEAR);

    glTexImage2D(GLenum(GL_TEXTURE_2D), 0, GLenum(GL_RGBA), GLsizei(width), GLsizei(height), 0, GLenum(GL_RGBA),
                 GLenum(GL_UNSIGNED_BYTE), NULL);


    GLuint colorRenderBuffer = 0;
    glGenRenderbuffers(1, &colorRenderBuffer);
    glBindRenderbuffer(GLenum(GL_RENDERBUFFER), colorRenderBuffer);
    glRenderbufferStorage(GLenum(GL_RENDERBUFFER), GLenum(GL_DEPTH24_STENCIL8), GLsizei(width), GLsizei(height));

    glFramebufferTexture2D(GLenum(GL_FRAMEBUFFER), GLenum(GL_COLOR_ATTACHMENT0), GLenum(GL_TEXTURE_2D), texture, 0);

    glFramebufferRenderbuffer(GLenum(GL_FRAMEBUFFER), GLenum(GL_DEPTH_ATTACHMENT), GLenum(GL_RENDERBUFFER), colorRenderBuffer);
    glFramebufferRenderbuffer(GLenum(GL_FRAMEBUFFER), GLenum(GL_STENCIL_ATTACHMENT), GLenum(GL_RENDERBUFFER), colorRenderBuffer);
    printf(".... initGL exit %d\n", width);

}

int CustomRender::updateTexture(GLuint sourceTexture) {
 //  fl_texture_registrar_register_texture(texture_registrar_, texture_);
  //  printf(".... custome render updatetexture %ld %ld %ld\n",frameBuffer, sourceTexture, width);
  //  printf(".... custome render updatetexture %d\n",width);
    eglEnv.makeCurrent();
    glBindFramebuffer(GLenum(GL_FRAMEBUFFER), frameBuffer);

    glClearColor( GLclampf(0.0), GLclampf(0.0), GLclampf(0.0), GLclampf(0.0) );
    glClear(GLbitfield(GL_COLOR_BUFFER_BIT));


    int data = renderWorker.renderTexture(sourceTexture) ;///, false);


    // use PBO better???
    uint8_t *buffer = myTexturep->buffer;
    glReadPixels(0, 0, GLsizei(width), GLsizei(height), GL_RGBA, GL_UNSIGNED_BYTE, buffer);


    // flutter_pixel_buffer_->buffer = buffer;
    // flutter_pixel_buffer_->width = width;
    // flutter_pixel_buffer_->height = height;

   // texture_registrar_->MarkTextureFrameAvailable(texture_id_);
  //  printf(".... updatetexture vals %ld %ld\n",texture_registrar_,texture_);
    fl_texture_registrar_mark_texture_frame_available(texture_registrar_, texture_);

    return data;

}

