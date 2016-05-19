#include "Mesh.h"

Mesh::Mesh()
    : m_maxLocalScale(1.0L)
{
}

Mesh::Mesh(const Mesh &mesh)
{
    m_vertices = mesh.m_vertices;
    m_faces = mesh.m_faces;
    m_maxLocalScale = mesh.m_maxLocalScale;
}

void Mesh::addVertex(const Vertex &vertex)
{
    long double x = std::abs(vertex.x());
    long double y = std::abs(vertex.y());
    long double z = std::abs(vertex.z());
    
    if (x > m_maxLocalScale) {
        m_maxLocalScale = x;
    }
    
    if (y > m_maxLocalScale) {
        m_maxLocalScale = y;
    }
    
    if (z > m_maxLocalScale) {
        m_maxLocalScale = z;
    }
    
    m_vertices.push_back(vertex);
}

void Mesh::addFace(const Face &face)
{
    m_faces.push_back(face);
}

void Mesh::clearVertices()
{
    m_vertices.clear();
}

void Mesh::clearFaces()
{
    m_faces.clear();
}
