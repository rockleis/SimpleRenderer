//
// Created by rock on 9/28/21.
//

#ifndef RENDER_UTILS_H
#define RENDER_UTILS_H

#include "AlicePrefix.h"

struct Vertice{
    float mPosition[4];//x,y,z,w
};

unsigned  char* LoadFileContent(const char* path, int & filesize);
GLuint CompileShader(GLenum shader_type,const char * source_code);
GLuint CreateProgram(GLuint vertex_shader,GLuint fragment_shader);
GLuint CreateStandardProgram(const char *vertex_shader_path,const char * fragment_shader_path);
float GetFrameTime();

#endif //RENDER_UTILS_H
