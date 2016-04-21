#include "Vec3i.h"

Vec3i::Vec3i(int x, int y, int z)
    : x(x), y(y), z(z)
{
}

long double Vec3i::length() const
{
    return sqrtl((long double)(x * x + y * y + z * z));
}
