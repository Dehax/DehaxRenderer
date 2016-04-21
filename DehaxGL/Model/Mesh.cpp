#include "Mesh.h"

Mesh::Mesh()
{
    
}

int Mesh::numVertices() const
{
    return m_vertices.size();
}

int Mesh::numFaces() const
{
    return m_faces.size();
}

Vertex Mesh::getVertex(const int index) const
{
    return m_vertices[index];
}

Face Mesh::getFace(const int index) const
{
    return m_faces[index];
}

void Mesh::addVertex(Vertex vertex)
{
    m_vertices.push_back(vertex);
}

void Mesh::addFace(Face face)
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
