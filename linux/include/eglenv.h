#ifndef EGLENV_H
#define EGLENV_H


#include <flutter_linux/flutter_linux.h>

//#include "fl_my_texture_gl.h"

class EglEnv {
public:
    //EGLDisplay egl_display;
   // EGLSurface egl_surface;
    //EGLContext egl_context;
    GdkGLContext* context_;
  // GdkWindow  *window_;//m_hWnd;
    EglEnv() {}
  //  EglEnv(GdkWindow *window);//m_hWnd);
//    EglEnv(GdkGLContext* context_);//GdkWindow *window);//m_hWnd);
    void setupRender(GdkWindow *window);//EglEnv* shareEglEnv);//EGLContext shareContext);//EglEnv* shareEglEnv);
    void makeCurrent();
};

#endif