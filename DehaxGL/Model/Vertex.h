#ifndef VERTEX_H
#define VERTEX_H

#include "Math/Vec3f.h"

struct Vertex
{
public:
    explicit Vertex(long double x, long double y, long double z);
    explicit Vertex(Vec3f position);
    
private:
    Vec3f m_position;
};

#endif // VERTEX_H
