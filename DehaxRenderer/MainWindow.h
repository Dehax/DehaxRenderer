#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QWheelEvent>
#include <QListWidgetItem>
#include <QFlags>
#include <QMessageBox>
#include "../DehaxGL/DehaxGL.h"
#include "../DehaxGL/Model/Model.h"
#include "../DehaxGL/Utils/Utils.h"
#include "../DehaxGL/Model/ModelsFactory.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    virtual ~MainWindow();
    
protected:
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void wheelEvent(QWheelEvent *event);
    
//    bool eventFilter(QObject *obj, QEvent *event);
    
private:
    void updateViewport();
    void updateObjectsList();
    void modifyObject(int index, Qt::KeyboardModifiers modifiers, Vec3f transform, Vec3f rotation, Vec3f scale);
    
    Ui::MainWindow *ui;
    
    DehaxGL *m_dgl;
    DehaxGL::RenderModes m_renderModes;
    int m_lastSelectedObjectIndex;
    
    bool m_isFreeCameraMode;
    
private slots:
    void viewportSizeChanged(QSize newSize);
    void objectSelected(QListWidgetItem *current, QListWidgetItem *previous);
    void on_aboutAction_triggered(bool checked);
    void on_aboutQt_triggered(bool checked);
};

#endif // MAINWINDOW_H
