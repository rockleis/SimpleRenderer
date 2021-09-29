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
GLuint  ibo;

GLuint  program;
GLint   modelMatrixLocation,viewMatrixLocation,projectionMatrixLocation;
GLint   attrPositionLocation,attrTexCoordLocation;
GLuint  texture1,texture2,texture3;

// m v p 矩阵
glm::mat4 modelMatrix1,viewMatrix,projectionMatrix, modelMatrix2, modelMatrix3;

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
    glClearColor(0.8f,0.4f,0.1f,1.0f);

    Vertice vertices[4];
    vertices[0].mPosition[0] = -100.0f; //x
    vertices[0].mPosition[1] = -100.0f; //y
    vertices[0].mPosition[2] = -2.0f; //z
    vertices[0].mPosition[3] = 1.0f; //w
    vertices[0].mTexcoord[0]=0.0f;//u
    vertices[0].mTexcoord[1]=0.0f;//v
    vertices[0].mTexcoord[2]=0.0f;//
    vertices[0].mTexcoord[3]=0.0f;//

    vertices[1].mPosition[0] =  100.0f; //x
    vertices[1].mPosition[1] = -100.0f; //y
    vertices[1].mPosition[2] = -2.0f; //z
    vertices[1].mPosition[3] = 1.0f; //w
    vertices[1].mTexcoord[0]=1.0f;//u
    vertices[1].mTexcoord[1]=0.0f;//v
    vertices[1].mTexcoord[2]=0.0f;//
    vertices[1].mTexcoord[3]=0.0f;//

    vertices[2].mPosition[0] = -100.0f; //x
    vertices[2].mPosition[1] = 100.0f; //y
    vertices[2].mPosition[2] = -2.0f; //z
    vertices[2].mPosition[3] = 1.0f; //w
    vertices[2].mTexcoord[0]=0.0f;//u
    vertices[2].mTexcoord[1]=1.0f;//v
    vertices[2].mTexcoord[2]=0.0f;//
    vertices[2].mTexcoord[3]=0.0f;//

    vertices[3].mPosition[0] = 100.0f; //x
    vertices[3].mPosition[1] = 100.0f; //y
    vertices[3].mPosition[2] = -2.0f; //z
    vertices[3].mPosition[3] = 1.0f; //w
    vertices[3].mTexcoord[0]=1.0f;//u
    vertices[3].mTexcoord[1]=1.0f;//v
    vertices[3].mTexcoord[2]=0.0f;//
    vertices[3].mTexcoord[3]=0.0f;//

    modelMatrix1=glm::translate(0.0f,300.0f,-1.0f);
    //modelMatrix=glm::scale(modelMatrix,glm::vec3(4.0, 4.0, 1.30));

    modelMatrix2=glm::translate(300.0f,0.0f,-2.0f);
    modelMatrix2=glm::translate(-300.0f,0.0f,-2.0f);

    //描述了每三个点顺序绘制一个三角形， 节省点 常用来做四边形绘制
    unsigned short indexes[]={ 0,1,2,1,3,2};
    ibo=CreateBufferObject(GL_ELEMENT_ARRAY_BUFFER,indexes,sizeof(unsigned short)*6,GL_STATIC_DRAW);
    vbo=CreateBufferObject(GL_ARRAY_BUFFER,vertices,sizeof(Vertice)*4,GL_STATIC_DRAW);

    //uniform 一致的， 所有的点共用一致的举证
    //attribute 数据跟着顶点走，归纳为顶点属性
    program=CreateStandardProgram("test.vs","test.fs");
    attrPositionLocation=glGetAttribLocation(program,"position");
    attrTexCoordLocation=glGetAttribLocation(program,"texcoord");
    modelMatrixLocation=glGetUniformLocation(program,"U_ModelMatrix");
    viewMatrixLocation=glGetUniformLocation(program,"U_ViewMatrix");
    projectionMatrixLocation=glGetUniformLocation(program,"U_ProjectionMatrix");

    texture1=CreateTextureFromFile("head.png");
    texture2=CreateTextureFromFile("content.png");
    texture3=CreateTextureFromFile("weixin.png");

    __android_log_print(ANDROID_LOG_INFO,ALICE_LOG_TAG,"%d,%d,%d,%d",
                        attrPositionLocation,modelMatrixLocation,viewMatrixLocation,projectionMatrixLocation);

}
extern "C" JNIEXPORT void JNICALL JNI_RENDER(OnViewportChanged)(
        JNIEnv*env,
        jobject MainActivity,jint width,jint height
){

//    一个一个来,首先得设置gluPerspective,来看看它的参数都表示什么意思
//    fovy,这个最难理解,我的理解是,眼睛睁开的角度,即,视角的大小,如果设置为0,相当你闭上眼睛了,所以什么也看不到,如果为180,那么可以认为你的视界很广阔,
//            aspect,这个好理解,就是实际窗口的纵横比,即x/y
//    zNear,这个呢,表示你近处,的裁面,
//            zFar表示远处的裁面,

    __android_log_print(ANDROID_LOG_INFO,ALICE_LOG_TAG,"OnViewportChanged %dx%d",width,height);
    glViewport(0,0,width,height);
    //右手坐标系，z轴朝外正方向
    viewMatrix=glm::lookAt(glm::vec3(0.0f,0.0f,0.5f),
                           glm::vec3(0.0,0.0,-1.0f),
                           glm::vec3(0.0,1.0f,0.0f));

    //OpenGL默认使用右手坐标系
    //projectionMatrix=glm::perspective(45.0f,float(width)/float(height),0.1f,1000.0f);

    //正交投影，适合2dui
    float half_width=float(width)/2.0f;
    float half_height=float(height)/2.0f;
    projectionMatrix=glm::ortho(-half_width,half_width,-half_height,half_height,0.1f,100.0f);
}
extern "C" JNIEXPORT void JNICALL JNI_RENDER(Render)(
        JNIEnv*env,
        jobject MainActivity
){
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);

    glUseProgram(program);
    //glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glUniformMatrix4fv(modelMatrixLocation,1,GL_FALSE,glm::value_ptr(modelMatrix1));
    glUniformMatrix4fv(viewMatrixLocation,1,GL_FALSE,glm::value_ptr(viewMatrix));
    glUniformMatrix4fv(projectionMatrixLocation,1,GL_FALSE,glm::value_ptr(projectionMatrix));

    commitRendData(vbo,ibo,texture1,modelMatrix1,
            attrPositionLocation,attrTexCoordLocation,modelMatrixLocation);
    commitRendData(vbo,ibo,texture2,modelMatrix2,
                   attrPositionLocation,attrTexCoordLocation,modelMatrixLocation);
    commitRendData(vbo,ibo,texture3,modelMatrix3,
                   attrPositionLocation,attrTexCoordLocation,modelMatrixLocation);

    glUseProgram(0);
}
