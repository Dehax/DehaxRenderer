#include "Vec2i.h"

Vec2i::Vec2i(int x, int y)
    : x(x), y(y)
{
}

long double Vec2i::length() const
{
    return sqrtl(x * x + y * y);
}
