#ifndef VERTEX_H
#define VERTEX_H

#include "dehaxgl_global.h"
#include "../Math/Vec3f.h"

struct DEHAXGLSHARED_EXPORT Vertex
{
public:
    explicit Vertex();
    explicit Vertex(const long double &x, const long double &y, const long double &z);
    explicit Vertex(const Vec3f &position);
    
    long double x() const;
    long double y() const;
    long double z() const;
    Vec3f position() const;
    
private:
    Vec3f m_position;
};

#endif // VERTEX_H
