#ifndef CAMERA_H
#define CAMERA_H

#include "dehaxgl_global.h"
#include <cmath>
#include "Math/Vec3f.h"
#include "Math/Vec4f.h"
#include "Math/Matrix.h"
#include "Utils/Utils.h"

class DEHAXGLSHARED_EXPORT Camera
{
public:
    enum ProjectionType { Parallel, Perspective };
    
    explicit Camera();
    explicit Camera(const Vec3f &position, const Vec3f &lookAt, const Vec3f &up, long double FOV = M_PI_2);
    
    void rotate(const long double &angleX, const long double &angleY, const long double &angleZ);
    void zoom(const long double &multiplier);
    void changeProjection();
    void move(const Vec3f &offset);
    void strafeRight(const long double &value);
    void strafeForward(const long double &value);
    void strafeUp(const long double &value);
    
    int width() const;
    void setWidth(const int &width);
    int height() const;
    void setHeight(const int &height);
    int getZoom() const;
    void setZoom(const int &zoom);
    ProjectionType projection() const;
    void setProjection(const ProjectionType &projection);
    Vec3f position() const;
    void setPosition(const Vec3f &position);
    Vec3f lookAt() const;
    void setLookAt(const Vec3f &lookAt);
    Vec3f up() const;
    void setUp(const Vec3f &up);
    long double FOV() const;
    void setFOV(const long double &FOV);
    long double nearZ();
    void setNearZ(const long double &nearZ);
    long double farZ();
    void setFarZ(const long double &farZ);
    
    Matrix viewMatrix() const;
    Matrix projectionMatrix() const;
    
private:
    const ProjectionType DEFAULT_PROJECTION = Perspective;
    const Vec3f DEFAULT_POSITION = Vec3f(0.0L, 0.0L, -100.0L);
    const Vec3f DEFAULT_LOOK_AT = Vec3f(0.0L, 0.0L, 0.0L);
    const Vec3f DEFAULT_UP = Vec3f(0.0L, 1.0L, 0.0L);
    const long double DEFAULT_FOV = M_PI_2;
    const int DEFAULT_PARALLEL_ZOOM = 500;
    const long double DEFAULT_NEAR_Z = 1.0L;
    const long double DEFAULT_FAR_Z = 500.0L;
    
    int m_width;
    int m_height;
    int m_zoom;
    
    ProjectionType m_projection;
    Vec3f m_position;
    Vec3f m_lookAt;
    Vec3f m_up;
    long double m_fov;
    long double m_nearPlaneZ;
    long double m_farPlaneZ;
    
    long double m_theta;
    long double m_phi;
};

#endif // CAMERA_H
