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
    
    virtual void setPixel(const int &x, const int &y, const ARGB &color) final;
    //virtual void setLine(int x0, int y0, int x1, int y1, ARGB color);
    virtual void setSize(const int &width, const int &height) final;
    virtual void clear() final;
    
    virtual int getWidth() const;
    virtual int getHeight() const;
    
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
};

#endif // VIEWPORT_H
