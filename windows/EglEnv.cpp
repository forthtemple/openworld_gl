#include "EglEnv.h"


EglEnv::EglEnv(HWND m_hWnd) {
   
}

void EglEnv::setupRender(EglEnv* shareEglEnv) {
    printf("eglenv setuprender\n");

    glfwInit();
    printf("eglenv setuprender\n");
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    printf("eglenv setuprender2\n");
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

    GLFWwindow* shareWindow = NULL;

    if(shareEglEnv != NULL) {
        shareWindow = shareEglEnv->window;
    }

    printf("eglenv setuprender3\n");
    window = glfwCreateWindow(1, 1, "", NULL, shareWindow);
    printf("eglenv setuprender4\n");
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return;
    }
  
}

void EglEnv::makeCurrent() {
    glfwMakeContextCurrent(window);
}