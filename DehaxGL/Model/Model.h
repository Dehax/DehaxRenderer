#ifndef MODEL_H
#define MODEL_H

#include "dehaxgl_global.h"
#include <QString>
#include <QStringList>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include "Mesh.h"
//#include "../Math/Vec3f.h"
#include "../Math/Matrix.h"
#include "../Utils/Utils.h"

class DEHAXGLSHARED_EXPORT Model
{
public:
    Model(const Model &model);
    explicit Model(const QString &name, Mesh *mesh, ARGB color = RGBA(0, 0, 0, 255));
    explicit Model(const QString &name, const QString &filePath);
    ~Model();
    
    Vec3f position() const;
    void setPosition(Vec3f position);
    Vec3f rotation() const;
    void setRotation(Vec3f rotation);
    Vec3f scale() const;
    void setScale(Vec3f scale);
    Vec3f pivot() const;
    void setPivot(Vec3f pivot);
    Mesh *mesh();
    
    Matrix worldMatrix();
    QString name() const;
    void setName(QString &name);
    ARGB color() const;
    void setColor(ARGB color);
    
private:
    void parseObjFile(const QString &filePath);
    
    Mesh *m_mesh;
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
