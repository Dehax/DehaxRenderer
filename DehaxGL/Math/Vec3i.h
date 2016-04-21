#ifndef VEC3I_H
#define VEC3I_H

#include <cmath>

struct Vec3i
{
public:
    explicit Vec3i(int x, int y, int z);
    
    long double length() const;
    
    int x;
    int y;
    int z;
};

#endif // VEC3I_H
