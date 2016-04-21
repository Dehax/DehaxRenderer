#include "Vertex.h"

Vertex::Vertex(long double x, long double y, long double z)
    : m_position(x, y, z)
{
}

Vertex::Vertex(Vec3f position)
    : m_position(position)
{
}
