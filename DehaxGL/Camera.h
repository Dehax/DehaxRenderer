#ifndef CAMERA_H
#define CAMERA_H

#include <cmath>
#include "Math/Vec3f.h"
#include "Math/Matrix.h"

class Camera
{
public:
    enum ProjectionType { Parallel, Perspective };
    
    explicit Camera();
    explicit Camera(Vec3f position, Vec3f lookAt, Vec3f up, long double FOV = M_PI_2);
    
    int width() const;
    void setWidth(int width);
    int height() const;
    void setHeight(int height);
    int zoom() const;
    void setZoom(int zoom);
    ProjectionType projection() const;
    void setProjection(ProjectionType projection);
    Vec3f position() const;
    void setPosition(Vec3f position);
    Vec3f lookAt() const;
    void setLookAt(Vec3f lookAt);
    Vec3f up() const;
    void setUp(Vec3f up);
    long double FOV() const;
    void setFOV(long double FOV);
    
    Matrix viewMatrix() const;
    Matrix projectionMatrix() const;
    
private:
    int m_width;
    int m_height;
    int m_zoom;
    
    ProjectionType m_projection;
    Vec3f m_position;
    Vec3f m_lookAt;
    Vec3f m_up;
    long double m_fov;
};

#endif // CAMERA_H
