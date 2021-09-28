#include <jni.h>
#include "Sence.h"
#include "Utils.h"

#define JNI_METHOD2(CLASS2,FUNC2) Java_##CLASS2##_##FUNC2
#define JNI_METHOD1(CLASS1,FUNC1) JNI_METHOD2(CLASS1,FUNC1)

#ifndef COM_ROCK_RENDER_CLASS_NAME
#define COM_ROCK_RENDER_CLASS_NAME com_rock_render_MainActivity
#endif

#define JNI_RENDER(FUNC) JNI_METHOD1(COM_ROCK_RENDER_CLASS_NAME,FUNC)

static AAssetManager *sAssetManager= nullptr;
GLuint  vbo;//vertex buffer object
GLuint  program;
GLint   modelMatrixLocation,viewMatrixLocation,projectionMatrixLocation;
GLint   attrPositionLocation;

unsigned char * LoadFileContent(const char *path,int&filesize){
    unsigned char *filecontent=nullptr;
    filesize=0;
    AAsset*asset=AAssetManager_open(sAssetManager,path,AASSET_MODE_UNKNOWN);
    if(asset!= nullptr){
        filesize=AAsset_getLength(asset);
        filecontent=new unsigned char[filesize+1];
        AAsset_read(asset,filecontent,filesize);
        filecontent[filesize]=0;
        AAsset_close(asset);
    }
    return filecontent;
}

extern "C" JNIEXPORT void JNICALL JNI_RENDER(Init)(
        JNIEnv*env,
        jobject MainActivity,
        jobject am
){
    sAssetManager = AAssetManager_fromJava(env,am);
    __android_log_print(ANDROID_LOG_INFO,ALICE_LOG_TAG,"Init");
    glClearColor(0.1f,0.4f,0.1f,1.0f);

    Vertice vertices[3];
    vertices[0].mPosition[0] = -0.5f; //x
    vertices[0].mPosition[1] = -0.5f; //y
    vertices[0].mPosition[2] = -2.0f; //z
    vertices[0].mPosition[3] = 1.0f; //w

    vertices[1].mPosition[0] =  0.5f; //x
    vertices[1].mPosition[1] = -0.5f; //y
    vertices[1].mPosition[2] = -2.0f; //z
    vertices[1].mPosition[3] = 1.0f; //w

    vertices[2].mPosition[0] = 0.0f; //x
    vertices[2].mPosition[1] = 0.5f; //y
    vertices[2].mPosition[2] = -2.0f; //z
    vertices[2].mPosition[3] = 1.0f; //w


//    使用glGenBuffers()生成新缓存对象。
//    使用glBindBuffer()绑定缓存对象。
//    使用glBufferData()将顶点数据拷贝到缓存对象中。
    //GLuint vbo;
    glGenBuffers(1,&vbo);
    glBindBuffer(GL_ARRAY_BUFFER,vbo);
    glBufferData(GL_ARRAY_BUFFER,sizeof(Vertice)*3, nullptr,GL_STATIC_DRAW);//alloc gpu
    glBufferSubData(GL_ARRAY_BUFFER,0,sizeof(Vertice)*3,vertices);//cpu -> gpu
    //glBufferData(GL_ARRAY_BUFFER,sizeof(Vertice)*3,vertices,GL_STATIC_DRAW);//cpu -> gpu
    glBindBuffer(GL_ARRAY_BUFFER,0);

    //uniform 一致的， 所有的点共用一致的举证
    //attribute 数据跟着顶点走，归纳为顶点属性
    program=CreateStandardProgram("test.vs","test.fs");
    attrPositionLocation=glGetAttribLocation(program,"position");
    modelMatrixLocation=glGetUniformLocation(program,"U_ModelMatrix");
    viewMatrixLocation=glGetUniformLocation(program,"U_ViewMatrix");
    projectionMatrixLocation=glGetUniformLocation(program,"U_ProjectionMatrix");
    __android_log_print(ANDROID_LOG_INFO,ALICE_LOG_TAG,"%d,%d,%d,%d",
                        attrPositionLocation,modelMatrixLocation,viewMatrixLocation,projectionMatrixLocation);

}
extern "C" JNIEXPORT void JNICALL JNI_RENDER(OnViewportChanged)(
        JNIEnv*env,
        jobject MainActivity,jint width,jint height
){
    glViewport(0,0,width,height);
}
extern "C" JNIEXPORT void JNICALL JNI_RENDER(Render)(
        JNIEnv*env,
        jobject MainActivity
){
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);
}
