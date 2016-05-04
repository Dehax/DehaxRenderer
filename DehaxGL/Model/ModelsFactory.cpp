#include "ModelsFactory.h"

Model ModelsFactory::box(long double width, long double length, long double height)
{
    width /= 2.0L;
    length /= 2.0L;
    height /= 2.0L;
    
    Mesh *mesh = new Mesh();
    Model model = Model(QString("(G) box"), mesh, RGBA(255, 0, 0, 255));
    
    // -Z
    mesh->addVertex(Vertex(-length, -height, -width)); // 0
    mesh->addVertex(Vertex(-length, height, -width));  // 1
    mesh->addVertex(Vertex(length, height, -width));   // 2
    mesh->addVertex(Vertex(length, -height, -width));  // 3
    
    // +Z
    mesh->addVertex(Vertex(-length, -height, width));  // 4
    mesh->addVertex(Vertex(-length, height, width));   // 5
    mesh->addVertex(Vertex(length, height, width));    // 6
    mesh->addVertex(Vertex(length, -height, width));   // 7
    
    mesh->addFace(Face(0, 1, 3));
    mesh->addFace(Face(3, 1, 2));
    mesh->addFace(Face(3, 2, 7));
    mesh->addFace(Face(7, 2, 6));
    mesh->addFace(Face(7, 6, 4));
    mesh->addFace(Face(4, 6, 5));
    mesh->addFace(Face(4, 5, 0));
    mesh->addFace(Face(0, 5, 1));
    mesh->addFace(Face(1, 5, 2));
    mesh->addFace(Face(2, 5, 6));
    mesh->addFace(Face(3, 4, 0));
    mesh->addFace(Face(7, 4, 3));
    
    return model;
}

Model ModelsFactory::cylinder(long double radius, long double height, int sides)
{
    height /= 2.0L;
    
    Mesh *mesh = new Mesh();
    Model model = Model(QString("(G) cylinder"), mesh, RGBA(0, 255, 0, 255));
    
    // BUG: Неверная генерация.
    int nbVerticesCap = sides + 1;
    
    int verticesLength = nbVerticesCap + nbVerticesCap;// + sides * 2 + 2;
    
    Vertex *vertices = new Vertex[verticesLength];
    int vert = 0;
    const long double _2pi = M_PI * 2.0L;
    
    // Bottom cap
    // Центральная вершина нижней крышки
    vertices[vert++] = Vertex(0.0L, -height, 0.0L);
    
    while (vert <= sides) {
        long double rad = (long double)vert / sides * _2pi;
        vertices[vert] = Vertex(std::cos(rad) * radius, -height, std::sin(rad) * radius);
        vert++;
    }
    
    // Top cap
    vertices[vert++] = Vertex(0.0L, height, 0.0L);
    
    while (vert <= sides * 2 + 1) {
        long double rad = (long double)(vert - sides - 1) / sides * _2pi;
        vertices[vert] = Vertex(std::cos(rad) * radius, height, std::sin(rad) * radius);
        vert++;
    }
    
    // Sides
//    int v = 0;
    
//    while (vert <= verticesLength - 4) {
//        long double rad = (long double)v / sides * _2pi;
//        vertices[vert] = Vertex(std::cos(rad) * radius, height, std::sin(rad) * radius);
//        vertices[vert + 1] = Vertex(std::cos(rad) * radius, 0.0L, std::sin(rad) * radius);
//        vert += 2;
//        v++;
//    }
    
//    vertices[vert] = vertices[sides * 2 + 2];
//    vertices[vert + 1] = vertices[sides * 2 + 3];
    
    // Triangles
    int nbTriangles = sides * 4;//sides * sides;// + sides * 2;
    int *triangles = new int[nbTriangles * 3/* + 3*/];
    
    // Bottom cap
    int tri = 0;
    int i = 0;
    
    while (tri < sides - 1) {
        triangles[i] = 0;
        triangles[i + 1] = tri + 1;
        triangles[i + 2] = tri + 2;
        tri++;
        i += 3;
    }
    
    triangles[i] = 0;
    triangles[i + 1] = tri + 1;
    triangles[i + 2] = 1;
    tri++;
    i += 3;
    
    // Top cap
    tri++;
    
    while (tri < sides * 2) {
        triangles[i] = tri + 2;
        triangles[i + 1] = tri + 1;
        triangles[i + 2] = nbVerticesCap;
        tri++;
        i += 3;
    }
    
    triangles[i] = nbVerticesCap + 1;
    triangles[i + 1] = tri + 1;
    triangles[i + 2] = nbVerticesCap;
    tri++;
    i += 3;
    tri++;
    
    // Sides
    int j = tri;
    
    while (j <= nbTriangles - 2) {
        triangles[i] = tri - nbVerticesCap * 2 + 1;
        triangles[i + 1] = tri - nbVerticesCap + 1;
        triangles[i + 2] = tri - nbVerticesCap * 2 + 2;
        //tri++;
        j++;
        i += 3;
        
        triangles[i] = tri - nbVerticesCap * 2 + 2;
        triangles[i + 1] = tri - nbVerticesCap + 1;
        triangles[i + 2] = tri - nbVerticesCap + 2;
        tri++;
        j++;
        i += 3;
    }
    
    triangles[i] = tri - nbVerticesCap * 2 + 1;
    triangles[i + 1] = tri - nbVerticesCap + 1;
    triangles[i + 2] = 1;
    i += 3;
    
    triangles[i] = 1;
    triangles[i + 1] = tri - nbVerticesCap + 1;
    triangles[i + 2] = 1 + nbVerticesCap;
    
    for (int i = 0; i < verticesLength; i++) {
        mesh->addVertex(vertices[i]);
    }
    
    for (int i = 0; i < nbTriangles * 3; i += 3) {
        mesh->addFace(Face(triangles[i], triangles[i + 1], triangles[i + 2]));
    }
    
    delete[] triangles;
    delete[] vertices;
    
    return model;
}

Model ModelsFactory::lensMount(long double width, long double frontLength, long double backLength, long double height)
{
    width /= 2.0L;
    frontLength /= 2.0L;
    backLength /= 2.0L;
    height /= 2.0L;
    
    Mesh *mesh = new Mesh();
    Model model = Model(QString("(G) lens mount"), mesh, RGBA(0, 0, 255, 255));
    
    // -Z
    mesh->addVertex(Vertex(-frontLength, -height, -width)); // 0
    mesh->addVertex(Vertex(-frontLength, height, -width));  // 1
    mesh->addVertex(Vertex(frontLength, height, -width));   // 2
    mesh->addVertex(Vertex(frontLength, -height, -width));  // 3
    
    // +Z
    mesh->addVertex(Vertex(-backLength, -height, width));  // 4
    mesh->addVertex(Vertex(-backLength, height, width));   // 5
    mesh->addVertex(Vertex(backLength, height, width));    // 6
    mesh->addVertex(Vertex(backLength, -height, width));   // 7
    
    mesh->addFace(Face(0, 1, 3));
    mesh->addFace(Face(3, 1, 2));
    mesh->addFace(Face(3, 2, 7));
    mesh->addFace(Face(7, 2, 6));
    mesh->addFace(Face(7, 6, 4));
    mesh->addFace(Face(4, 6, 5));
    mesh->addFace(Face(4, 5, 0));
    mesh->addFace(Face(0, 5, 1));
    mesh->addFace(Face(1, 5, 2));
    mesh->addFace(Face(2, 5, 6));
    mesh->addFace(Face(3, 4, 0));
    mesh->addFace(Face(7, 4, 3));
    
    return model;
}

//Model ModelsFactory::camera(long double width, long double length, long double height, long double radius, long double lensWidth, long double lensMountLength, long double lensMountWidth, long double marginWidth, long double sideButtonsHeight, long double shutterButtonHeight, long double sideButtonsRadius, long double shutterButtonRadius)
//{
    
//}
