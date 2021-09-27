#include <jni.h>
#include <string>

extern "C" JNIEXPORT jstring JNICALL
Java_com_rock_render_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++ my name is rocklei";
    return env->NewStringUTF(hello.c_str());
}
