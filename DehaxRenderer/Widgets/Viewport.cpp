#include "Viewport.h"

Viewport::Viewport(QWidget *parent)
    : QWidget(parent), m_mousePressed(false)
{
    m_width = width();
    m_height = height();
    m_buffer = QImage(m_width, m_height, QImage::Format_ARGB32);
    clear();
}

void Viewport::setSize(const int &width, const int &height)
{
    m_buffer = QImage(width, height, QImage::Format_ARGB32);
    m_width = width;
    m_height = height;
    clear();
}

void Viewport::setRenderer(DehaxGL *dehaxGL)
{
    m_dehaxGL = dehaxGL;
}

void Viewport::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawImage(0, 0, m_buffer);
    painter.drawText(QRect(0, 0, m_width, m_height), QString::number(m_fps));
}

void Viewport::resizeEvent(QResizeEvent *event)
{
    emit sizeChanged(event->size());
}

void Viewport::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        m_mousePressed = true;
        m_mousePreviousPosition = event->globalPos();
    }
}

void Viewport::mouseMoveEvent(QMouseEvent *event)
{
    if (!m_mousePressed) {
        return;
    }
    
    QPoint currentPosition = event->globalPos();
    
    if (currentPosition == m_mousePreviousPosition) {
        return;
    }
    
    int deltaX = currentPosition.x() - m_mousePreviousPosition.x();
    int deltaY = currentPosition.y() - m_mousePreviousPosition.y();
    
    m_dehaxGL->camera().rotate(degreeToRadian(-deltaY * MOUSE_CAMERA_MOVE_SCALE), degreeToRadian(-deltaX * MOUSE_CAMERA_MOVE_SCALE), 0.0L);
    
    emit cameraUpdated();
    
    m_mousePreviousPosition = currentPosition;
}

void Viewport::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        m_mousePressed = false;
    }
}
