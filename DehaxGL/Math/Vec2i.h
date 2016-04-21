#ifndef VEC2I_H
#define VEC2I_H

#include <cmath>

struct Vec2i
{
public:
    explicit Vec2i(int x, int y);
    
    long double length() const;
    
    int x;
    int y;
};

#endif // VEC2I_H
