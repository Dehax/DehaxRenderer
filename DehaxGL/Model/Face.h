#ifndef FACE_H
#define FACE_H

#include "dehaxgl_global.h"

struct DEHAXGLSHARED_EXPORT Face
{
public:
    explicit Face(int v1, int v2, int v3);
    
    int v1;
    int v2;
    int v3;
};

#endif // FACE_H
