#include "Vec4f.h"

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

Vec4f Vec4f::operator*(Matrix &a)
{
    long double rx = a[0][0] * x + a[1][0] * y + a[2][0] * z + a[3][0] * w;
    long double ry = a[0][1] * x + a[1][1] * y + a[2][1] * z + a[3][1] * w;
    long double rz = a[0][2] * x + a[1][2] * y + a[2][2] * z + a[3][2] * w;
    long double rw = a[0][3] * x + a[1][3] * y + a[2][3] * z + a[3][3] * w;
    
    return Vec4f(rx, ry, rz, rw);
}

Vec4f Vec4f::operator+(Vec4f &v)
{
    Vec3f v1 = Vec3f(*this);
    Vec3f v2 = Vec3f(v);
    
    return Vec4f(v1 + v2);
}
