#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QWheelEvent>
#include <QListWidgetItem>
#include <QFlags>
#include <QMessageBox>
#include <QFileDialog>
#include <QColorDialog>
#include <chrono>
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
    
private:
    void updateViewport();
    void updateObjectsList();
    void updateObjectInfo(int index);
    void updateCameraProperties();
    void modifyObject(int index, Qt::KeyboardModifiers modifiers, Vec3f transform, Vec3f rotation, Vec3f scale);
    void deleteObject(const int &index);
    void createCamera();
    void setUiObjectColor(const QColor &color);
    QColor getUiObjectColor() const;
    
    Ui::MainWindow *ui;
    QLabel *m_cameraInfo;
    
    DehaxGL *m_dgl;
    DehaxGL::RenderModes m_renderModes;
    int m_lastSelectedObjectIndex;
    
private slots:
    void viewportCameraUpdated();
    void viewportSizeChanged(QSize newSize);
    void objectSelected(QListWidgetItem *current, QListWidgetItem *previous);
    void on_aboutAction_triggered(bool checked);
    void on_aboutQt_triggered(bool checked);
    void on_cameraPositionX_valueChanged(double x);
    void on_cameraPositionY_valueChanged(double y);
    void on_cameraPositionZ_valueChanged(double z);
    void on_cameraLookAtX_valueChanged(double x);
    void on_cameraLookAtY_valueChanged(double y);
    void on_cameraLookAtZ_valueChanged(double z);
    void on_objectPositionX_valueChanged(double x);
    void on_objectPositionY_valueChanged(double y);
    void on_objectPositionZ_valueChanged(double z);
    void on_objectRotationX_valueChanged(double x);
    void on_objectRotationY_valueChanged(double y);
    void on_objectRotationZ_valueChanged(double z);
    void on_objectScaleX_valueChanged(double x);
    void on_objectScaleY_valueChanged(double y);
    void on_objectScaleZ_valueChanged(double z);
    void on_createModelButton_clicked();
    void on_fov_valueChanged(double fov);
    void on_viewDistance_valueChanged(double d);
    void on_editModelButton_clicked();
    void on_nearZ_valueChanged(double nearZ);
    void on_farZ_valueChanged(double farZ);
    void on_openSceneAction_triggered();
    void on_saveSceneAction_triggered();
    void on_turnOnParallelAction_toggled(bool isOn);
    void on_exitAction_triggered();
    void on_importAction_triggered();
    void on_pickColorButton_clicked();
};

#endif // MAINWINDOW_H
