#ifndef VEC2I_H
#define VEC2I_H

#include "dehaxgl_global.h"
#include <cmath>

struct DEHAXGLSHARED_EXPORT Vec2i
{
public:
    explicit Vec2i(int x, int y);
    
    inline long double length() const
    {
        return std::sqrt((long double)(x * x + y * y));
    }
    
    int x;
    int y;
};

#endif // VEC2I_H
