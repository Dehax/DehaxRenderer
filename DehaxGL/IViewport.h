#ifndef IVIEWPORT_H
#define IVIEWPORT_H

#include "dehaxgl_global.h"
#include "Utils/Utils.h"

class DEHAXGLSHARED_EXPORT IViewport
{
public:
    /**
     * @brief setPixel Рисует пиксель определённого цвета.
     * @param x Координата пикселя по горизонтали.
     * @param y Координата пикселя по вертикали.
     */
    virtual void setPixel(const int &x, const int &y, const ARGB &color) = 0;
    //virtual void setLine(int x1, int y1, int x2, int y2, ARGB color) = 0;
    virtual void setSize(const int &width, const int &height) = 0;
    virtual void clear() = 0;
    
    virtual int getWidth() const = 0;
    virtual int getHeight() const = 0;
};

#endif // IVIEWPORT_H
