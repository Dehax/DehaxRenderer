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
    mesh->addVertex(Vertex(-backLength, -height, width));   // 4
    mesh->addVertex(Vertex(-backLength, height, width));    // 5
    mesh->addVertex(Vertex(backLength, height, width));     // 6
    mesh->addVertex(Vertex(backLength, -height, width));    // 7
    
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

Model ModelsFactory::camera(long double width, long double length, long double height, long double radius, long double lensWidth, long double lensMountLength, long double lensMountWidth, long double marginWidth, long double sideButtonsHeight, long double shutterButtonHeight, long double sideButtonsRadius, long double shutterButtonRadius)
{
    if (width <= 0.0L || 3.0L * width >= length || 1.5L * width >= height) {
        throw std::out_of_range("Ширина должна быть больше 0.0, меньше 1/3 длины и меньше 2/3 высоты!");
    }
    
    if (length <= 0.0L) {
        throw std::out_of_range("Длина должна быть больше 0.0!");
    }
    
    if (height <= 0.0L || height >= length) {
        throw std::out_of_range("Высота должна быть больше 0.0 и меньше длины!");
    }
    
    if (radius <= 0.0L || radius > lensMountLength) {
        throw std::out_of_range("Радиус объектива должен быть больше 0.0 и меньше либо равен длине крепления объектива!");
    }
    
    if (lensWidth <= 0.0L) {
        throw std::out_of_range("Ширина объектива должна быть больше 0.0!");
    }
    
    if (lensMountLength <= 0.25L * length || lensMountLength >= 0.5L * length) {
        throw std::out_of_range("Длина крепления объектива должна быть больше 1/4 и меньше 1/2 длины фотоаппарата!");
    }
    
    if (lensMountWidth <= 0.0L || lensMountWidth >= width) {
        throw std::out_of_range("Ширина крепления объектива должна быть больше 0.0 и меньше ширины фотоаппарата!");
    }
    
    if (marginWidth <= 0.0L || 2.0L * marginWidth + lensMountLength >= length) {
        throw std::out_of_range("Длина свободной части должна быть больше 0.0 и соответствовать длине крепления объектива!");
    }
    
    if (sideButtonsHeight <= 0.0L) {
        throw std::out_of_range("Высота боковых кнопок должна быть больше 0.0!");
    }
    
    if (shutterButtonHeight <= 0.0L) {
        throw std::out_of_range("Высота кнопки спуска затвора должна быть больше 0.0!");
    }
    
    if (sideButtonsRadius <= 0.0L || sideButtonsRadius >= width) {
        throw std::out_of_range("Радиус боковых кнопок должен быть больше 0.0 и меньше ширины фотоаппарата!");
    }
    
    if (shutterButtonRadius <= 0.0L || 3.0L * shutterButtonRadius >= width) {
        throw std::out_of_range("Радиус кнопки спуска затвора должен быть больше 0.0 и меньше 1/3 ширины фотоаппарата!");
    }
    
    Mesh *mesh = new Mesh();
    Model result = Model("Camera", mesh, RGBA(255, 0, 255, 255));
    result.setParameters(width, length, height, radius, lensWidth, lensMountLength, lensMountWidth, marginWidth, sideButtonsHeight, shutterButtonHeight, sideButtonsRadius, shutterButtonRadius);
    
    Model base = ModelsFactory::box(width, length, height);
    
    Mesh *currentMesh = base.mesh();
    int numVertices = currentMesh->numVertices();
    int numFaces = currentMesh->numFaces();
    int verticesOffset = 0;
    
    for (int i = 0; i < numVertices; i++) {
        mesh->addVertex(currentMesh->getVertex(i));
    }
    
    for (int i = 0; i < numFaces; i++) {
        Face face = currentMesh->getFace(i);
        face.v1 += verticesOffset;
        face.v2 += verticesOffset;
        face.v3 += verticesOffset;
        mesh->addFace(face);
    }
    
    verticesOffset += numVertices;
    
    Model lensMount = ModelsFactory::lensMount(lensMountWidth, lensMountLength, length - marginWidth * 2.0L, height);
    
    currentMesh = lensMount.mesh();
    numVertices = currentMesh->numVertices();
    numFaces = currentMesh->numFaces();
    
    for (int i = 0; i < numVertices; i++) {
        Vertex vertex = currentMesh->getVertex(i);
        mesh->addVertex(Vertex(vertex.x(), vertex.y(), vertex.z() - (width / 2.0L + lensMountWidth / 2.0L)));
    }
    
    for (int i = 0; i < numFaces; i++) {
        Face face = currentMesh->getFace(i);
        face.v1 += verticesOffset;
        face.v2 += verticesOffset;
        face.v3 += verticesOffset;
        mesh->addFace(face);
    }
    
    verticesOffset += numVertices;
    
    Model lens = ModelsFactory::cylinder(radius, lensWidth, 12);
    
    currentMesh = lens.mesh();
    numVertices = currentMesh->numVertices();
    numFaces = currentMesh->numFaces();
    
    for (int i = 0; i < numVertices; i++) {
        Vertex vertex = currentMesh->getVertex(i);
        Matrix rotationMatrix = Matrix::rotationX(degreeToRadian(90.0L));
        Vec4f newPosition = Vec4f(vertex.position()) * rotationMatrix;
        Vec3f newPositionV3 = Vec3f(newPosition);
        mesh->addVertex(Vertex(newPositionV3.x, newPositionV3.y, newPositionV3.z - (width / 2.0L + lensMountWidth + lensWidth / 2.0L)));
    }
    
    for (int i = 0; i < numFaces; i++) {
        Face face = currentMesh->getFace(i);
        face.v1 += verticesOffset;
        face.v2 += verticesOffset;
        face.v3 += verticesOffset;
        mesh->addFace(face);
    }
    
    verticesOffset += numVertices;
    
    Model rightSideButton = ModelsFactory::cylinder(sideButtonsRadius, sideButtonsHeight, 12);
    
    currentMesh = rightSideButton.mesh();
    numVertices = currentMesh->numVertices();
    numFaces = currentMesh->numFaces();
    
    for (int i = 0; i < numVertices; i++) {
        Vertex vertex = currentMesh->getVertex(i);
        mesh->addVertex(Vertex(vertex.x() - length / 2.0L + marginWidth / 2.0L, vertex.y() + height / 2.0L + sideButtonsHeight / 2.0L, vertex.z()));
    }
    
    for (int i = 0; i < numFaces; i++) {
        Face face = currentMesh->getFace(i);
        face.v1 += verticesOffset;
        face.v2 += verticesOffset;
        face.v3 += verticesOffset;
        mesh->addFace(face);
    }
    
    verticesOffset += numVertices;
    
    Model leftSideButton = ModelsFactory::cylinder(sideButtonsRadius, sideButtonsHeight, 12);
    
    currentMesh = leftSideButton.mesh();
    numVertices = currentMesh->numVertices();
    numFaces = currentMesh->numFaces();
    
    for (int i = 0; i < numVertices; i++) {
        Vertex vertex = currentMesh->getVertex(i);
        mesh->addVertex(Vertex(vertex.x() + length / 2.0L - marginWidth / 2.0L, vertex.y() + height / 2.0L + sideButtonsHeight / 2.0L, vertex.z()));
    }
    
    for (int i = 0; i < numFaces; i++) {
        Face face = currentMesh->getFace(i);
        face.v1 += verticesOffset;
        face.v2 += verticesOffset;
        face.v3 += verticesOffset;
        mesh->addFace(face);
    }
    
    verticesOffset += numVertices;
    
    Model centerButton = ModelsFactory::cylinder(sideButtonsRadius, sideButtonsHeight / 2.0L, 12);
    
    currentMesh = centerButton.mesh();
    numVertices = currentMesh->numVertices();
    numFaces = currentMesh->numFaces();
    
    for (int i = 0; i < numVertices; i++) {
        Vertex vertex = currentMesh->getVertex(i);
        mesh->addVertex(Vertex(vertex.x(), vertex.y() + height / 2.0L + sideButtonsHeight / 4.0L, vertex.z()));
    }
    
    for (int i = 0; i < numFaces; i++) {
        Face face = currentMesh->getFace(i);
        face.v1 += verticesOffset;
        face.v2 += verticesOffset;
        face.v3 += verticesOffset;
        mesh->addFace(face);
    }
    
    verticesOffset += numVertices;
    
    Model shutterButton = ModelsFactory::cylinder(shutterButtonRadius, shutterButtonHeight, 12);
    
    currentMesh = shutterButton.mesh();
    numVertices = currentMesh->numVertices();
    numFaces = currentMesh->numFaces();
    
    for (int i = 0; i < numVertices; i++) {
        Vertex vertex = currentMesh->getVertex(i);
        mesh->addVertex(Vertex(vertex.x() - length / 4.0L + marginWidth / 4.0L, vertex.y() + height / 2.0L + shutterButtonHeight / 2.0L, vertex.z() + width / 4.0L));
    }
    
    for (int i = 0; i < numFaces; i++) {
        Face face = currentMesh->getFace(i);
        face.v1 += verticesOffset;
        face.v2 += verticesOffset;
        face.v3 += verticesOffset;
        mesh->addFace(face);
    }
    
    verticesOffset += numVertices;
    
    return result;
}
