#ifndef MODELSFACTORY_H
#define MODELSFACTORY_H

#include "dehaxgl_global.h"
#include <QString>
#include "Mesh.h"
#include "Model.h"
#include "../Utils/Utils.h"

class DEHAXGLSHARED_EXPORT ModelsFactory
{
public:
    static Model box(long double width = 1.0L, long double length = 1.0L, long double height = 1.0L);
    static Model cylinder(long double radius = 1.0L, long double height = 1.0L, int sides = 12);
    static Model lensMount(long double width, long double frontLength, long double backLength, long double height);
//    static Model camera(long double width, long double length, long double height, long double radius, long double lensWidth, long double lensMountLength, long double lensMountWidth, long double marginWidth, long double sideButtonsHeight, long double shutterButtonHeight, long double sideButtonsRadius, long double shutterButtonRadius);
};

#endif // MODELSFACTORY_H
