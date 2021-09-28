//
// Created by rock on 9/28/21.
//

#include "Utils.h"

float GetFrameTime(){
    static unsigned long long lastTime=0,currentTime=0;
    timeval current;
    gettimeofday(&current, nullptr);
    currentTime=current.tv_sec*1000+current.tv_usec/1000;
    unsigned long long frameTime=lastTime==0?0:currentTime-lastTime;
    lastTime=currentTime;
    return float(frameTime)/1000.0f;
}

GLuint CompileShader(GLenum shader_type,const char * source_code){
    GLuint shader_to_ret=glCreateShader(shader_type);
    glShaderSource(shader_to_ret,1,&source_code, nullptr);
    glCompileShader(shader_to_ret);
    GLint compile_result=GL_TRUE;
    glGetShaderiv(shader_to_ret,GL_COMPILE_STATUS,&compile_result);
    if(compile_result==GL_FALSE){
        char szLog[1024]={0};
        GLsizei logLen=0;
        glGetShaderInfoLog(shader_to_ret,1024,&logLen,szLog);
        __android_log_print(ANDROID_LOG_ERROR,ALICE_LOG_TAG,"CompileShader %s\ncode:\n%s\n",szLog,source_code);
        glDeleteShader(shader_to_ret);
        shader_to_ret=0;
    }
    return shader_to_ret;
}

GLuint CreateProgram(GLuint vertex_shader,GLuint fragment_shader){
    GLuint program_to_ret=glCreateProgram();
    glAttachShader(program_to_ret,vertex_shader);
    glAttachShader(program_to_ret,fragment_shader);
    glLinkProgram(program_to_ret);
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
    GLint link_result=GL_TRUE;
    glGetProgramiv(program_to_ret,GL_LINK_STATUS,&link_result);
    if(GL_FALSE==link_result){
        char szLog[1024]={0};
        GLsizei logLen=0;
        glGetProgramInfoLog(program_to_ret,1024,&logLen,szLog);
        __android_log_print(ANDROID_LOG_ERROR,ALICE_LOG_TAG,"CreateProgram %s\n",szLog);
        glDeleteProgram(program_to_ret);
        program_to_ret=0;
    }
    return program_to_ret;
}

GLuint CreateStandardProgram(const char *vertex_shader_path,const char * fragment_shader_path){
    int filesize=0;
    unsigned char * filecontent=LoadFileContent(vertex_shader_path,filesize);
    GLuint vsshader=CompileShader(GL_VERTEX_SHADER,(char*)filecontent);
    delete [] filecontent;
    filecontent=LoadFileContent(fragment_shader_path,filesize);
    GLuint fsshader=CompileShader(GL_FRAGMENT_SHADER,(char*)filecontent);
    delete [] filecontent;
    GLuint program=CreateProgram(vsshader,fsshader);
    glDeleteShader(vsshader);
    glDeleteShader(fsshader);
    return program;
}