
#include "include/renderworker.h"
/*
#include <GLES3/gl3.h>
#include <GLES3/gl3ext.h>
#include <EGL/egl.h>
#include <EGL/eglext.h>
*/
/*RenderWorker::RenderWorker() {
    printf(".... renderworker create \n");
    program=0;
}*/

void RenderWorker::setup() {
    openGLProgram = OpenGLProgram();
    //program=0;
    printf(".... %d renderworker setup\n", program);
    setupVBO();
 //   GLuint a;
    //setupVBO4FBO();
}

int RenderWorker::renderTexture(GLuint sourceTexture) {//}, bool isFBO) {

  //  printf(".... render texture\n");
    //GLuint _vertexBuffer;

    //if(isFBO) {
    //    _vertexBuffer = vertexBuffer4FBO;
    //} else {
    //    _vertexBuffer = vertexBuffer;
    //}

    return drawTexture(sourceTexture, vertexBuffer);
}


int RenderWorker::drawTexture(GLuint texture, GLuint vertexBuffer_) {

    // checkGlError(op: "drawTexture 01");
  //  printf(".... %d draw texturei %ld\n",program, texture);
    printf(".... draw textureo \n");


    GLuint _program = getProgram();
   // printf(".... %d draw textureii \n",program);
    //glLinkProgram(_program);
    glUseProgram(_program);


    GLuint _positionSlot =GLuint(glGetAttribLocation(_program, "Position"));
    GLuint _textureSlot = GLuint(glGetAttribLocation(_program, "TextureCoords"));
     printf(".... ps %d tex %d \n",_positionSlot,_textureSlot);

    GLuint _texture0Uniform = GLuint(glGetUniformLocation(_program, "Texture0"));


    // 将纹理 ID 传给着色器程序
    // 是否是
    glActiveTexture(GLenum(GL_TEXTURE8));
    glBindTexture(GLenum(GL_TEXTURE_2D), texture);
    glUniform1i(GLint(_texture0Uniform), 8);
    // 将 textureSlot 赋值为 0，而 0 与 GL_TEXTURE0 对应，这里如果写 1，上面也要改成 GL_TEXTURE1


    glBindBuffer(GLenum(GL_ARRAY_BUFFER), vertexBuffer_);


    GLuint vao = GLuint(0);
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glVertexAttribPointer(_positionSlot, 3, GLenum(GL_FLOAT), GLboolean(GL_FALSE), 5 * sizeof(float), (GLvoid*)0);

    // 设置顶点数据
    glEnableVertexAttribArray(_positionSlot);


    // 设置纹理数据
    glVertexAttribPointer(_textureSlot, 2, GLenum(GL_FLOAT), GLboolean(GL_FALSE), 5 * sizeof(float), (const GLvoid*)(3*sizeof(float)));

    glEnableVertexAttribArray(_textureSlot);

    // // 开始绘制
    glDrawArrays(GLenum(GL_TRIANGLE_STRIP), 0, 4);


    glDeleteVertexArrays(1, &vao);

  //  glFinish();
    return 1;


    // checkGlError(op: "drawTexture 11");
}

GLuint RenderWorker::getProgram() {

  //  printf(".... get program %d\n",program);
    if(program == 0) {//} 0) {
        printf(".... get program\n");
        program = openGLProgram.getProgram();//glCreateProgram(); //openGLProgram.getProgram();
    }

    return program;
}


void RenderWorker::setupVBO() {
    // 创建顶点缓存
  /*  int width=1000;
    int height=700;
    float wd = (float)width / 16;
    float ht = (float)height / 16;*/

    // The background quad is made of four vertices:
    //
    //   3--2
    //   |  |
    //   0--1
    //
 /*  float vertices[] = {
             -1, -1,  0,  0 ,	// Bottom left
              1, -1, wd,  0 ,	// Bottom right
              1,  1, wd, ht ,	// Top right
             -1,  1,  0, ht ,	// Top left
    };*/

    float vertices[] = {
            -1.0f,-1.0f,0.0f, 0.0f, 1.0f, // 左上角
            1.0f,-1.0f,0.0f, 1.0f,1.0f, // 左下角
            -1.0f,1.0f,0.0f, 0.0f,0.0f, // 右上角
            1.0f,1.0f,0.0f, 1.0f,0.0f // 右下角  lower right corner
    };
  /*  float vertices[] = {
            -1.0,-1.0,0.0, 0.0, 0.0,
            1.0,-1.0,0.0, 1.0,0.0,
            -1.0,1.0,0.0, 0.0,1.0,
            1.0,1.0,0.0, 1.0,1.0
    };*/
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GLenum(GL_ARRAY_BUFFER), vertexBuffer);

    glBufferData(GLenum(GL_ARRAY_BUFFER), sizeof(vertices), vertices, GLenum(GL_STATIC_DRAW));
}