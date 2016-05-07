#ifndef VEC4F_H
#define VEC4F_H

#include "dehaxgl_global.h"
#include "Matrix.h"

//struct Vec3f;

struct DEHAXGLSHARED_EXPORT Vec4f
{
public:
    explicit Vec4f();
    explicit Vec4f(long double x, long double y, long double z, long double w);
    Vec4f(const Vec3f &v3);
    
    Vec4f operator*(Matrix &a);
    Vec4f operator+(Vec4f &v);
    
    long double x;
    long double y;
    long double z;
    long double w;
};

#endif // VEC4F_H
