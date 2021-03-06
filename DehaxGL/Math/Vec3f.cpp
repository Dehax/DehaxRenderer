#include "Vec3f.h"
#include "Vec3i.h"
#include "Vec4f.h"

Vec3f::Vec3f()
    : x(0.0L), y(0.0L), z(0.0L)
{
}

Vec3f::Vec3f(long double a)
    : x(a), y(a), z(a)
{
}

Vec3f::Vec3f(long double x, long double y, long double z)
    : x(x), y(y), z(z)
{
}

Vec3f::Vec3f(const Vec3i &v3i)
    : x(v3i.x), y(v3i.y), z(v3i.z)
{
}

Vec3f::Vec3f(const Vec4f &v4)
    : x(v4.x / v4.w), y(v4.y / v4.w), z(v4.z / v4.w)
{
}

Vec3f Vec3f::normal(const Vec3f &v3)
{
    long double length = v3.length();
    
    return Vec3f(v3.x / length, v3.y / length, v3.z / length);
}

Vec3f Vec3f::cross(const Vec3f &a, const Vec3f &b)
{
    // LHS
    return Vec3f(a.z * b.y - a.y * b.z, a.x * b.z - a.z * b.x, a.y * b.x - a.x * b.y);
}

Vec3f Vec3f::operator-() const
{
    return Vec3f(-x, -y, -z);
}

Vec3f Vec3f::operator-(const Vec3f &v3) const
{
    return Vec3f(x - v3.x, y - v3.y, z - v3.z);
}

Vec3f Vec3f::operator+(const Vec3f &v3) const
{
    return Vec3f(x + v3.x, y + v3.y, z + v3.z);
}

Vec3f Vec3f::operator+=(const Vec3f &v3)
{
    *this = *this + v3;
    
    return *this;
}

long double Vec3f::operator*(const Vec3f &v3) const
{
    return x * v3.x + y * v3.y + z * v3.z;
}

Vec3f Vec3f::operator*(const long double &a) const
{
    return Vec3f(x * a, y * a, z * a);
}

Vec3f Vec3f::operator/(const long double &a) const
{
    return Vec3f(x / a, y / a, z / a);
}

Vec3f::operator QString() const
{
    return QString::number(x, 'f', 2) % ", " % QString::number(y, 'f', 2) % ", " % QString::number(z, 'f', 2);
}

QTextStream &operator<<(QTextStream &out, const Vec3f &v3f)
{
    char blank = ' ';
    out << (double)v3f.x << blank << (double)v3f.y << blank << (double)v3f.z;
    
    return out;
}

QTextStream &operator>>(QTextStream &in, Vec3f &v3f)
{
    double x, y, z;
    in >> x >> y >> z;
    
    v3f.x = x;
    v3f.y = y;
    v3f.z = z;
    
    return in;
}
