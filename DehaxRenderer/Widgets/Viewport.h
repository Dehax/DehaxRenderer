#ifndef VIEWPORT_H
#define VIEWPORT_H

#include <QWidget>
#include <QPainter>
#include <QResizeEvent>
#include <QImage>
#include "../DehaxGL/IViewport.h"

class Viewport : public QWidget, public IViewport
{
    Q_OBJECT
public:
    explicit Viewport(QWidget *parent = 0);
    
    inline virtual void setPixel(const int &x, const int &y, const ARGB &color) final
    {
        int h = m_height - y;
        
        if (x >= 0 && x < m_width && h >= 0 && h < m_height) {
            m_buffer.setPixelColor(x, h, QColor(color));
        }
    }
    
    //virtual void setLine(int x0, int y0, int x1, int y1, ARGB color);
    virtual void setSize(const int &width, const int &height) final;
    
    inline virtual void clear() final
    {
        m_buffer.fill(BACKGROUND_COLOR);
    }
    
    inline virtual int getWidth() const
    {
        return m_width;
    }
    
    inline virtual int getHeight() const
    {
        return m_height;
    }
    
    inline void drawFps(int fps)
    {
        m_fps = fps;
    }
    
signals:
    void sizeChanged(QSize newSize);
    
public slots:
    
protected:
    virtual void paintEvent(QPaintEvent *event);
    virtual void resizeEvent(QResizeEvent *event);
    
private:
    const QColor BACKGROUND_COLOR = QColor(127, 127, 127);
    
    QImage m_buffer;
    int m_width;
    int m_height;
    int m_fps;
};

#endif // VIEWPORT_H
