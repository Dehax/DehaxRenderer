#include "Vec4f.h"

Vec4f::Vec4f()
{
}

Vec4f::Vec4f(long double x, long double y, long double z, long double w)
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
}

Vec4f::Vec4f(const Vec3f &v3)
{
    x = v3.x;
    y = v3.y;
    z = v3.z;
    w = 1.0L;
}

Vec4f Vec4f::operator+(Vec4f &v)
{
    Vec3f v1 = Vec3f(*this);
    Vec3f v2 = Vec3f(v);
    
    return Vec4f(v1 + v2);
}
