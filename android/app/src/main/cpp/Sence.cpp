#include "Sence.h"

#define JNI_METHOD2(CLASS2,FUNC2) Java_##CLASS2##_##FUNC2
#define JNI_METHOD1(CLASS1,FUNC1) JNI_METHOD2(CLASS1,FUNC1)

#ifndef COM_ROCK_RENDER_CLASS_NAME
#define COM_ROCK_RENDER_CLASS_NAME com_rock_render_MainActivity
#endif

#define JNI_RENDER(FUNC) JNI_METHOD1(COM_ROCK_RENDER_CLASS_NAME,FUNC)

extern "C" JNIEXPORT void JNICALL JNI_RENDER(Init)(
        JNIEnv*env,
        jobject MainActivity
){
    glClearColor(0.1f,0.4f,0.1f,1.0f);
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
