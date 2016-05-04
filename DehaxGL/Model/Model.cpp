#include "Model.h"

Model::Model(const Model &model)
{
    m_mesh = new Mesh(*model.m_mesh);
    m_color = model.m_color;
    
    m_position = model.m_position;
    m_rotation = model.m_rotation;
    m_scale = model.m_scale;
    m_pivot = model.m_pivot;
    
    m_transformMatrix = model.m_transformMatrix;
    m_rotateMatrix = model.m_rotateMatrix;
    m_scaleMatrix = model.m_scaleMatrix;
    m_pivotMatrix = model.m_pivotMatrix;
    m_pivotInverseMatrix = model.m_pivotInverseMatrix;
    
    m_name = model.m_name;
}

Model::Model(const QString &name, Mesh *mesh, ARGB color)
    : m_mesh(mesh), m_color(color), m_name(name)
{
    m_position = Vec3f(0.0L, 0.0L, 0.0L);
    m_rotation = Vec3f(0.0L, 0.0L, 0.0L);
    m_scale = Vec3f(1.0L, 1.0L, 1.0L);
    m_pivot = Vec3f(0.0L, 0.0L, 0.0L);
    
    m_pivotMatrix = Matrix(4, 4, true);
    m_pivotInverseMatrix = Matrix(4, 4, true);
    m_transformMatrix = Matrix(4, 4, true);
    m_rotateMatrix = Matrix(4, 4, true);
    m_scaleMatrix = Matrix(4, 4, true);
}

Model::Model(const QString &name, const QString &filePath)
    : m_mesh(new Mesh()), m_name(name)
{
    m_position = Vec3f(0.0L, 0.0L, 0.0L);
    m_rotation = Vec3f(0.0L, 0.0L, 0.0L);
    m_scale = Vec3f(1.0L, 1.0L, 1.0L);
    m_pivot = Vec3f(0.0L, 0.0L, 0.0L);
    
    m_pivotMatrix = Matrix(4, 4, true);
    m_pivotInverseMatrix = Matrix(4, 4, true);
    m_transformMatrix = Matrix(4, 4, true);
    m_rotateMatrix = Matrix(4, 4, true);
    m_scaleMatrix = Matrix(4, 4, true);
    
    parseObjFile(filePath);
    
    m_color = RGBA((int)(std::rand() % 255), (int)(std::rand() % 255), (int)(std::rand() % 255), 255);
}

Model::~Model()
{
    if (m_mesh != nullptr) {
        delete m_mesh;
        m_mesh = nullptr;
    }
}

Vec3f Model::position() const
{
    return m_position;
}

void Model::setPosition(Vec3f position)
{
    m_position = position;
    
    m_transformMatrix = Matrix::transform(position);
}

Vec3f Model::rotation() const
{
    return m_rotation;
}

void Model::setRotation(Vec3f rotation)
{
    m_rotation = rotation;
    
    m_rotateMatrix = Matrix::rotation(rotation);
}

Vec3f Model::scale() const
{
    return m_scale;
}

void Model::setScale(Vec3f scale)
{
    m_scale = scale;
    
    m_scaleMatrix = Matrix::scale(scale);
}

Vec3f Model::pivot() const
{
    return m_pivot;
}

void Model::setPivot(Vec3f pivot)
{
    m_pivot = pivot;
}

Mesh *Model::mesh()
{
    return m_mesh;
}

Matrix Model::worldMatrix()
{
    Matrix P = m_pivotMatrix;
    Matrix R = m_rotateMatrix;
    Matrix S = m_scaleMatrix;
    Matrix PI = m_pivotInverseMatrix;
    Matrix T = m_transformMatrix;
    
    return P * R * S * PI * T;
}

QString Model::name() const
{
    return m_name;
}

ARGB Model::color() const
{
    return m_color;
}

void Model::setColor(ARGB color)
{
    m_color = color;
}

void Model::parseObjFile(const QString &filePath)
{
    QFile modelFile(filePath);
    
    if (modelFile.open(QIODevice::ReadOnly)) {
        QTextStream stream(&modelFile);
        QString line;
        
        while (!stream.atEnd()) {
            line = stream.readLine();
            
            if (line.startsWith("v ", Qt::CaseInsensitive)) {
                QStringList vertexData = line.split(' ', QString::SkipEmptyParts);
                long double x = vertexData[1].toDouble();
                long double y = vertexData[2].toDouble();
                long double z = vertexData[3].toDouble();
                
                Vertex vertex(x, y, z);
                m_mesh->addVertex(vertex);
            } else if (line.startsWith("f ", Qt::CaseInsensitive)) {
                QStringList faceData = line.split(' ', QString::SkipEmptyParts);
                int v1 = faceData[1].toInt() - 1;
                int v2 = faceData[2].toInt() - 1;
                int v3 = faceData[3].toInt() - 1;
                
                Face face(v1, v2, v3);
                m_mesh->addFace(face);
            }
        }
        
        if (stream.status() != QTextStream::Ok) {
            qDebug() << "Error reading " << filePath << "!";
        }
        
        modelFile.close();
    }
}
