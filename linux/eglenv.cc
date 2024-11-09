
#include "include/eglenv.h"

//#include <EGL/egl.h>
//#include <EGL/eglext.h>
//#include "include/fl_my_texture_gl.h"
/*EglEnv::EglEnv(GdkWindow *window) {
//EglEnv::EglEnv(GdkGLContext* context) { //GdkWindow *window) {
  //  context_=context;//window_=window;
   window_=window;
}
*/
void EglEnv::setupRender(GdkWindow *window) {//EglEnv* shareEglEnv) {//EGLContext shareContext) {//) {
  //  glfwInit();
   // GError *error = NULL;
    g_autoptr(GError) error = nullptr;
    context_ = gdk_window_create_gl_context(window, &error);
    printf(".... eglenv setuprender \n");//%ld\n",context_);
    if (error!=nullptr)
        printf(".... setup render error\n");

    if (!gdk_gl_context_realize (
            context_,
            &error
    )) {
        printf(".... setuprenderer realize false\n");
    }
    if( error != NULL )
    {
       // mylog("make current realize failure");
       printf(".... setuprenderer realize failed\n");
      //  std::cout << error->message << std::endl;
        g_clear_error (&error);
    } //else
    //    mylog("make current realize fine");

//    window = gtk_widget_get_parent_window(GTK_WIDGET(self->fl_view));

    //GtkWidget *widget = GTK_WIDGET(self->fl_view);



   /* egl_display =
            eglGetDisplay((EGLNativeDisplayType)gdk_x11_display_get_xdisplay(
                    gtk_widget_get_display(widget)));*/
  /*  EGLint majorVersion, minorVersion;
    EGLConfig egl_config;
    EGLint n_config;
    EGLint attributes[] = {
            EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
            EGL_BUFFER_SIZE,    16,
            EGL_DEPTH_SIZE,     16,
            EGL_STENCIL_SIZE,   0,
            EGL_BLUE_SIZE, 8,
            EGL_GREEN_SIZE, 8,
            EGL_RED_SIZE, 8,
            EGL_NONE
    };
    egl_display= eglGetDisplay(EGL_DEFAULT_DISPLAY);
  //  eglPrintError("eglGetDisplay()");

    eglInitialize(egl_display, &majorVersion, &minorVersion);
  //  eglPrintError("eglInitialize()");

    eglChooseConfig(egl_display, attributes, &egl_config, 1, &n_config);
 //   eglPrintError("eglChooseConfig()");

    eglBindAPI(EGL_OPENGL_ES_API);
   // eglPrintError("eglBindAPI()");

    // egl_surface = eglCreateWindowSurface(
    //     egl_display, egl_config, gdk_x11_window_get_xid(viewWindow), NULL);
    //egl_surface = eglCreateWindowSurface(
   //         egl_display, egl_config, _window, NULL);
    //eglPrintError("eglCreateWindowSurface()");

//    shareContext: EGLContext = EGL14.EGL_NO_CONTEXT
    egl_context = eglCreateContext(egl_display, egl_config, shareContext, 0);
*/

//    egl_context = eglCreateContext(egl_display, egl_config, EGL_NO_CONTEXT, 0);
    //egl_context = eglCreateContext(egl_display, egl_config, EGL_NO_CONTEXT, 0);


}

void EglEnv::makeCurrent() {
    printf(".... eglenv make current\n");
    //glfwMakeContextCurrent(window);
   // if (!eglMakeCurrent(egl_display, egl_surface, egl_surface, egl_context)) {
     //   checkEglError("EGL make current failed")
   // }
   // gdk_gl_context_set_use_es(context_,TRUE);//self->resource_context, TRUE);

    gdk_gl_context_make_current(context_);//window_);
}
