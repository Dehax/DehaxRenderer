#ifndef MODELSFACTORY_H
#define MODELSFACTORY_H

#include "dehaxgl_global.h"
#include <stdexcept>
#include <QString>
#include "Mesh.h"
#include "Model.h"
#include "../Math/Vec4f.h"
#include "../Utils/Utils.h"

class DEHAXGLSHARED_EXPORT ModelsFactory
{
public:
    static Model box(long double width = 1.0L, long double length = 1.0L, long double height = 1.0L);
    static Model cylinder(long double radius = 1.0L, long double height = 1.0L, int sides = 12);
    static Model lensMount(long double width, long double frontLength, long double backLength, long double height);
    /**
     * @brief camera Генерирует модель фотоаппарата по заданным параметрам.
     * @param width Толщина фотоаппарата
     * @param length Длина фотоаппарата
     * @param height Высота фотоаппарата
     * @param radius Радиус объектива
     * @param lensWidth Ширина объектива
     * @param lensMountLength Длина крепления объектива
     * @param lensMountWidth Ширина крепления объектива
     * @param marginWidth Ширина свободной части
     * @param sideButtonsHeight Высота боковых кнопок
     * @param shutterButtonHeight Высота кнопки спуска затвора
     * @param sideButtonsRadius Радиус боковых кнопок
     * @param shutterButtonRadius Радиус кнопки спуска затвора
     * @return Возвращает сгенерированную модель
     */
    static Model camera(long double width = 40.0L, long double length = 140.0L, long double height = 70.0L, long double radius = 25.0L, long double lensWidth = 30.0L, long double lensMountLength = 50.0L, long double lensMountWidth = 10.0L, long double marginWidth = 40.0L, long double sideButtonsHeight = 10.0L, long double shutterButtonHeight = 15.0L, long double sideButtonsRadius = 15.0L, long double shutterButtonRadius = 5.0L);
};

#endif // MODELSFACTORY_H
