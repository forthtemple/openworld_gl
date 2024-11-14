

#ifndef RENDERWORKER_H
#define RENDERWORKER_H

#include "openworldcommon.h"
#include "OpenGLProgram.h"
#include <flutter_linux/flutter_linux.h>

//#include <GL/glew.h>
// #include <GL/glut.h>
//#include "openworld_gl/openworld_gl_plugin.h"
//#include "customrender.h"
//#include <GL/gl.h>
//#include <EGL/egl.h>
//#include "../../src/common.h"
//#include "fl_my_texture_gl.h"

class RenderWorker {
public:
   // RenderWorker();
  void setup();
   // int64_t vertexBuffer = 0;
    GLuint vertexBuffer = 0;
    GLuint program = 0;
    GLuint getProgram();
    OpenGLProgram openGLProgram;
    int renderTexture(GLuint sourceTexture);//, bool isFBO);
    int drawTexture(GLuint texture, GLuint vertexBuffer_);
private:
  void setupVBO();
};

#endif