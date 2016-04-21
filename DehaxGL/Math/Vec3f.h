#ifndef VEC3F_H
#define VEC3F_H

#include <cmath>

struct Vec3f
{
public:
    explicit Vec3f();
    explicit Vec3f(long double x, long double y, long double z);
    
    static Vec3f normal(Vec3f v3);
    static Vec3f cross(Vec3f v1, Vec3f v2);
    
    long double length() const;
    
    Vec3f operator-() const;
    Vec3f operator-(const Vec3f &v3) const;
    long double operator*(const Vec3f &v3) const;
    
    long double x;
    long double y;
    long double z;
};

#endif // VEC3F_H
