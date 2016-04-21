#ifndef IVIEWPORT_H
#define IVIEWPORT_H

#include "Utils/Utils.h"

class IViewport
{
public:
    /**
     * @brief setPixel Рисует пиксель определённого цвета.
     * @param x Координата пикселя по горизонтали.
     * @param y Координата пикселя по вертикали.
     */
    virtual void setPixel(int x, int y, ARGB color) = 0;
};

#endif // IVIEWPORT_H
