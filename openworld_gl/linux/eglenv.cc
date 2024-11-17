
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

}

void EglEnv::makeCurrent() {
  //  printf(".... eglenv make current\n");

    gdk_gl_context_make_current(context_);//window_);
}
