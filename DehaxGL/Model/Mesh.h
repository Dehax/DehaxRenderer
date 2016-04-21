#ifndef MESH_H
#define MESH_H

#include <vector>
#include "Vertex.h"
#include "Face.h"

class Mesh
{
public:
    explicit Mesh();
    
    int numVertices() const;
    int numFaces() const;
    
    Vertex getVertex(const int index) const;
    Face getFace(const int index) const;
    
    void addVertex(Vertex vertex);
    void addFace(Face face);
    void clearVertices();
    void clearFaces();
    
private:
    std::vector<Vertex> m_vertices;
    std::vector<Face> m_faces;
};

#endif // MESH_H
