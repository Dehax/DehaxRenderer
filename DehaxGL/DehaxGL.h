#ifndef DEHAXGL_H
#define DEHAXGL_H

#include "dehaxgl_global.h"
#include "IViewport.h"
#include "Scene.h"
#include "Camera.h"
#include "Utils/Utils.h"
#include "Math/Vec3i.h"
#include "Math/Vec3f.h"
#include "Math/Vec4f.h"

class DEHAXGLSHARED_EXPORT DehaxGL
{
    
public:
    explicit DehaxGL(IViewport *viewport);
    ~DehaxGL();
    
    enum RenderMode { Wireframe = 0x1, Solid = 0x2, Both = Wireframe | Solid };
    Q_DECLARE_FLAGS(RenderModes, RenderMode)
    void render(const DehaxGL::RenderModes &renderMode);
    
    void setViewportSize(const int &width, const int &height);
    
    Camera &camera() const;
    Scene &scene() const;
    
private:
    void renderModel(Model &model, const DehaxGL::RenderModes &renderMode);
    void drawFace(Vec3f &v1, Vec3f &v2, Vec3f &v3, const ARGB &color, int *zBuffer, const DehaxGL::RenderModes &renderMode);
    void drawTriangle(Vec3i &t0, Vec3i &t1, Vec3i &t2, const ARGB &color, int *zBuffer, const DehaxGL::RenderModes &renderMode);
    //void drawLine(Vec3i from, Vec3i to, ARGB color, int *zBuffer);
    Vec3i calculateScreenCoordinates(Vec3f &v);
    Matrix calculateVertexMatrix(Matrix &world) const;
    
    IViewport *m_viewport;
    Scene *m_scene;
    Camera *m_camera;
    int *m_zBuffer;
    int m_width;
    int m_height;
};

Q_DECLARE_OPERATORS_FOR_FLAGS(DehaxGL::RenderModes)

#endif // DEHAXGL_H
