#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include "Model/Model.h"

class Scene
{
public:
    Scene();
    
private:
    std::vector<Model> m_objects;
};

#endif // SCENE_H
