
#include "include/customrender.h"

//#include "include/openworld_gl/openworld_gl_plugin.h"
#include "include/fl_my_texture_gl.h"
/*#include <GL/gl.h>
#include <GLES3/gl3.h>
#include <GLES3/gl3ext.h>
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <fl_texture_registrar.h>*/
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

/*
static constexpr uint32_t kBufferWidth = 4u;
static constexpr uint32_t kBufferHeight = 4u;
static constexpr uint32_t kRealBufferWidth = 2u;
static constexpr uint32_t kRealBufferHeight = 2u;

G_DECLARE_FINAL_TYPE(FlTestPixelBufferTexture,
        fl_test_pixel_buffer_texture,
        FL,
        TEST_PIXEL_BUFFER_TEXTURE,
        FlPixelBufferTexture)

/// A simple texture with fixed contents.
struct _FlTestPixelBufferTexture {
    FlPixelBufferTexture parent_instance;
};

G_DEFINE_TYPE(FlTestPixelBufferTexture,
        fl_test_pixel_buffer_texture,
        fl_pixel_buffer_texture_get_type())

static gboolean fl_test_pixel_buffer_texture_copy_pixels(
            FlPixelBufferTexture* texture,
    const uint8_t** out_buffer,
            uint32_t* width,
    uint32_t* height,
            GError** error) {
    if (!FL_IS_TEST_PIXEL_BUFFER_TEXTURE(texture)) {
        printf("err");
    }

    // RGBA
    static const uint8_t buffer[] = {0x0a, 0x1a, 0x2a, 0x3a, 0x4a, 0x5a,
                                     0x6a, 0x7a, 0x8a, 0x9a, 0xaa, 0xba,
                                     0xca, 0xda, 0xea, 0xfa};
    if (*width!=kBufferWidth) {
        printf("err");
    }
    if (*height!=kBufferHeight) {
        printf("err");
    }
    *out_buffer = buffer;
    *width = kRealBufferWidth;
    *height = kRealBufferHeight;

    return TRUE;
}

static void fl_test_pixel_buffer_texture_class_init(
        FlTestPixelBufferTextureClass* klass) {
    FL_PIXEL_BUFFER_TEXTURE_CLASS(klass)->copy_pixels =
            fl_test_pixel_buffer_texture_copy_pixels;
}

static void fl_test_pixel_buffer_texture_init(FlTestPixelBufferTexture* self) {

}

static FlTestPixelBufferTexture* fl_test_pixel_buffer_texture_new() {
    return FL_TEST_PIXEL_BUFFER_TEXTURE(
            g_object_new(fl_test_pixel_buffer_texture_get_type(), nullptr));
}


*/



CustomRender::CustomRender(uint32_t width_,uint32_t height_,  FlTextureRegistrar* texture_registrar,   GdkWindow *window)
//GdkGLContext* context)
 //context)//GdkWindow *window)
 //  :texture_registrar_(texture_registrar) //, HWND m_hWnd)
//        : texture_registrar_(texture_registrar) {
{

    // Test that getting the texture ID works.
//TEST(FlPixelBufferTextureTest, TextureID) {
  /*  g_autoptr(FlTexture) texturei = FL_TEXTURE(fl_test_pixel_buffer_texture_new());
   // fl_texture_set_id(texture, 42);
    if (fl_texture_get_id(texturei)!= static_cast<int64_t>(42)) {
        printf("err");
    }
//}

// Test that populating an OpenGL texture works.
  // TEST(FlPixelBufferTextureTest, PopulateTexture) {
        g_autoptr(FlPixelBufferTexture) texture =
                                                FL_PIXEL_BUFFER_TEXTURE(fl_test_pixel_buffer_texture_new());
      //  FlutterOpenGLTexture
      //  int opengl_texture = {0};
        FlMyTextureGL *opengl_texture = fl_my_texture_gl_new(GL_TEXTURE_2D, texture_name, width, height);
        g_autoptr(GError) error = nullptr;
        //     fl_pixel_buffer_texture_populate (FlPixelBufferTexture *texture, uint32_t width, uint32_t height, FlutterOpenGLTexture *opengl_texture, GError **error)
        if (!fl_pixel_buffer_texture_populate(
                texture, kBufferWidth, kBufferHeight, opengl_texture, &error)) {
            printf("err");
        }
        if (error!=nullptr)
            printf("err");
        if(opengl_texture->width!= kRealBufferWidth)
            printf("err");
        if (opengl_texture->height!= kRealBufferHeight)
            printf("err");
  //  }
   */



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
//    texturep_ = FL_PIXEL_BUFFER_TEXTURE(myTexturep);//yTexture);//myTexture);
  //  FlPixelBufferTextureClass* priv =
   //         reinterpret_cast<FlPixelBufferTextureClass*>(
//            reinterpret_cast<FlPixelBufferTexturePrivate*>(
                  //  fl_pixel_buffer_texture_get_instance(texture_));
       //             fl_pixel_buffer_texture_get_instance_private(texture_));
  //  g_autoptr(GError) error = nullptr;
   // pixels_ = nullptr;
   // checkout    https://chromium.googlesource.com/external/github.com/flutter/flutter/+/master/examples/texture/linux/
    /*if (!FL_PIXEL_BUFFER_TEXTURE_GET_CLASS(texture_)->copy_pixels(
            texturep_, &pixels_, &width, &height, &error)) {
       // return FALSE;
       printf("errrrr\n");
    }*/
    fl_texture_registrar_register_texture(texture_registrar_, texture_);
    //gdk_gl_context_clear_current();
   // fl_texture_registrar_mark_texture_frame_available(texture_registrar_,texture_);

    //window=window_;


    texture_id_ =  fl_texture_get_id(texture_);
   // printf(".... customerender created textureid %ld %ld\n",texture_id_, texture_);
    //FlutterDesktopPixelBuffer *dog;
    //FlPixelBufferTexture* dog;
   // texture_id_ =
    //        fl_value_new_int(fl_texture_get_id(FL_TEXTURE(texture_)));
   //int size = width * height * 4;
    //std::unique_ptr<uint8_t> pixels;
  //  pixels_.reset(new uint8_t[size]);
  /*  std::unique_ptr<FlutterDesktopPixelBuffer> flutter_pixel_buffer_ = std::make_unique<FlutterDesktopPixelBuffer>();
    flutter_pixel_buffer_->buffer = pixels_.get();
    flutter_pixel_buffer_->width = width;
    flutter_pixel_buffer_->height = height;*/
    //   pixels_.reset(new uint8_t[size]);
    //flutter_pixel_buffer_ = std::make_unique<FlutterDesktopPixelBuffer>();
    initEGL();
   // fl_texture_registrar_register_texture(texture_registrar_, texture_);
}

FlValue *CustomRender::getEgls() {
   /* int size;
    glGetIntegerv(GL_MAX_TEXTURE_SIZE, &size);

    int majorver = 0, minorver = 0;
    glGetIntegerv(GL_MAJOR_VERSION, &majorver);
    glGetIntegerv(GL_MINOR_VERSION, &minorver);*/

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
   /* if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return;
    }*/
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
    printf(".... custome render updatetexture %d\n",width);
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

