#include "Vertex.h"

Vertex::Vertex()
    : Vertex(0.0L, 0.0L, 0.0L)
{
}

Vertex::Vertex(const long double &x, const long double &y, const long double &z)
    : m_position(x, y, z)
{
}

Vertex::Vertex(const Vec3f &position)
    : m_position(position)
{
}

long double Vertex::x() const
{
    return m_position.x;
}

long double Vertex::y() const
{
    return m_position.y;
}

long double Vertex::z() const
{
    return m_position.z;
}

Vec3f Vertex::position() const
{
    return m_position;
}
