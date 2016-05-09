#include "Camera.h"

Camera::Camera()
{
    m_position = DEFAULT_POSITION;
    m_lookAt = DEFAULT_LOOK_AT;
    m_up = DEFAULT_UP;
    m_fov = DEFAULT_FOV;
    m_projection = DEFAULT_PROJECTION;
    m_zoom = DEFAULT_PARALLEL_ZOOM;
    m_nearPlaneZ = DEFAULT_NEAR_Z;
    m_farPlaneZ = DEFAULT_FAR_Z;
    
    m_theta = M_PI_2;
    m_phi = 0.0L;
}

Camera::Camera(const Vec3f &position, const Vec3f &lookAt, const Vec3f &up, long double FOV)
{
    m_position = position;
    m_lookAt = lookAt;
    m_up = up;
    m_fov = FOV;
    m_projection = DEFAULT_PROJECTION;
    m_zoom = DEFAULT_PARALLEL_ZOOM;
    m_nearPlaneZ = DEFAULT_NEAR_Z;
    m_farPlaneZ = DEFAULT_FAR_Z;
    
    m_theta = M_PI_2;
    m_phi = 0.0L;
}

void Camera::rotate(const long double &angleX, const long double &angleY, const long double &angleZ)
{
    Vec3f oldPosition = m_position - m_lookAt;
    
    long double r = oldPosition.length();
    
    if (radianToDegree(m_theta) >= 5.0L && radianToDegree(m_theta) <= 175.0L) {
        m_theta += angleX;
    } else {
        if (radianToDegree(m_theta) < 5.0L) {
            m_theta = degreeToRadian(5.0L);
        } else {
            m_theta = degreeToRadian(175.0L);
        }
    }
    
    m_phi += angleY;
    
    Vec3f newPosition = Vec3f(r * std::sin(m_theta) * std::sin(m_phi), r * std::cos(m_theta), -r * std::sin(m_theta) * std::cos(m_phi));
    
    m_position = newPosition + m_lookAt;
}

void Camera::zoom(const long double &multiplier)
{
    if (std::abs(multiplier) < 0.000001L) {
        return;
    }
    
    long double zoom = std::pow(2.0L, multiplier);
    
    switch (m_projection) {
    case Parallel:
        m_zoom /= zoom;
        break;
    case Perspective:
        long double newFOV = m_fov - multiplier * degreeToRadian(5.0L);
        if (newFOV <= degreeToRadian(120.0L) && newFOV >= degreeToRadian(30.0L)) {
            m_fov = newFOV;
        }
        break;
    }
}

void Camera::changeProjection()
{
    if (m_projection == Perspective) {
        m_projection = Parallel;
    } else if (m_projection == Parallel) {
        m_projection = Perspective;
    }
}

void Camera::move(const Vec3f &offset)
{
    m_position += offset;
    m_lookAt += offset;
}

void Camera::strafeRight(const long double &value)
{
    Vec3f zAxis = Vec3f::normal(m_lookAt - m_position);
    Vec3f xAxis = Vec3f::normal(Vec3f::cross(zAxis, m_up));
    Vec3f delta = xAxis * value;
    
    m_position += delta;
    m_lookAt += delta;
}

void Camera::strafeForward(const long double &value)
{
    Vec3f zAxis = Vec3f::normal(m_lookAt - m_position);
    Vec3f delta = zAxis * value;
    
    m_position += delta;
    m_lookAt += delta;
}

void Camera::strafeUp(const long double &value)
{
    Vec3f zAxis = Vec3f::normal(m_lookAt - m_position);
    Vec3f xAxis = Vec3f::normal(Vec3f::cross(zAxis, m_up));
    Vec3f yAxis = Vec3f::cross(xAxis, zAxis);
    Vec3f delta = yAxis * value;
    
    m_position += delta;
    m_lookAt += delta;
}

int Camera::width() const
{
    return m_width;
}

void Camera::setWidth(const int &width)
{
    m_width = width;
}

int Camera::height() const
{
    return m_height;
}

void Camera::setHeight(const int &height)
{
    m_height = height;
}

int Camera::getZoom() const
{
    return m_zoom;
}

void Camera::setZoom(const int &zoom)
{
    m_zoom = zoom;
}

Camera::ProjectionType Camera::projection() const
{
    return m_projection;
}

void Camera::setProjection(const Camera::ProjectionType &projection)
{
    m_projection = projection;
}

Vec3f Camera::position() const
{
    return m_position;
}

void Camera::setPosition(const Vec3f &position)
{
    m_position = position;
}

Vec3f Camera::lookAt() const
{
    return m_lookAt;
}

void Camera::setLookAt(const Vec3f &lookAt)
{
    m_lookAt = lookAt;
}

Vec3f Camera::up() const
{
    return m_up;
}

void Camera::setUp(const Vec3f &up)
{
    m_up = up;
}

long double Camera::FOV() const
{
    return m_fov;
}

void Camera::setFOV(const long double &FOV)
{
    m_fov = FOV;
}

long double Camera::nearZ()
{
    return m_nearPlaneZ;
}

void Camera::setNearZ(const long double &nearZ)
{
    if (nearZ >= 1.0L && nearZ < m_farPlaneZ) {
        m_nearPlaneZ = nearZ;
    }
}

long double Camera::farZ()
{
    return m_farPlaneZ;
}

void Camera::setFarZ(const long double &farZ)
{
    if (farZ <= 1000.0L && farZ > m_nearPlaneZ) {
        m_farPlaneZ = farZ;
    }
}

Matrix Camera::viewMatrix() const
{
    Vec3f zAxis = Vec3f::normal(m_lookAt - m_position);
    Vec3f xAxis = Vec3f::normal(Vec3f::cross(zAxis, m_up));
    Vec3f yAxis = Vec3f::cross(xAxis, zAxis);
    
    Matrix viewMatrix;
    
    viewMatrix.set(0, 0, xAxis.x);
    viewMatrix.set(1, 0, xAxis.y);
    viewMatrix.set(2, 0, xAxis.z);
    viewMatrix.set(3, 0, -(xAxis * m_position));
    viewMatrix.set(0, 1, yAxis.x);
    viewMatrix.set(1, 1, yAxis.y);
    viewMatrix.set(2, 1, yAxis.z);
    viewMatrix.set(3, 1, -(yAxis * m_position));
    viewMatrix.set(0, 2, zAxis.x);
    viewMatrix.set(1, 2, zAxis.y);
    viewMatrix.set(2, 2, zAxis.z);
    viewMatrix.set(3, 2, -(zAxis * m_position));
    viewMatrix.set(3, 3, 1.0L);
    
    return viewMatrix;
}

Matrix Camera::projectionMatrix() const
{
    Matrix projection;
    
    long double h;
    long double v;
    long double zf = m_farPlaneZ;
    long double zn = m_nearPlaneZ;
    long double aspectRatio = m_width / (long double)m_height;
    long double yScale = 1.0L / std::tan(m_fov / 2.0L);
    long double xScale = yScale / aspectRatio;
    
    switch (m_projection)
    {
    case Perspective:
        projection.set(0, 0, xScale);
        projection.set(1, 1, yScale);
        projection.set(2, 2, zf / (zf - zn));
        projection.set(3, 2, -zn * zf / (zf - zn));
        projection.set(2, 3, 1.0L);
//        projection[0][0] = 1.0L;
//        projection[1][1] = 1.0L;
//        projection[2][2] = 1.0L;
//        projection[2][3] = 1 / (m_width / 2 * std::tan(m_fov / 2.0L));
        break;
    case Parallel:
        if (m_width > m_height) {
            h = 0.5L * m_zoom;
            v = m_height * h / m_width;
        } else {
            v = 0.5L * m_zoom;
            h = m_width * v / m_height;
        }
        
        projection.set(0, 0, 2.0L / h);
        projection.set(1, 1, 2.0L / v);
        projection.set(2, 2, 1.0L / (zf - zn));
        projection.set(3, 2, -zn / (zf - zn));
        projection.set(3, 3, 1.0L);
        break;
    }
    
    return projection;
}
