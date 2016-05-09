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

//Vec4f Vec4f::operator*(Matrix &a)
//{
//    long double rx = a.get(0, 0) * x + a.get(1, 0) * y + a.get(2, 0) * z + a.get(3, 0) * w;
//    long double ry = a.get(0, 1) * x + a.get(1, 1) * y + a.get(2, 1) * z + a.get(3, 1) * w;
//    long double rz = a.get(0, 2) * x + a.get(1, 2) * y + a.get(2, 2) * z + a.get(3, 2) * w;
//    long double rw = a.get(0, 3) * x + a.get(1, 3) * y + a.get(2, 3) * z + a.get(3, 3) * w;
    
//    return Vec4f(rx, ry, rz, rw);
//}

Vec4f Vec4f::operator+(Vec4f &v)
{
    Vec3f v1 = Vec3f(*this);
    Vec3f v2 = Vec3f(v);
    
    return Vec4f(v1 + v2);
}
