#ifndef MODEL_H
#define MODEL_H

#include <QString>
#include <QStringList>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include "Mesh.h"
#include "Math/Vec3f.h"
#include "Math/Matrix.h"
#include "Utils/Utils.h"

class Model
{
public:
    explicit Model(Mesh &mesh, ARGB color = RGBA(0, 0, 0, 255));
    explicit Model(QString filePath);
    
    Vec3f position() const;
    void setPosition(Vec3f position);
    Vec3f rotation() const;
    void setRotation(Vec3f rotation);
    Vec3f scale() const;
    void setScale(Vec3f scale);
    
    
    Matrix worldMatrix();
    QString name() const;
    void setName(QString &name);
    
private:
    void parseObjFile(QString filePath);
    
    Mesh m_mesh;
    ARGB m_color;
    
    // World
    Vec3f m_position;
    Vec3f m_rotation;
    Vec3f m_scale;
    Vec3f m_pivot;
    
    Matrix m_transformMatrix;
    Matrix m_rotateMatrix;
    Matrix m_scaleMatrix;
    Matrix m_pivotMatrix;
    Matrix m_pivotInverseMatrix;
    
    QString m_name;
};

#endif // MODEL_H
