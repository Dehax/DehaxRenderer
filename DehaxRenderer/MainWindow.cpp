#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), m_renderModes(DehaxGL::Both), m_lastSelectedObjectIndex(-1), m_isFreeCameraMode(false)
{
    ui->setupUi(this);
    connect(ui->viewport, SIGNAL(sizeChanged(QSize)), SLOT(viewportSizeChanged(QSize)));
    connect(ui->objectsListWidget, SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)), SLOT(objectSelected(QListWidgetItem*,QListWidgetItem*)));
    
//    ui->objectsListWidget->installEventFilter(this);
    
    m_dgl = new DehaxGL(ui->viewport);
    
    Model teapotModel = Model("teapot", "../../models/teapot.obj");
    Model boxModel = Model("box", "../../models/box.obj");
    Model planeModel = Model("plane", "../../models/plane.obj");
    Model suzanneModel = Model("suzanne", "../../models/suzanne.obj");
    suzanneModel.setScale(Vec3f(100.0L));
    Model generatedBox = ModelsFactory::box(1.0L, 1.0L, 1.5L);
    Model generatedCylinder = ModelsFactory::cylinder(1.0L, 2.0L, 12);
    Model camera = ModelsFactory::camera();
    
    m_dgl->scene().addModel(camera);
    
    //m_dgl->scene().generateCamera();
    
    //m_dgl->scene().addModel(teapotModel);
    //m_dgl->scene().addModel(boxModel);
    //m_dgl->scene().addModel(suzanneModel);
    //m_dgl->scene().addModel(generatedBox);
    //m_dgl->scene().addModel(generatedCylinder);
    //m_dgl->scene().addModel(planeModel);
    //m_dgl->camera().setPosition(Vec3f(10.0L, 0.0L, 0.0L));
    
    updateObjectsList();
    
    //ui->viewport->setFocus();
}

MainWindow::~MainWindow()
{
    delete ui;
    
    if (m_dgl != nullptr) {
        delete m_dgl;
        m_dgl = nullptr;
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    int key = event->key();
    Qt::KeyboardModifiers modifiers = event->modifiers();
    Vec3f oldPosition;
    
    switch (key) {
    case Qt::Key_Right:
        m_dgl->camera().rotate(0.0L, degreeToRadian(1.0L), 0.0L);
        break;
    case Qt::Key_Left:
        m_dgl->camera().rotate(0.0L, degreeToRadian(-1.0L), 0.0L);
        break;
    case Qt::Key_Up:
        m_dgl->camera().rotate(degreeToRadian(-1.0L), 0.0L, 0.0L);
        break;
    case Qt::Key_Down:
        m_dgl->camera().rotate(degreeToRadian(1.0L), 0.0L, 0.0L);
        break;
    case Qt::Key_P:
        m_dgl->camera().changeProjection();
        break;
    case Qt::Key_W:
        modifyObject(m_lastSelectedObjectIndex, modifiers, Vec3f(0.0L, 1.0L, 0.0L), Vec3f(-degreeToRadian(1.0L), 0.0L, 0.0L), Vec3f(1.0L, 2.0L, 1.0L));
        break;
    case Qt::Key_S:
        modifyObject(m_lastSelectedObjectIndex, modifiers, Vec3f(0.0L, -1.0L, 0.0L), Vec3f(degreeToRadian(1.0L), 0.0L, 0.0L), Vec3f(1.0L, 0.5L, 1.0L));
        break;
    case Qt::Key_D:
        modifyObject(m_lastSelectedObjectIndex, modifiers, Vec3f(1.0L, 0.0L, 0.0L), Vec3f(0.0L, degreeToRadian(1.0L), 0.0L), Vec3f(2.0L, 1.0L, 1.0L));
        break;
    case Qt::Key_A:
        modifyObject(m_lastSelectedObjectIndex, modifiers, Vec3f(-1.0L, 0.0L, 0.0L), Vec3f(0.0L, -degreeToRadian(1.0L), 0.0L), Vec3f(0.5L, 1.0L, 1.0L));
        break;
    case Qt::Key_E:
        modifyObject(m_lastSelectedObjectIndex, modifiers, Vec3f(0.0L, 0.0L, 1.0L), Vec3f(0.0L, 0.0L, degreeToRadian(1.0L)), Vec3f(1.0L, 1.0L, 2.0L));
        break;
    case Qt::Key_Q:
        modifyObject(m_lastSelectedObjectIndex, modifiers, Vec3f(0.0L, 0.0L, -1.0L), Vec3f(0.0L, 0.0L, -degreeToRadian(1.0L)), Vec3f(1.0L, 1.0L, 0.5L));
        break;
    case Qt::Key_F3:
        m_renderModes ^= DehaxGL::Solid;
        break;
    case Qt::Key_F4:
        m_renderModes ^= DehaxGL::Wireframe;
        break;
    case Qt::Key_F:
        m_isFreeCameraMode = !m_isFreeCameraMode;
        break;
    case Qt::Key_I:
        //m_dgl->camera().move(Vec3f(0.0L, 1.0L, 0.0L));
        m_dgl->camera().strafeUp(1.0L);
        break;
    case Qt::Key_K:
        //m_dgl->camera().move(Vec3f(0.0L, -1.0L, 0.0L));
        m_dgl->camera().strafeUp(-1.0L);
        break;
    case Qt::Key_J:
        //m_dgl->camera().move(Vec3f(-1.0L, 0.0L, 0.0L));
        m_dgl->camera().strafeRight(-1.0L);
        break;
    case Qt::Key_L:
        //m_dgl->camera().move(Vec3f(1.0L, 0.0L, 0.0L));
        m_dgl->camera().strafeRight(1.0L);
        break;
    case Qt::Key_U:
        //m_dgl->camera().move(Vec3f(0.0L, 0.0L, -1.0L));
        m_dgl->camera().strafeForward(-1.0L);
        break;
    case Qt::Key_O:
        //m_dgl->camera().move(Vec3f(0.0L, 0.0L, 1.0L));
        m_dgl->camera().strafeForward(1.0L);
        break;
    }
    
    updateViewport();
    updateObjectsList();
}

void MainWindow::wheelEvent(QWheelEvent *event)
{
    QPoint angleDelta = event->angleDelta();
    long double zoomDelta = angleDelta.y() / 112.0L;
    
    m_dgl->camera().zoom(zoomDelta);
    updateViewport();
}

//bool MainWindow::eventFilter(QObject *obj, QEvent *event)
//{
//    if (obj != this && event->type() == QEvent::KeyPress) {
////        return QMainWindow::eventFilter(obj, event);
//        keyPressEvent(static_cast<QKeyEvent *>(event));
        
//        return true;
//    }
    
//    return QMainWindow::eventFilter(obj, event);
//}

void MainWindow::updateViewport()
{
    // WARNING: Перенести обновление позиции камеры в UI.
    ui->cameraPositionValueLabel->setText(m_dgl->camera().position());
    
    m_dgl->render(m_renderModes);
    ui->viewport->update();
}

void MainWindow::updateObjectsList()
{
    ui->objectsListWidget->clear();
    Scene &scene = m_dgl->scene();
    int numObjects = scene.numObjects();
    for (int i = 0; i < numObjects; i++) {
        Model &model = scene[i];
        QString objectName = model.name() + " (" + model.position() + ")";
        QListWidgetItem *objectItem = new QListWidgetItem(objectName);
        ui->objectsListWidget->addItem(objectItem);
    }
}

void MainWindow::modifyObject(int index, Qt::KeyboardModifiers modifiers, Vec3f transform, Vec3f rotation, Vec3f scale)
{
    if (index < 0) {
        return;
    }
    
    if (modifiers == Qt::NoModifier) {
        m_dgl->scene().moveObject(index, transform);
    } else if (modifiers.testFlag(Qt::ShiftModifier)) {
        m_dgl->scene().rotateObject(index, rotation);
    } else if (modifiers.testFlag(Qt::ControlModifier)) {
        m_dgl->scene().scaleObject(index, scale);
    }
}

void MainWindow::viewportSizeChanged(QSize newSize)
{
    m_dgl->setViewportSize(newSize.width(), newSize.height());
    updateViewport();
}

void MainWindow::objectSelected(QListWidgetItem *current, QListWidgetItem *previous)
{
    int index = ui->objectsListWidget->currentRow();
    
    if (index < 0 && ui->objectsListWidget->count() > 0) {
        return;
    }
    
    m_lastSelectedObjectIndex = index;
}

void MainWindow::on_aboutAction_triggered(bool checked)
{
    QMessageBox::about(this, "DehaxRenderer", "Визуализатор DehaxRenderer.\nРазработал студент ИПО-13а, Кубашевский Денис (aka Dehax) © ДонНТУ 2016");
}

void MainWindow::on_aboutQt_triggered(bool checked)
{
    QMessageBox::aboutQt(this, "DehaxRenderer");
}
