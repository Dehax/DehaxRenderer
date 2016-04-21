#include "Camera.h"

Camera::Camera()
{
    m_position = Vec3f(0.0L, 0.0L, -10.0L);
    m_lookAt = Vec3f(0.0L, 0.0L, 0.0L);
    m_up = Vec3f(0.0L, 1.0L, 0.0L);
    m_fov = M_PI_2;
}

Camera::Camera(Vec3f position, Vec3f lookAt, Vec3f up, long double FOV)
{
    m_position = position;
    m_lookAt = lookAt;
    m_up = up;
    m_fov = FOV;
}

int Camera::width() const
{
    return m_width;
}

void Camera::setWidth(int width)
{
    m_width = width;
}

int Camera::height() const
{
    return m_height;
}

void Camera::setHeight(int height)
{
    m_height = height;
}

int Camera::zoom() const
{
    return m_zoom;
}

void Camera::setZoom(int zoom)
{
    m_zoom = zoom;
}

Camera::ProjectionType Camera::projection() const
{
    return m_projection;
}

void Camera::setProjection(Camera::ProjectionType projection)
{
    m_projection = projection;
}

Vec3f Camera::position() const
{
    return m_position;
}

void Camera::setPosition(Vec3f position)
{
    m_position = position;
}

Vec3f Camera::lookAt() const
{
    return m_lookAt;
}

void Camera::setLookAt(Vec3f lookAt)
{
    m_lookAt = lookAt;
}

Vec3f Camera::up() const
{
    return m_up;
}

void Camera::setUp(Vec3f up)
{
    m_up = up;
}

long double Camera::FOV() const
{
    return m_fov;
}

void Camera::setFOV(long double FOV)
{
    m_fov = FOV;
}

Matrix Camera::viewMatrix() const
{
    Vec3f zAxis = Vec3f::normal(m_lookAt - m_position);
    Vec3f xAxis = Vec3f::normal(Vec3f::cross(zAxis, m_up));
    Vec3f yAxis = Vec3f::cross(xAxis, zAxis);
    
    Matrix viewMatrix = Matrix();
    
    viewMatrix[0][0] = xAxis.x;
    viewMatrix[1][0] = xAxis.y;
    viewMatrix[2][0] = xAxis.z;
    viewMatrix[3][0] = -(xAxis * m_position);
    viewMatrix[0][1] = yAxis.x;
    viewMatrix[1][1] = yAxis.y;
    viewMatrix[2][1] = yAxis.z;
    viewMatrix[3][1] = -(yAxis * m_position);
    viewMatrix[0][2] = zAxis.x;
    viewMatrix[1][2] = zAxis.y;
    viewMatrix[2][2] = zAxis.z;
    viewMatrix[3][2] = -(zAxis * m_position);
    viewMatrix[3][3] = 1.0L;
    
    return viewMatrix;
}

Matrix Camera::projectionMatrix() const
{
    Matrix projection = Matrix();
    
    long double h;
    long double v;
    long double zf = 100.0L;
    long double zn = 1.0L;
    long double aspectRatio = m_width / (long double)m_height;
    long double yScale = 1.0L / tanl(m_fov / 2.0L);
    long double xScale = yScale / aspectRatio;
    
    switch (m_projection)
    {
    case Perspective:
        projection[0][0] = xScale;
        projection[1][1] = yScale;
        projection[2][2] = zf / (zf - zn);
        projection[3][2] = -zn * zf / (zf - zn);
        projection[2][3] = 1.0L;
        break;
    case Parallel:
        if (m_width > m_height) {
            h = 0.5L * m_zoom;
            v = m_height * h / m_width;
        } else {
            v = 0.5L * m_zoom;
            h = m_width * v / m_height;
        }
        
        projection[0][0] = 2.0L / h;
        projection[1][1] = 2.0L / v;
        projection[2][2] = 1.0L / (zf - zn);
        projection[3][2] = -zn / (zf - zn);
        projection[3][3] = 1.0L;
        break;
    }
    
    return projection;
}
