#include "Vec3f.h"

Vec3f::Vec3f()
    : x(0.0L), y(0.0L), z(0.0L)
{
}

Vec3f::Vec3f(long double x, long double y, long double z)
    : x(x), y(y), z(z)
{
}

Vec3f Vec3f::normal(Vec3f v3)
{
    long double length = v3.length();
    
    return Vec3f(v3.x / length, v3.y / length, v3.z / length);
}

Vec3f Vec3f::cross(Vec3f v1, Vec3f v2)
{
    return Vec3f(v1.z * v2.y - v1.y * v2.z, v1.x * v2.z - v1.z * v2.x, v1.y * v2.x - v1.x * v2.y);
}

long double Vec3f::length() const
{
    return sqrtl(x * x + y * y + z * z);
}

Vec3f Vec3f::operator-() const
{
    return Vec3f(-x, -y, -z);
}

Vec3f Vec3f::operator-(const Vec3f &v3) const
{
    return Vec3f(x - v3.x, y - v3.y, z - v3.z);
}

long double Vec3f::operator*(const Vec3f &v3) const
{
    return x * v3.x + y * v3.y + z * v3.z;
}
