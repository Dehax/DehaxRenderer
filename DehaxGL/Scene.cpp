#include "Scene.h"

Scene::Scene()
{
    createAxisModels();
    
    std::srand(unsigned(std::time(0)));
}

Scene::Scene(const QString &sceneFilePath)
    : Scene()
{
    loadSceneFile(sceneFilePath);
}

void Scene::moveObject(const int &index, const Vec3f &offset)
{
    Vec3f oldPosition = m_objects[index].position();
    Vec3f newPosition = oldPosition + offset;
    m_objects[index].setPosition(newPosition);
}

void Scene::rotateObject(const int &index, const Vec3f &rotation)
{
    Vec3f oldRotation = m_objects[index].rotation();
    Vec3f newRotation = oldRotation + rotation;
    m_objects[index].setRotation(newRotation);
}

void Scene::scaleObject(const int &index, const Vec3f &scale)
{
    Vec3f oldScale = m_objects[index].scale();
    Vec3f newScale = Vec3f(oldScale.x * scale.x, oldScale.y * scale.y, oldScale.z * scale.z);
    m_objects[index].setScale(newScale);
}

void Scene::generateCamera(long double width, long double length, long double height, long double radius, long double lensWidth, long double lensMountLength, long double lensMountWidth, long double marginWidth, long double sideButtonsHeight, long double shutterButtonHeight, long double sideButtonsRadius, long double shutterButtonRadius)
{
    long double multiplier = 1.0L;
    width /= multiplier;
    length /= multiplier;
    height /= multiplier;
    radius /= multiplier;
    lensWidth /= multiplier;
    lensMountLength /= multiplier;
    lensMountWidth /= multiplier;
    marginWidth /= multiplier;
    sideButtonsHeight /= multiplier;
    shutterButtonHeight /= multiplier;
    sideButtonsRadius /= multiplier;
    shutterButtonRadius /= multiplier;
    
    Model base = ModelsFactory::box(width, length, height);
    Model lensMount = ModelsFactory::lensMount(lensMountWidth, lensMountLength, length - marginWidth * 2.0L, height);
    lensMount.setPosition(Vec3f(0.0L, 0.0L, -(width / 2.0L + lensMountWidth / 2.0L)));
    Model lens = ModelsFactory::cylinder(radius, lensWidth, 12);
    lens.setPosition(Vec3f(0.0L, 0.0L, -(width / 2.0L + lensMountWidth + lensWidth / 2.0L)));
    lens.setRotation(Vec3f(degreeToRadian(90.0L), 0.0L, 0.0L));
    Model rightSideButton = ModelsFactory::cylinder(sideButtonsRadius, sideButtonsHeight, 12);
    rightSideButton.setPosition(Vec3f(-length / 2.0L + marginWidth / 2.0L, height / 2.0L + sideButtonsHeight / 2.0L, 0.0L));
    Model leftSideButton = ModelsFactory::cylinder(sideButtonsRadius, sideButtonsHeight, 12);
    leftSideButton.setPosition(Vec3f(length / 2.0L - marginWidth / 2.0L, height / 2.0L + sideButtonsHeight / 2.0L, 0.0L));
    Model centerButton = ModelsFactory::cylinder(sideButtonsRadius, sideButtonsHeight / 2.0L, 12);
    centerButton.setPosition(Vec3f(0.0L, height / 2.0L + sideButtonsHeight / 4.0L, 0.0L));
    Model shutterButton = ModelsFactory::cylinder(shutterButtonRadius, shutterButtonHeight, 12);
    shutterButton.setPosition(Vec3f(-length / 4.0L + marginWidth / 4.0L, height / 2.0L + shutterButtonHeight / 2.0L, width / 4.0L));
    
    addModel(base);
    addModel(lensMount);
    addModel(lens);
    addModel(rightSideButton);
    addModel(leftSideButton);
    addModel(centerButton);
    addModel(shutterButton);
}

void Scene::addModel(const Model &model)
{
    m_objects.push_back(model);
}

void Scene::removeModel(const int &index)
{
    m_objects.erase(m_objects.begin() + index);
}

void Scene::exportToFile(const QString &sceneFilePath)
{
    QFile sceneFile(sceneFilePath);
    
    if (!sceneFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return;
    }
    
    QTextStream stream(&sceneFile);
    
    // Write to stream.
    int numberObjects = numObjects();
    
    stream << numberObjects - 3 << endl;
    
    for (int i = 3; i < numberObjects; i++) {
        stream << m_objects[i];
    }
    
    sceneFile.close();
}

int Scene::numObjects() const
{
    return m_objects.size();
}

Model &Scene::operator [](const int &i)
{
    return m_objects[i];
}

void Scene::loadSceneFile(const QString &sceneFilePath)
{
    QFile sceneFile(sceneFilePath);
    
    if (!sceneFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }
    
    QTextStream stream(&sceneFile);
    QString line = stream.readLine();
    
    int numberObjects = line.toInt();
    
    for (int i = 0; i < numberObjects; i++) {
        Model model;
        stream >> model;
        stream.readLine();
        
        addModel(model);
    }
    
    sceneFile.close();
}

void Scene::createAxisModels()
{
    Model axisX = ModelsFactory::box(0.01L * AXIS_SCALE, 1.0L * AXIS_SCALE, 0.01L * AXIS_SCALE);
    axisX.setPosition(Vec3f(0.5L * AXIS_SCALE, 0.0L, 0.0L));
    axisX.setColor(RGBA(255, 0, 0, 255));
    Model axisY = ModelsFactory::box(0.01L * AXIS_SCALE, 0.01L * AXIS_SCALE, 1.0L * AXIS_SCALE);
    axisY.setPosition(Vec3f(0.0L, 0.5L * AXIS_SCALE, 0.0L));
    axisY.setColor(RGBA(0, 255, 0, 255));
    Model axisZ = ModelsFactory::box(1.0L * AXIS_SCALE, 0.01L * AXIS_SCALE, 0.01L * AXIS_SCALE);
    axisZ.setPosition(Vec3f(0.0L, 0.0L, 0.5L * AXIS_SCALE));
    axisZ.setColor(RGBA(0, 0, 255, 255));
    
    addModel(axisX);
    addModel(axisY);
    addModel(axisZ);
}
