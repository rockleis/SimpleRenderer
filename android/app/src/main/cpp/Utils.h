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
float GetFrameTime();

#endif //RENDER_UTILS_H
