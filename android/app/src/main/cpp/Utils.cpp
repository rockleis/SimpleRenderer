//
// Created by rock on 9/28/21.
//

#include "Utils.h"
//#include "../../../../../../../../Library/Android/sdk/ndk/19.0.5232133/toolchains/llvm/prebuilt/darwin-x86_64/sysroot/usr/include/sys/time.h"
//#include "../../../../../../../../Library/Android/sdk/ndk/19.0.5232133/toolchains/llvm/prebuilt/darwin-x86_64/sysroot/usr/include/linux/time.h"


float GetFrameTime(){
    static unsigned long long lastTime=0,currentTime=0;
    timeval current;
    gettimeofday(&current, nullptr);
    currentTime=current.tv_sec*1000+current.tv_usec/1000;
    unsigned long long frameTime=lastTime==0?0:currentTime-lastTime;
    lastTime=currentTime;
    return float(frameTime)/1000.0f;
}