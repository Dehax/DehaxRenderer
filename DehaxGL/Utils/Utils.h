#ifndef UTILS_H
#define UTILS_H

#include <cmath>

typedef unsigned int ARGB;

#define RGBA(r, g, b, a) \
    ARGB(((a & 0xff) << 24) | ((r & 0xff) << 16) | ((g & 0xff) << 8) | (b & 0xff))


inline long double degreeToRadian(long double angle)
{
    return M_PI * angle / 180.0L;
}

inline long double radianToDegree(long double angle)
{
    return angle * (180.0L / M_PI);
}

#endif // UTILS_H
