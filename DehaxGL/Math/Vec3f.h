#ifndef VEC3F_H
#define VEC3F_H

#include "dehaxgl_global.h"
#include <cmath>
#include <QString>
#include <QStringBuilder>
//#include "Vec3i.h"
//#include "Vec4f.h"

struct Vec4f;
struct Vec3i;

struct DEHAXGLSHARED_EXPORT Vec3f
{
public:
    explicit Vec3f();
    explicit Vec3f(long double a);
    explicit Vec3f(long double x, long double y, long double z);
    Vec3f(const Vec3i &v3i);
    explicit Vec3f(const Vec4f &v4);
    
    static Vec3f normal(const Vec3f &v3);
    static Vec3f cross(const Vec3f &a, const Vec3f &b);
    
    long double length() const;
    
    Vec3f operator-() const;
    Vec3f operator-(const Vec3f &v3) const;
    Vec3f operator+(const Vec3f &v3) const;
    Vec3f operator+=(const Vec3f &v3);
    long double operator*(const Vec3f &v3) const;
    Vec3f operator*(const long double &a) const;
    
    operator QString() const;
    
    long double x;
    long double y;
    long double z;
};

#endif // VEC3F_H
