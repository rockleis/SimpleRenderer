//
// Created by rock on 9/28/21.
//

#ifndef RENDER_UTILS_H
#define RENDER_UTILS_H

#include "AlicePrefix.h"

struct Vertice{
    float mPosition[4];//x,y,z,w
    float mTexcoord[4];
};

unsigned  char* LoadFileContent(const char* path, int & filesize);
GLuint CompileShader(GLenum shader_type,const char * source_code);
GLuint CreateProgram(GLuint vertex_shader,GLuint fragment_shader);
GLuint CreateStandardProgram(const char *vertex_shader_path,const char * fragment_shader_path);
float GetFrameTime();

GLuint CreateBufferObject(GLenum type,void * data,int size,GLenum usage);
void UpdateBufferObject(GLuint object,GLenum type,void * data,int size,int offset=0);


unsigned char * DecodeBMP(unsigned char *bmp_file_content,int&width,int&height);
GLuint CreateTextureFromFile(const char *path);

#endif //RENDER_UTILS_H
