#include "Viewport.h"

Viewport::Viewport(QWidget *parent)
    : QWidget(parent)
{
    m_width = width();
    m_height = height();
    m_buffer = QImage(m_width, m_height, QImage::Format_ARGB32);
    clear();
}

void Viewport::setPixel(const int &x, const int &y, const ARGB &color)
{
    //int offset = 0;
    int h = m_height - y;
    
    if (x >= 0 && x < m_width && h >= 0 && h < m_height) {
        m_buffer.setPixelColor(x, h, QColor(RED(color), GREEN(color), BLUE(color)));
    }
    
//    for (int i = x - offset; i <= x + offset; i++) {
//        for (int j = y - offset; j <= y + offset; j++) {
//            if (i >= 0 && i < w && j >= 0 && j < h) {
//                m_buffer.setPixelColor(i, h - j, QColor(RED(color), GREEN(color), BLUE(color)));
//            }
//        }
//    }
}

int Viewport::getWidth() const
{
    return m_width;
}

int Viewport::getHeight() const
{
    return m_height;
}

void Viewport::setSize(const int &width, const int &height)
{
    resize(width, height);
    
    m_buffer = QImage(width, height, QImage::Format_ARGB32);
    m_width = width;
    m_height = height;
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
