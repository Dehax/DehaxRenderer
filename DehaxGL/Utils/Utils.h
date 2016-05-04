#ifndef UTILS_H
#define UTILS_H

#include "dehaxgl_global.h"
#include <cmath>

typedef unsigned int ARGB;

inline constexpr ARGB RGBA(int r, int g, int b, int a)
{ return ((a & 0xffu) << 24) | ((r & 0xffu) << 16) | ((g & 0xffu) << 8) | (b & 0xffu); }

inline constexpr int RED(ARGB rgb)
{ return ((rgb >> 16) & 0xff); }

inline constexpr int GREEN(ARGB rgb)
{ return ((rgb >> 8) & 0xff); }

inline constexpr int BLUE(ARGB rgb)
{ return (rgb & 0xff); }

inline long double degreeToRadian(long double angle)
{
    return M_PI * angle / 180.0L;
}

inline long double radianToDegree(long double angle)
{
    return angle * (180.0L / M_PI);
}

#endif // UTILS_H
