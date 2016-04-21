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
    
    virtual void setPixel(int x, int y, ARGB color);
    
signals:
    
public slots:
    
protected:
    virtual void paintEvent(QPaintEvent *event);
    virtual void resizeEvent(QResizeEvent *event);
    
private:
    QImage m_buffer;
};

#endif // VIEWPORT_H
