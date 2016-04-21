#include "Viewport.h"

Viewport::Viewport(QWidget *parent)
    : QWidget(parent), m_buffer(width(), height(), QImage::Format_ARGB32)
{
    
}

void Viewport::setPixel(int x, int y, ARGB color)
{
    m_buffer.setPixelColor(x, y, QColor(color));
}

void Viewport::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPoint(0, 0);
    painter.drawPoint(width() - 1, height() - 1);
}

void Viewport::resizeEvent(QResizeEvent *event)
{
    const QSize &newSize = event->size();
    m_buffer = QImage(newSize, QImage::Format_ARGB32);
}
