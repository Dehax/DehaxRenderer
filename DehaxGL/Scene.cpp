#include "Scene.h"

Scene::Scene()
{
    Model teapotModel = Model("teapot.obj");
    m_objects.push_back(teapotModel);
}
