#ifndef VEC3I_H
#define VEC3I_H

#include "dehaxgl_global.h"
#include <cmath>
#include "Vec3f.h"

//struct Vec3f;

struct DEHAXGLSHARED_EXPORT Vec3i
{
public:
    explicit Vec3i(int x, int y, int z);
    Vec3i(const Vec3f &v3f);
    
    Vec3i operator-(const Vec3i &v3) const;
    
    long double length() const;
    
    int x;
    int y;
    int z;
};

#endif // VEC3I_H
