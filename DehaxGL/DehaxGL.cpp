#include "DehaxGL.h"


DehaxGL::DehaxGL(IViewport *viewport)
    : m_viewport(viewport), m_zBuffer(nullptr), m_renderAxis(true)
{
    m_scene = new Scene();
    m_camera = new Camera();
    m_width = m_viewport->getWidth();
    m_height = m_viewport->getHeight();
    setViewportSize(m_width, m_height);
}

DehaxGL::~DehaxGL()
{
    if (m_scene != nullptr) {
        delete m_scene;
        m_scene = nullptr;
    }
    
    if (m_camera != nullptr) {
        delete m_camera;
        m_camera = nullptr;
    }
    
    if (m_zBuffer != nullptr) {
        delete[] m_zBuffer;
        m_zBuffer = nullptr;
    }
}

void DehaxGL::render(const RenderModes &renderMode)
{
    m_viewport->clear();
    
    int numObjects = m_scene->numObjects();
    
    for (int i = 0; i < m_width * m_height; i++) {
        m_zBuffer[i] = std::numeric_limits<int>::min();
    }
    
    for (int i = (m_renderAxis ? 0 : 3); i < numObjects; i++) {
        Model &model = (*m_scene)[i];
        
        renderModel(model, renderMode);
    }
}

void DehaxGL::loadScene(const QString &sceneFilePath)
{
    delete m_scene;
    
    m_scene = new Scene(sceneFilePath);
}

void DehaxGL::setViewportSize(const int &width, const int &height)
{
    m_camera->setWidth(width);
    m_camera->setHeight(height);
    m_viewport->setSize(width, height);
    m_width = width;
    m_height = height;
    
    if (m_zBuffer != nullptr) {
        delete[] m_zBuffer;
    }
    
    m_zBuffer = new int[width * height];
}

void DehaxGL::toggleAxisRender()
{
    m_renderAxis = !m_renderAxis;
}

Camera &DehaxGL::camera() const
{
    return *m_camera;
}

Scene &DehaxGL::scene() const
{
    return *m_scene;
}

void DehaxGL::renderModel(Model &model, const RenderModes &renderMode)
{
    Matrix worldMatrix = model.worldMatrix();
    Matrix viewMatrix = m_camera->viewMatrix();
    Matrix projectionMatrix = m_camera->projectionMatrix();
    
    Mesh *mesh = model.mesh();
    int numFaces = mesh->numFaces();
    const ARGB modelColor = model.color();
    const ARGB edgeColor = RGBA(255, 255, 255, 255);
    
    Camera::ProjectionType projection = m_camera->projection();
    long double viewDistance = m_camera->viewDistance();
    long double zoom = m_camera->getZoom();
    long double fov = m_camera->FOV();
    long double nearZ = m_camera->nearZ();
    long double farZ = m_camera->farZ();
    
    long double objectRadius = mesh->maxLocalScale();
    Vec3f objectPosition = model.position();
    Vec3f objectPositionView = Vec3f(Vec4f(objectPosition) * viewMatrix);
    long double objectNearZ = objectPositionView.z - objectRadius * model.scale().z;
    long double objectFarZ = objectPositionView.z + objectRadius * model.scale().z;
    long double objectLeftX = objectPositionView.x - objectRadius * model.scale().x;
    long double objectRightX = objectPositionView.x + objectRadius * model.scale().x;
    long double objectBottomY = objectPositionView.y - objectRadius * model.scale().y;
    long double objectTopY = objectPositionView.y + objectRadius * model.scale().y;
    
    long double clipX = 0.0L;
    long double clipY = 0.0L;
    
    if (objectNearZ <= nearZ || objectFarZ >= farZ) {
        return;
    }
    
    if (projection == Camera::Parallel) {
        if (m_width > m_height) {
            clipX = 0.5L * zoom;
        } else {
            clipX = m_width * 0.5L * zoom / m_height;
        }
    } else if (projection == Camera::Perspective) {
        clipX = 0.5L * m_width * objectPositionView.z / viewDistance;
        clipX = std::tan(fov / 2.0L) * (m_width / (long double)m_height) * objectPositionView.z;
    }
    
    if (objectLeftX < -clipX || objectRightX > clipX) {
        return;
    }
    
    if (m_camera->projection() == Camera::Parallel) {
        if (m_width > m_height) {
            clipY = m_height * 0.5L * zoom / m_width;
        } else {
            clipY = 0.5L * zoom;
        }
    } else if (m_camera->projection() == Camera::Perspective) {
        clipY = 0.5L * m_height * objectPositionView.z / viewDistance;
        clipY = std::tan(fov / 2.0L) * objectPositionView.z;
    }
    
    if (objectBottomY < -clipY || objectTopY > clipY) {
        return;
    }
    
    Face face;
    Vertex v1;
    Vertex v2;
    Vertex v3;
    Vec3f local1;
    Vec3f local2;
    Vec3f local3;
    Vec4f world1;
    Vec4f world2;
    Vec4f world3;
    Vec4f view1;
    Vec4f view2;
    Vec4f view3;
    Vec3f view1v3;
    Vec3f view2v3;
    Vec3f view3v3;
    Vec4f result1;
    Vec4f result2;
    Vec4f result3;
    Vec3f hc1;
    Vec3f hc2;
    Vec3f hc3;
    Vec3f n;
    Vec3f lightDirection;
    bool backfaceCulling;
    
    for (int j = 0; j < numFaces; j++) {
        face = mesh->getFace(j);
        
        v1 = mesh->getVertex(face.v1);
        v2 = mesh->getVertex(face.v2);
        v3 = mesh->getVertex(face.v3);
        
        // Локальные координаты
        local1 = v1.position();
        local2 = v2.position();
        local3 = v3.position();
        
        // Мировые координаты
        world1 = Vec4f(local1) * worldMatrix;
        world2 = Vec4f(local2) * worldMatrix;
        world3 = Vec4f(local3) * worldMatrix;
        
        // Нормаль грани
        n = Vec3f::cross(Vec3f(world3) - Vec3f(world1), Vec3f(world2) - Vec3f(world1));
        n = Vec3f::normal(n);
        // Вектор взгляда
        lightDirection = m_camera->lookAt() - m_camera->position();
        lightDirection = Vec3f::normal(lightDirection);
        long double intensity = -(n * lightDirection);
        
        if (intensity < 0.0L) {
            intensity = 0.0L;
        }
        
        ARGB faceColor = RGBA((int)(RED(modelColor) * intensity), (int)(GREEN(modelColor) * intensity), (int)(BLUE(modelColor) * intensity), 255);
        
        lightDirection = (projection == Camera::Parallel ? m_camera->lookAt() : Vec3f(world1)) - m_camera->position();
        lightDirection = Vec3f::normal(lightDirection);
        intensity = -(n * lightDirection);
        
        if (intensity <= 0.0L) {
            backfaceCulling = true;
        } else {
            backfaceCulling = false;
        }
        
        // Координаты вида
        view1 = world1 * viewMatrix;
        view2 = world2 * viewMatrix;
        view3 = world3 * viewMatrix;
        
        view1v3 = Vec3f(view1);
        view2v3 = Vec3f(view2);
        view3v3 = Vec3f(view3);
        
        // Координаты проекции
        result1 = view1 * projectionMatrix;
        result2 = view2 * projectionMatrix;
        result3 = view3 * projectionMatrix;
        
        // Однородные итоговые координаты
        hc1 = Vec3f(result1);
        hc2 = Vec3f(result2);
        hc3 = Vec3f(result3);
        
        drawFace(hc1, hc2, hc3, faceColor, edgeColor, m_zBuffer, renderMode, backfaceCulling);
    }
}

void DehaxGL::drawFace(Vec3f &v1, Vec3f &v2, Vec3f &v3, const ARGB &triangleColor, const ARGB &edgeColor, int *zBuffer, const RenderModes &renderMode, bool backfaceCulling)
{
    Vec3i s1 = calculateScreenCoordinates(v1);
    Vec3i s2 = calculateScreenCoordinates(v2);
    Vec3i s3 = calculateScreenCoordinates(v3);
    
    if (!backfaceCulling && renderMode.testFlag(DehaxGL::Solid)) {
        drawTriangle(s1, s2, s3, triangleColor, zBuffer);
    }
    
    if (renderMode.testFlag(DehaxGL::Wireframe)) {
        drawLine(s1, s2, edgeColor);
        drawLine(s2, s3, edgeColor);
        drawLine(s3, s1, edgeColor);
    }
}

void DehaxGL::drawTriangle(Vec3i &t0, Vec3i &t1, Vec3i &t2, const ARGB &color, int *zBuffer)
{
    if (t0.y == t1.y && t0.y == t2.y) {
        return;
    }
    
    if (t0.y > t1.y) {
        std::swap(t0, t1);
    }
    
    if (t0.y > t2.y) {
        std::swap(t0, t2);
    }
    
    if (t1.y > t2.y) {
        std::swap(t1, t2);
    }
    
    int total_height = t2.y - t0.y;
    
    for (int i = 0; i < total_height; i++) {
        bool second_half = i > t1.y - t0.y || t1.y == t0.y;
        int segment_height = second_half ? t2.y - t1.y : t1.y - t0.y;
        long double alpha = (long double)i / total_height;
        long double beta = (long double)(i - (second_half ? t1.y - t0.y : 0)) / segment_height;
        Vec3i A = Vec3f(t0) + Vec3f(t2 - t0) * alpha;
        Vec3i B = second_half ? (Vec3f)t1 + Vec3f(t2 - t1) * beta : (Vec3f)t0 + Vec3f(t1 - t0) * beta;
        
        if (A.x > B.x) {
            std::swap(A, B);
        }
        
        for (int j = A.x; j <= B.x; j++) {
            long double phi = B.x == A.x ? 1.0L : (long double)(j - A.x) / (long double)(B.x - A.x);
            Vec3i P = Vec3f(A) + Vec3f(B - A) * phi;
            
            int idx = P.x + P.y * m_width;
            
            if (idx >= 0 && idx < m_width * m_height && zBuffer[idx] < P.z) {
                zBuffer[idx] = P.z;
                m_viewport->setPixel(P.x, P.y, color);
            }
        }
    }
}

void DehaxGL::drawLine(Vec3i &from, Vec3i &to, const ARGB &color)
{
    int x0 = from.x;
    int y0 = from.y;
    int x1 = to.x;
    int y1 = to.y;
    
    bool steep = false;
    
    if (std::abs(x0 - x1) < std::abs(y0 - y1)) {
        std::swap(x0, y0);
        std::swap(x1, y1);
        steep = true;
    }
    
    if (x0 > x1) {
        std::swap(x0, x1);
        std::swap(y0, y1);
    }
    
    int dx = x1 - x0;
    int dy = y1 - y0;
    int derror2 = std::abs(dy) * 2;
    int error2 = 0;
    int y = y0;
    
    for (int x = x0; x <= x1; x++) {
        if (steep) {
            m_viewport->setPixel(y, x, color);
        } else {
            m_viewport->setPixel(x, y, color);
        }
        
        error2 += derror2;
    
        if (error2 > dx) {
            y += (y1 > y0 ? 1 : -1);
            error2 -= dx * 2;
        }
    }
}

Vec3i DehaxGL::calculateScreenCoordinates(const Vec3f &v)
{
    int depth = std::numeric_limits<int>::max() / 2;
    
    int x = (v.x + 1.0L) * m_width * 0.5L;
    int y = (v.y + 1.0L) * m_height * 0.5L;
    int z = (v.z + 1.0L) * -depth;
    
    return Vec3i(x, y, z);
}

Matrix DehaxGL::calculateVertexMatrix(const Matrix &world) const
{
    return world * m_camera->viewMatrix() * m_camera->projectionMatrix();
}
