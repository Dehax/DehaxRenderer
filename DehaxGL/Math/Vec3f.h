#ifndef VEC3F_H
#define VEC3F_H

#include "dehaxgl_global.h"
#include <cmath>
#include <QString>
#include <QStringBuilder>
#include <QTextStream>

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
    
    inline long double length() const
    {
        return std::sqrt(x * x + y * y + z * z);
    }
    
    Vec3f operator-() const;
    Vec3f operator-(const Vec3f &v3) const;
    Vec3f operator+(const Vec3f &v3) const;
    Vec3f operator+=(const Vec3f &v3);
    long double operator*(const Vec3f &v3) const;
    Vec3f operator*(const long double &a) const;
    Vec3f operator/(const long double &a) const;
    
    operator QString() const;
    
    long double x;
    long double y;
    long double z;
};

QTextStream &operator<<(QTextStream &out, const Vec3f &v3f);
QTextStream &operator>>(QTextStream &in, Vec3f &v3f);

#endif // VEC3F_H
