#include "DehaxGL.h"


DehaxGL::DehaxGL(IViewport *viewport)
    : m_viewport(viewport)
{
    m_scene = new Scene();
    m_camera = new Camera();
    setViewportSize(m_viewport->getWidth(), m_viewport->getHeight());
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
    
    int width = m_viewport->getWidth();
    int height = m_viewport->getHeight();
    
    for (int i = 0; i < width * height; i++) {
        m_zBuffer[i] = std::numeric_limits<int>::min();
    }
    
    for (int i = 0; i < numObjects; i++) {
        Model &model = (*m_scene)[i];
        
        renderModel(model, renderMode);
    }
}

void DehaxGL::setViewportSize(const int &width, const int &height)
{
    m_camera->setWidth(width);
    m_camera->setHeight(height);
    m_viewport->setSize(width, height);
    
    if (m_zBuffer != nullptr) {
        delete[] m_zBuffer;
    }
    
    m_zBuffer = new int[width * height];
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
    
    long double nearZ = m_camera->nearZ();
    long double farZ = m_camera->farZ() + (m_camera->width() / 2) * std::tan(m_camera->FOV() / 2);
    
    const ARGB modelColor = model.color();
    
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
        
        lightDirection = (m_camera->projection() == Camera::Parallel ? m_camera->lookAt() : Vec3f(world1)) - m_camera->position();
        lightDirection = Vec3f::normal(lightDirection);
        intensity = -(n * lightDirection);
        // BUG: Нельзя делать проверку на Wireframe здесь, тогда отрисовываются backface.        
        if (intensity <= 0.0L && !renderMode.testFlag(Wireframe)) {
            continue;
        }
        
        // Координаты вида
        view1 = world1 * viewMatrix;
        view2 = world2 * viewMatrix;
        view3 = world3 * viewMatrix;
        
        view1v3 = Vec3f(view1);
        view2v3 = Vec3f(view2);
        view3v3 = Vec3f(view3);
        
        if (view1v3.z <= nearZ || view1v3.z >= farZ || view2v3.z <= nearZ || view2v3.z >= farZ || view3v3.z <= nearZ || view3v3.z >= farZ) {
            return;
        }
        
        // Координаты проекции
        result1 = view1 * projectionMatrix;
        result2 = view2 * projectionMatrix;
        result3 = view3 * projectionMatrix;
        
        // Однородные итоговые координаты
        hc1 = Vec3f(result1);
        hc2 = Vec3f(result2);
        hc3 = Vec3f(result3);
        
        drawFace(hc1, hc2, hc3, faceColor, m_zBuffer, renderMode);
    }
}

void DehaxGL::drawFace(Vec3f &v1, Vec3f &v2, Vec3f &v3, const ARGB &color, int *zBuffer, const RenderModes &renderMode)
{
    Vec3i s1 = calculateScreenCoordinates(v1);
    Vec3i s2 = calculateScreenCoordinates(v2);
    Vec3i s3 = calculateScreenCoordinates(v3);
    
    drawTriangle(s1, s2, s3, color, zBuffer, renderMode);
}

void DehaxGL::drawTriangle(Vec3i &t0, Vec3i &t1, Vec3i &t2, const ARGB &color, int *zBuffer, const RenderModes &renderMode)
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
    int width = m_viewport->getWidth();
    int height = m_viewport->getHeight();
    const ARGB edgeColor = RGBA(255, 255, 255, 255);
    
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
        
        if (renderMode.testFlag(Both) || renderMode.testFlag(Wireframe)) {
            // start
            long double phi = B.x == A.x ? 1.0L : 0.0L;
            Vec3i P = Vec3f(A) + Vec3f(B - A) * phi;
            
            //int idx = P.x + P.y * width;
            
//            if (idx >= 0 && idx < width * height && zBuffer[idx] < P.z) {
//                zBuffer[idx] = P.z;
//                m_viewport->setPixel(P.x, P.y, edgeColor);
//            }
            m_viewport->setPixel(P.x, P.y, edgeColor);
            
            // end
            phi = 1.0L;
            P = Vec3f(A) + Vec3f(B - A) * phi;
            
            //int idx = P.x + P.y * width;
            
//            if (idx >= 0 && idx < width * height && zBuffer[idx] < P.z) {
//                zBuffer[idx] = P.z;
//                m_viewport->setPixel(P.x, P.y, edgeColor);
//            }
            m_viewport->setPixel(P.x, P.y, edgeColor);
        }
        
        if (renderMode.testFlag(Both) || renderMode.testFlag(Solid)) {
            for (int j = A.x; j <= B.x; j++) {
                long double phi = B.x == A.x ? 1.0L : (long double)(j - A.x) / (long double)(B.x - A.x);
                Vec3i P = Vec3f(A) + Vec3f(B - A) * phi;
                
                int idx = P.x + P.y * width;
                
                if (idx >= 0 && idx < width * height && zBuffer[idx] < P.z) {
                    zBuffer[idx] = P.z;
                    m_viewport->setPixel(P.x, P.y, color);
                }
            }
        }
    }
}

Vec3i DehaxGL::calculateScreenCoordinates(Vec3f &v)
{
    int width = m_viewport->getWidth();
    int height = m_viewport->getHeight();
    int depth = std::numeric_limits<int>::max() / 2;//m_camera->farZ() - m_camera->nearZ();
    
    int x = (v.x + 1.0L) * width / 2.0L;
    int y = (v.y + 1.0L) * height / 2.0L;
    int z = (v.z + 1.0L) * -depth;
    
    return Vec3i(x, y, z);
}

Matrix DehaxGL::calculateVertexMatrix(Matrix &world) const
{
    return world * m_camera->viewMatrix() * m_camera->projectionMatrix();
}
