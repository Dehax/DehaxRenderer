#include "Model.h"
#include "ModelsFactory.h"

Model::Model()
{
    m_mesh = nullptr;
}

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
    
    for (int i = 0; i < NUM_PARAMETERS; i++) {
        m_parameters[i] = model.m_parameters[i];
    }
}

Model::Model(const QString &name, Mesh *mesh, ARGB color)
    : m_mesh(mesh), m_color(color), m_name(name)
{
    m_position = Vec3f(0.0L, 0.0L, 0.0L);
    m_rotation = Vec3f(0.0L, 0.0L, 0.0L);
    m_scale = Vec3f(1.0L, 1.0L, 1.0L);
    m_pivot = Vec3f(0.0L, 0.0L, 0.0L);
    
    m_pivotMatrix = Matrix(/*4, 4, */true);
    m_pivotInverseMatrix = Matrix(/*4, 4, */true);
    m_transformMatrix = Matrix(/*4, 4, */true);
    m_rotateMatrix = Matrix(/*4, 4, */true);
    m_scaleMatrix = Matrix(/*4, 4, */true);
}

Model::Model(const QString &name, const QString &filePath)
    : m_mesh(new Mesh()), m_name(name)
{
    m_position = Vec3f(0.0L, 0.0L, 0.0L);
    m_rotation = Vec3f(0.0L, 0.0L, 0.0L);
    m_scale = Vec3f(1.0L, 1.0L, 1.0L);
    m_pivot = Vec3f(0.0L, 0.0L, 0.0L);
    
    m_pivotMatrix = Matrix(/*4, 4, */true);
    m_pivotInverseMatrix = Matrix(/*4, 4, */true);
    m_transformMatrix = Matrix(/*4, 4, */true);
    m_rotateMatrix = Matrix(/*4, 4, */true);
    m_scaleMatrix = Matrix(/*4, 4, */true);
    
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

QString Model::name() const
{
    return m_name;
}

void Model::setName(const QString &name)
{
    m_name = name;
}

//ARGB Model::color() const
//{
//    return m_color;
//}

void Model::setColor(ARGB color)
{
    m_color = color;
}

void Model::setParameters(long double width, long double length, long double height, long double radius, long double lensWidth, long double lensMountLength, long double lensMountWidth, long double marginWidth, long double sideButtonsHeight, long double shutterButtonHeight, long double sideButtonsRadius, long double shutterButtonRadius)
{
    m_parameters[0] = width;
    m_parameters[1] = length;
    m_parameters[2] = height;
    m_parameters[3] = radius;
    m_parameters[4] = lensWidth;
    m_parameters[5] = lensMountLength;
    m_parameters[6] = lensMountWidth;
    m_parameters[7] = marginWidth;
    m_parameters[8] = sideButtonsHeight;
    m_parameters[9] = shutterButtonHeight;
    m_parameters[10] = sideButtonsRadius;
    m_parameters[11] = shutterButtonRadius;
}

Model &Model::operator=(const Model &model)
{
    if (this != &model) {
        if (m_mesh != nullptr) {
            delete m_mesh;
        }
        
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
        
        for (int i = 0; i < NUM_PARAMETERS; i++) {
            m_parameters[i] = model.m_parameters[i];
        }
    }
    
    return *this;
}

void Model::parseObjFile(const QString &filePath)
{
    QFile modelFile(filePath);
    
    if (modelFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
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
                QStringList faceDataVertex = faceData[1].split('\\');
                int v1 = faceDataVertex[0].toInt() - 1;
                faceDataVertex = faceData[2].split('\\');
                int v2 = faceDataVertex[0].toInt() - 1;
                faceDataVertex = faceData[3].split('\\');
                int v3 = faceDataVertex[0].toInt() - 1;
                
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

QTextStream &operator<<(QTextStream &out, const Model &model)
{
    char blank = ' ';
    QString name = model.m_name;
    ARGB color = model.color();
    Vec3f pivot = model.m_pivot;
    Vec3f position = model.m_position;
    Vec3f rotation = model.m_rotation;
    Vec3f scale = model.m_scale;
    
    out << name << endl;
    out << color << endl;
    
    for (int i = 0; i < Model::NUM_PARAMETERS - 1; i++) {
        out << (double)model.m_parameters[i] << blank;
    }
    
    out << (double)model.m_parameters[Model::NUM_PARAMETERS - 1] << endl;
    
    out << pivot << endl;
    out << position << endl;
    out << rotation << endl;
    out << scale << endl;
    
    return out;
}

QTextStream &operator>>(QTextStream &in, Model &model)
{
    QString name;
    ARGB color;
    double parameters[Model::NUM_PARAMETERS];
    Vec3f pivot, position, rotation, scale;
    
    name = in.readLine();
    in >> color;
    
    for (int i = 0; i < Model::NUM_PARAMETERS; i++) {
        in >> parameters[i];
    }
    
    in >> pivot >> position >> rotation >> scale;
    
    model = ModelsFactory::camera(parameters[0], parameters[1], parameters[2], parameters[3], parameters[4], parameters[5], parameters[6], parameters[7], parameters[8], parameters[9], parameters[10], parameters[11]);
    model.setName(name);
    model.setColor(color);
    model.setPivot(pivot);
    model.setPosition(position);
    model.setRotation(rotation);
    model.setScale(scale);
    
    return in;
}
