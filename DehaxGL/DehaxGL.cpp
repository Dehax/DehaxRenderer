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
    Matrix vertexMatrix = calculateVertexMatrix(worldMatrix);
    
    Mesh *mesh = model.mesh();
    int numFaces = mesh->numFaces();
    //long double scale = mesh.maxLocalScale();
    
    //int width = m_viewport->getWidth();
    //int height = m_viewport->getHeight();
    //long double cameraZ = m_camera->position().z;
    //long double nearZ = m_camera->nearZ() + cameraZ;
    //long double farZ = m_camera->farZ() + cameraZ;
      
    Vec3f inverseLookDirection = m_camera->position() - m_camera->lookAt();
      
    Vec3f nearPosition = inverseLookDirection - Vec3f::normal(inverseLookDirection) * m_camera->nearZ();
    Vec3f farPosition = inverseLookDirection - Vec3f::normal(inverseLookDirection) * m_camera->farZ();
      
    //Vec4f nearV = Vec4f(nearPosition) * vertexMatrix;
    //Vec4f farV = Vec4f(farPosition) * vertexMatrix;
    
    const ARGB modelColor = model.color();
    
    for (int j = 0; j < numFaces; j++) {
        Face face = mesh->getFace(j);
        
        Vertex v1 = mesh->getVertex(face.v1);
        Vertex v2 = mesh->getVertex(face.v2);
        Vertex v3 = mesh->getVertex(face.v3);
        
        // Локальные координаты
        Vec3f local1 = v1.position();
        Vec3f local2 = v2.position();
        Vec3f local3 = v3.position();
        
        // Мировые координаты
        Vec4f world1 = Vec4f(local1) * worldMatrix;
        Vec4f world2 = Vec4f(local2) * worldMatrix;
        Vec4f world3 = Vec4f(local3) * worldMatrix;
        
        // Итоговые координаты (мировые + вида + проекции)
        Vec4f result1 = Vec4f(local1) * vertexMatrix;
        Vec4f result2 = Vec4f(local2) * vertexMatrix;
        Vec4f result3 = Vec4f(local3) * vertexMatrix;
        
        if (result1.w <= 0.0L || result2.w <= 0.0L || result3.w <= 0.0L) {
            continue;
        }
        
        // Однородные итоговые координаты
        Q_ASSERT(result1.w > 0.0L);
        Q_ASSERT(result2.w > 0.0L);
        Q_ASSERT(result3.w > 0.0L);
        Vec3f hc1 = Vec3f(result1.x / std::abs(result1.w), result1.y / std::abs(result1.w), result1.z / std::abs(result1.w));
        Vec3f hc2 = Vec3f(result2.x / std::abs(result2.w), result2.y / std::abs(result2.w), result2.z / std::abs(result2.w));
        Vec3f hc3 = Vec3f(result3.x / std::abs(result3.w), result3.y / std::abs(result3.w), result3.z / std::abs(result3.w));
        
        Vec3f n = Vec3f::cross(Vec3f(world3) - Vec3f(world1), Vec3f(world2) - Vec3f(world1));
        n = Vec3f::normal(n);
        Vec3f lightDirection = Vec3f(0.0L, 0.0L, -1.0L);
        lightDirection = m_camera->lookAt() - m_camera->position();
        lightDirection = Vec3f::normal(lightDirection);
        long double intensity = -(n * lightDirection);
        ARGB faceColor = RGBA((int)(RED(modelColor) * intensity), (int)(GREEN(modelColor) * intensity), (int)(BLUE(modelColor) * intensity), 255);
        
        if (intensity > 0.0L/* && result1.z >= nearV.z && result1.z <= farV.z && result2.z >= nearV.z && result2.z <= farV.z && result3.z >= nearV.z && result3.z <= farV.z*/) {
            drawFace(hc1, hc2, hc3, faceColor, m_zBuffer, renderMode);
        } else {
            continue;
        }
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
            
            int idx = P.x + P.y * width;
            
//            if (idx >= 0 && idx < width * height && zBuffer[idx] < P.z) {
//                zBuffer[idx] = P.z;
//                m_viewport->setPixel(P.x, P.y, edgeColor);
//            }
            m_viewport->setPixel(P.x, P.y, edgeColor);
            
            // end
            phi = 1.0L;
            P = Vec3f(A) + Vec3f(B - A) * phi;
            
            idx = P.x + P.y * width;
            
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
