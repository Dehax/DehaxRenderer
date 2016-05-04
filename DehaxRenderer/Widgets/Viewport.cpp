#include "Viewport.h"

Viewport::Viewport(QWidget *parent)
    : QWidget(parent)
{
    int w = width();
    int h = height();
    m_buffer = QImage(w, h, QImage::Format_ARGB32);
    clear();
}

void Viewport::setPixel(const int &x, const int &y, const ARGB &color)
{
    //int offset = 0;
    
    int w = m_buffer.width();
    int h = m_buffer.height();
    
    if (x >= 0 && x < w && h - y >= 0 && h - y < h) {
        m_buffer.setPixelColor(x, h - y, QColor(RED(color), GREEN(color), BLUE(color)));
    }
    
//    for (int i = x - offset; i <= x + offset; i++) {
//        for (int j = y - offset; j <= y + offset; j++) {
//            if (i >= 0 && i < w && j >= 0 && j < h) {
//                m_buffer.setPixelColor(i, h - j, QColor(RED(color), GREEN(color), BLUE(color)));
//            }
//        }
//    }
}

//void Viewport::setLine(int x0, int y0, int x1, int y1, ARGB color)
//{
//    int w = m_buffer.width();
//    int h = m_buffer.height();
    
//    y0 = h + 1 - y0;
//    y1 = h + 1 - y1;
    
//    bool steep = false;
    
//    if (std::abs(x0-x1)<std::abs(y0-y1)) { // if the line is steep, we transpose the image
//        std::swap(x0, y0);
//        std::swap(x1, y1);
//        steep = true;
//    }
//    if (x0>x1) { // make it left-to-right
//        std::swap(x0, x1);
//        std::swap(y0, y1);
//    }
    
//    for (int x=x0; x<=x1; x++) {
//        float t = (x-x0)/(float)(x1-x0);
//        int y = y0*(1.-t) + y1*t;
        
//        if (steep) {
//            if (y >= 0 && y < w && x >= 0 && x < h) {
//                m_buffer.setPixelColor(y, x, QColor(0, 0, 0));
//            }
//        } else {
//            if (x >= 0 && x < w && y >= 0 && y < h) {
//                m_buffer.setPixelColor(x, y, QColor(0, 0, 0));
//            }
//        }
//    }
//}

int Viewport::getWidth() const
{
    return width();
}

int Viewport::getHeight() const
{
    return height();
}

void Viewport::setSize(const int &width, const int &height)
{
    resize(width, height);
    
    m_buffer = QImage(width, height, QImage::Format_ARGB32);
    clear();
}

void Viewport::clear()
{
    m_buffer.fill(BACKGROUND_COLOR);
}

void Viewport::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawImage(0, 0, m_buffer);
}

void Viewport::resizeEvent(QResizeEvent *event)
{
    emit sizeChanged(event->size());
}
