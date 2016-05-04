#ifndef MESH_H
#define MESH_H

#include "dehaxgl_global.h"
#include <vector>
#include <cmath>
#include "Vertex.h"
#include "Face.h"

class DEHAXGLSHARED_EXPORT Mesh
{
public:
    explicit Mesh();
    explicit Mesh(const Mesh &mesh);
    
    int numVertices() const;
    int numFaces() const;
    
    Vertex getVertex(const int index) const;
    Face getFace(const int index) const;
    
    void addVertex(const Vertex &vertex);
    void addFace(const Face &face);
    void clearVertices();
    void clearFaces();
    
    long double maxLocalScale() const;
    
private:
    std::vector<Vertex> m_vertices;
    std::vector<Face> m_faces;
    long double m_maxLocalScale;
};

#endif // MESH_H
