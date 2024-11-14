
#ifndef CUSTOMRENDER_H
#define CUSTOMRENDER_H



#include <flutter_linux/flutter_linux.h>
#include "renderworker.h"
#include "eglenv.h"
//#include <GL/gl.h>
#include <memory>
#include "fl_my_texturep_gl.h"

//#include <flutter_texture_registrar.h>
/*
struct _MyTexture {
    FlPixelBufferTexture parent_instance;

    uint8_t *buffer;  // your pixel buffer.
};*/

class CustomRender {
public:
    uint32_t  width;
    uint32_t  height;
    CustomRender(uint32_t width_, uint32_t height_, FlTextureRegistrar* texture_registrar,   GdkWindow *window);
//    CustomRender(int width_, int height_, FlTextureRegistrar* texture_registrar,     GdkGLContext* context);
    // *context);//GdkWindow *window);//, HWND m_hWnd);
    GdkWindow *window_;//m_hWnd;
    //GdkGLContext* context_;
    RenderWorker renderWorker;
    void initEGL();
    void initGL();

    FlValue *getEgls();
   // g_autoptr(FlValue) texture_id() const { return texture_id_; }
    int64_t texture_id() const { return texture_id_; }
    int updateTexture(GLuint sourceTexture);
  //  EglEnv shareEglEnv;
    EglEnv eglEnv;
    EglEnv dartEglEnv;
    GLuint frameBuffer = 0;
private:
  //  std::unique_ptr<FlutterDesktopPixelBuffer> flutter_pixel_buffer_;

    //g_autoptr(FlTexture) texture_ = nullptr;
   // g_autoptr(FlValue) texture_id_ = nullptr;
    int64_t texture_id_;
   // std::unique_ptr<uint8_t> pixels_;
   // const uint8_t* pixels_ = nullptr;
};

#endif