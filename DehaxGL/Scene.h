#ifndef SCENE_H
#define SCENE_H

#include "dehaxgl_global.h"
#include <vector>
#include <ctime>
#include "Model/Model.h"
#include "Model/ModelsFactory.h"

class DEHAXGLSHARED_EXPORT Scene
{
public:
    explicit Scene();
    explicit Scene(const QString &sceneFilePath);
    
    void moveObject(const int &index, const Vec3f &offset);
    void rotateObject(const int &index, const Vec3f &rotation);
    void scaleObject(const int &index, const Vec3f &scale);
    
    void generateCamera(long double width = 40.0L, long double length = 140.0L, long double height = 70.0L, long double radius = 25.0L, long double lensWidth = 30.0L, long double lensMountLength = 50.0L, long double lensMountWidth = 10.0L, long double marginWidth = 40.0L, long double sideButtonsHeight = 10.0L, long double shutterButtonHeight = 15.0L, long double sideButtonsRadius = 15.0L, long double shutterButtonRadius = 5.0L);
    
    void addModel(const Model &model);
    void removeModel(const int &index);
    
    void exportToFile(const QString &sceneFilePath);
    
    int numObjects() const;
    Model &operator [](const int &i);
    
private:
    const long double AXIS_SCALE = 100.0L;
    
    void loadSceneFile(const QString &sceneFilePath);
    void createAxisModels();
    
    std::vector<Model> m_objects;
};

#endif // SCENE_H
