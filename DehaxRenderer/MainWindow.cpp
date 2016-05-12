#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), m_renderModes(DehaxGL::Both), m_lastSelectedObjectIndex(-1)
{
    ui->setupUi(this);
    m_cameraInfo = new QLabel("Hello");
    ui->statusBar->addPermanentWidget(m_cameraInfo);
    connect(ui->viewport, SIGNAL(sizeChanged(QSize)), SLOT(viewportSizeChanged(QSize)));
    connect(ui->viewport, SIGNAL(cameraUpdated()), SLOT(viewportCameraUpdated()));
    connect(ui->objectsListWidget, SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)), SLOT(objectSelected(QListWidgetItem*,QListWidgetItem*)));
//    ui->objectsListWidget->installEventFilter(this);
    
    m_dgl = new DehaxGL(ui->viewport);
    ui->viewport->setRenderer(m_dgl);
    
//    Model teapotModel = Model("teapot", "../../models/teapot.obj");
//    Model boxModel = Model("box", "../../models/box.obj");
//    boxModel.setScale(Vec3f(10.0L));
//    Model planeModel = Model("plane", "../../models/plane.obj");
//    Model suzanneModel = Model("suzanne", "../../models/suzanne.obj");
//    suzanneModel.setScale(Vec3f(10.0L));
//    Model generatedBox = ModelsFactory::box(1.0L, 1.0L, 1.5L);
//    Model generatedCylinder = ModelsFactory::cylinder(1.0L, 2.0L, 12);
//    Model camera = ModelsFactory::camera();
    
    //m_dgl->scene().addModel(camera);
    
    //m_dgl->scene().generateCamera();
    
    //m_dgl->scene().addModel(teapotModel);
    //m_dgl->scene().addModel(boxModel);
    //m_dgl->scene().addModel(suzanneModel);
    //m_dgl->scene().addModel(generatedBox);
    //m_dgl->scene().addModel(generatedCylinder);
    //m_dgl->scene().addModel(planeModel);
    //m_dgl->camera().setPosition(Vec3f(10.0L, 0.0L, 0.0L));
    
    updateCameraProperties();
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
    
    switch (key) {
    case Qt::Key_Right:
        m_dgl->camera().rotate(0.0L, degreeToRadian(1.0L), 0.0L);
        updateCameraProperties();
        break;
    case Qt::Key_Left:
        m_dgl->camera().rotate(0.0L, degreeToRadian(-1.0L), 0.0L);
        updateCameraProperties();
        break;
    case Qt::Key_Up:
        m_dgl->camera().rotate(degreeToRadian(-1.0L), 0.0L, 0.0L);
        updateCameraProperties();
        break;
    case Qt::Key_Down:
        m_dgl->camera().rotate(degreeToRadian(1.0L), 0.0L, 0.0L);
        updateCameraProperties();
        break;
//    case Qt::Key_P:
//        m_dgl->camera().changeProjection();
//        break;
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
        m_dgl->toggleAxisRender();
        break;
    case Qt::Key_I:
        //m_dgl->camera().move(Vec3f(0.0L, 1.0L, 0.0L));
        m_dgl->camera().strafeUp(1.0L);
        updateCameraProperties();
        break;
    case Qt::Key_K:
        //m_dgl->camera().move(Vec3f(0.0L, -1.0L, 0.0L));
        m_dgl->camera().strafeUp(-1.0L);
        updateCameraProperties();
        break;
    case Qt::Key_J:
        //m_dgl->camera().move(Vec3f(-1.0L, 0.0L, 0.0L));
        m_dgl->camera().strafeRight(-1.0L);
        updateCameraProperties();
        break;
    case Qt::Key_L:
        //m_dgl->camera().move(Vec3f(1.0L, 0.0L, 0.0L));
        m_dgl->camera().strafeRight(1.0L);
        updateCameraProperties();
        break;
    case Qt::Key_U:
        //m_dgl->camera().move(Vec3f(0.0L, 0.0L, -1.0L));
        m_dgl->camera().strafeForward(-1.0L);
        updateCameraProperties();
        break;
    case Qt::Key_O:
        //m_dgl->camera().move(Vec3f(0.0L, 0.0L, 1.0L));
        m_dgl->camera().strafeForward(1.0L);
        updateCameraProperties();
        break;
    case Qt::Key_Delete:
        deleteObject(m_lastSelectedObjectIndex);
        updateObjectsList();
        break;
    }
    
    updateViewport();
}

void MainWindow::wheelEvent(QWheelEvent *event)
{
    QPoint angleDelta = event->angleDelta();
    long double zoomDelta = angleDelta.y() / 112.0L;
    
    m_dgl->camera().zoom(zoomDelta);
    
    updateViewport();
    updateCameraProperties();
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
    // Начало измерения FPS
    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();
    
    // Вычисления
    m_dgl->render(m_renderModes);
    ui->viewport->update();
    
    // Конец измерения FPS
    end = std::chrono::system_clock::now();
    
    std::chrono::duration<long double> elapsed_seconds = end - start;
    
    long double fps = elapsed_seconds.count();
    
    if (fps != 0.0L) {
        ui->viewport->drawFps(std::round(1.0L / fps));
    }
    
    return;
}

void MainWindow::updateObjectsList()
{
    ui->objectsListWidget->clear();
    Scene &scene = m_dgl->scene();
    int numObjects = scene.numObjects();
    
    for (int i = 3; i < numObjects; i++) {
        Model &model = scene[i];
        QString objectName = model.name();
        QListWidgetItem *objectItem = new QListWidgetItem(objectName);
        ui->objectsListWidget->addItem(objectItem);
    }
}

void MainWindow::updateObjectInfo(int index)
{
    Model &model = m_dgl->scene()[index];
    Vec3f position = model.position();
    Vec3f rotation = model.rotation();
    Vec3f scale = model.scale();
    
    ui->objectPositionX->setValue(position.x);
    ui->objectPositionY->setValue(position.y);
    ui->objectPositionZ->setValue(position.z);
    ui->objectRotationX->setValue(radianToDegree(rotation.x));
    ui->objectRotationY->setValue(radianToDegree(rotation.y));
    ui->objectRotationZ->setValue(radianToDegree(rotation.z));
    ui->objectScaleX->setValue(scale.x);
    ui->objectScaleY->setValue(scale.y);
    ui->objectScaleZ->setValue(scale.z);
}

void MainWindow::updateCameraProperties()
{
    Vec3f position = m_dgl->camera().position();
    Vec3f lookAt = m_dgl->camera().lookAt();
    long double fov = radianToDegree(m_dgl->camera().FOV());
    long double d = m_dgl->camera().viewDistance();
    long double nearZ = m_dgl->camera().nearZ();
    long double farZ = m_dgl->camera().farZ();
    QString cameraInfo = QString(tr("Камера | (%1) FOV = %2°")).arg(position).arg((double)fov, 0, 'g', 2);
    
    ui->fov->setValue(fov);
    ui->viewDistance->setValue(d);
    ui->nearZ->setValue(nearZ);
    ui->farZ->setValue(farZ);
    ui->cameraPositionX->setValue(position.x);
    ui->cameraPositionY->setValue(position.y);
    ui->cameraPositionZ->setValue(position.z);
    ui->cameraLookAtX->setValue(lookAt.x);
    ui->cameraLookAtY->setValue(lookAt.y);
    ui->cameraLookAtZ->setValue(lookAt.z);
    m_cameraInfo->setText(cameraInfo);
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
    
    updateObjectInfo(index);
}

void MainWindow::deleteObject(const int &index)
{
    if (index < 0) {
        QMessageBox::warning(this, "Объект не выбран!", "Сначала выберите объект для удаления.");
        return;
    }
    
    m_dgl->scene().removeModel(index);
    
    updateViewport();
    updateObjectsList();
}

void MainWindow::createCamera()
{
    long double w = ui->width->value();
    long double l = ui->length->value();
    long double h = ui->height->value();
    long double r = ui->radius->value();
    long double wo = ui->lensWidth->value();
    long double lf = ui->lensMountLength->value();
    long double wf = ui->lensMountWidth->value();
    long double lh = ui->marginWidth->value();
    long double h1 = ui->sideButtonsHeight->value();
    long double h3 = ui->shutterButtonHeight->value();
    long double r1 = ui->sideButtonsRadius->value();
    long double r3 = ui->shutterButtonRadius->value();
    
    Model model = ModelsFactory::camera(w, l, h, r, wo, lf, wf, lh, h1, h3, r1, r3);
    m_dgl->scene().addModel(model);
}

void MainWindow::viewportCameraUpdated()
{
    updateViewport();
    updateCameraProperties();
}

void MainWindow::viewportSizeChanged(QSize newSize)
{
    m_dgl->setViewportSize(newSize.width(), newSize.height());
    updateViewport();
    updateCameraProperties();
}

void MainWindow::objectSelected(QListWidgetItem */*current*/, QListWidgetItem */*previous*/)
{
    int index = ui->objectsListWidget->currentRow();
    
//    bool enabled = true;
    
    if (index < 0 && ui->objectsListWidget->count() > 0) {
        return;
    }
    
    index += 3;
    
//    ui->objectPositionX->setEnabled(enabled);
//    ui->objectPositionY->setEnabled(enabled);
//    ui->objectPositionZ->setEnabled(enabled);
//    ui->objectRotationX->setEnabled(enabled);
//    ui->objectRotationY->setEnabled(enabled);
//    ui->objectRotationZ->setEnabled(enabled);
//    ui->objectScaleX->setEnabled(enabled);
//    ui->objectScaleY->setEnabled(enabled);
//    ui->objectScaleZ->setEnabled(enabled);
    
    m_lastSelectedObjectIndex = index;
    
    updateObjectInfo(index);
}

void MainWindow::on_aboutAction_triggered(bool /*checked*/)
{
    QMessageBox::about(this, "DehaxRenderer", "Визуализатор DehaxRenderer.\nРазработал студент ИПО-13а, Кубашевский Денис (aka Dehax) © ДонНТУ 2016");
}

void MainWindow::on_aboutQt_triggered(bool /*checked*/)
{
    QMessageBox::aboutQt(this, "DehaxRenderer");
}

void MainWindow::on_cameraPositionX_valueChanged(double x)
{
    Vec3f oldPosition = m_dgl->camera().position();
    oldPosition.x = x;
    m_dgl->camera().setPosition(oldPosition);
    
    updateViewport();
}

void MainWindow::on_cameraPositionY_valueChanged(double y)
{
    Vec3f oldPosition = m_dgl->camera().position();
    oldPosition.y = y;
    m_dgl->camera().setPosition(oldPosition);
    
    updateViewport();
}

void MainWindow::on_cameraPositionZ_valueChanged(double z)
{
    Vec3f oldPosition = m_dgl->camera().position();
    oldPosition.z = z;
    m_dgl->camera().setPosition(oldPosition);
    
    updateViewport();
}

void MainWindow::on_cameraLookAtX_valueChanged(double x)
{
    Vec3f lookAt = m_dgl->camera().lookAt();
    lookAt.x = x;
    m_dgl->camera().setLookAt(lookAt);
    
    updateViewport();
}

void MainWindow::on_cameraLookAtY_valueChanged(double y)
{
    Vec3f lookAt = m_dgl->camera().lookAt();
    lookAt.y = y;
    m_dgl->camera().setLookAt(lookAt);
    
    updateViewport();
}

void MainWindow::on_cameraLookAtZ_valueChanged(double z)
{
    Vec3f lookAt = m_dgl->camera().lookAt();
    lookAt.z = z;
    m_dgl->camera().setLookAt(lookAt);
    
    updateViewport();
}

void MainWindow::on_objectPositionX_valueChanged(double x)
{
    if (m_lastSelectedObjectIndex < 0) {
        return;
    }
    
    Model &model = m_dgl->scene()[m_lastSelectedObjectIndex];
    Vec3f position = model.position();
    position.x = x;
    model.setPosition(position);
    
    updateViewport();
}

void MainWindow::on_objectPositionY_valueChanged(double y)
{
    if (m_lastSelectedObjectIndex < 0) {
        return;
    }
    
    Model &model = m_dgl->scene()[m_lastSelectedObjectIndex];
    Vec3f position = model.position();
    position.y = y;
    model.setPosition(position);
    
    updateViewport();
}

void MainWindow::on_objectPositionZ_valueChanged(double z)
{
    if (m_lastSelectedObjectIndex < 0) {
        return;
    }
    
    Model &model = m_dgl->scene()[m_lastSelectedObjectIndex];
    Vec3f position = model.position();
    position.z = z;
    model.setPosition(position);
    
    updateViewport();
}

void MainWindow::on_objectRotationX_valueChanged(double x)
{
    if (m_lastSelectedObjectIndex < 0) {
        return;
    }
    
    Model &model = m_dgl->scene()[m_lastSelectedObjectIndex];
    Vec3f rotation = model.rotation();
    rotation.x = degreeToRadian(x);
    model.setRotation(rotation);
    
    updateViewport();
}

void MainWindow::on_objectRotationY_valueChanged(double y)
{
    if (m_lastSelectedObjectIndex < 0) {
        return;
    }
    
    Model &model = m_dgl->scene()[m_lastSelectedObjectIndex];
    Vec3f rotation = model.rotation();
    rotation.y = degreeToRadian(y);
    model.setRotation(rotation);
    
    updateViewport();
}

void MainWindow::on_objectRotationZ_valueChanged(double z)
{
    if (m_lastSelectedObjectIndex < 0) {
        return;
    }
    
    Model &model = m_dgl->scene()[m_lastSelectedObjectIndex];
    Vec3f rotation = model.rotation();
    rotation.z = degreeToRadian(z);
    model.setRotation(rotation);
    
    updateViewport();
}

void MainWindow::on_objectScaleX_valueChanged(double x)
{
    if (m_lastSelectedObjectIndex < 0) {
        return;
    }
    
    Model &model = m_dgl->scene()[m_lastSelectedObjectIndex];
    Vec3f scale = model.scale();
    scale.x = x;
    model.setScale(scale);
    
    updateViewport();
}

void MainWindow::on_objectScaleY_valueChanged(double y)
{
    if (m_lastSelectedObjectIndex < 0) {
        return;
    }
    
    Model &model = m_dgl->scene()[m_lastSelectedObjectIndex];
    Vec3f scale = model.scale();
    scale.y = y;
    model.setScale(scale);
    
    updateViewport();
}

void MainWindow::on_objectScaleZ_valueChanged(double z)
{
    if (m_lastSelectedObjectIndex < 0) {
        return;
    }
    
    Model &model = m_dgl->scene()[m_lastSelectedObjectIndex];
    Vec3f scale = model.scale();
    scale.z = z;
    model.setScale(scale);
    
    updateViewport();
}

void MainWindow::on_createModelButton_clicked()
{
    createCamera();
    
    updateViewport();
    updateObjectsList();
}

void MainWindow::on_fov_valueChanged(double fov)
{
    m_dgl->camera().setFOV(degreeToRadian(fov));
    
    updateViewport();
    updateCameraProperties();
}

void MainWindow::on_viewDistance_valueChanged(double d)
{
    m_dgl->camera().setViewDistance(d);
    
    updateViewport();
    updateCameraProperties();
}

void MainWindow::on_editModelButton_clicked()
{
    if (m_lastSelectedObjectIndex < 0) {
        QMessageBox::warning(this, "Объект не выбран!", "Выберите объект фотоаппарата для изменения параметров.");
        return;
    }
    
    m_dgl->scene().removeModel(m_lastSelectedObjectIndex);
    
    createCamera();
    
    updateViewport();
    updateObjectsList();
}

void MainWindow::on_nearZ_valueChanged(double nearZ)
{
    m_dgl->camera().setNearZ(nearZ);
    
    updateViewport();
    updateCameraProperties();
}

void MainWindow::on_farZ_valueChanged(double farZ)
{
    m_dgl->camera().setFarZ(farZ);
    
    updateViewport();
    updateCameraProperties();
}

void MainWindow::on_openSceneAction_triggered()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Выберите файл сцены", QString(), "DehaxRenderer Scene (*.drs)");
    
    if (filePath == nullptr) {
        return;
    }
    
    m_dgl->loadScene(filePath);
    
    m_lastSelectedObjectIndex = -1;
    updateViewport();
    updateObjectsList();
}

void MainWindow::on_saveSceneAction_triggered()
{
    QString filePath = QFileDialog::getSaveFileName(this, "Укажите имя файла для сохранения сцены", QString(), "DehaxRenderer Scene (*.drs)");
    
    if (filePath == nullptr) {
        return;
    }
    
    m_dgl->scene().exportToFile(filePath);
}

void MainWindow::on_turnOnParallelAction_toggled(bool /*isOn*/)
{
    m_dgl->camera().changeProjection();
    
    updateViewport();
}

void MainWindow::on_exitAction_triggered()
{
    close();
}

void MainWindow::on_importAction_triggered()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Выберите файл модели", QString(), "Wavefront (*.obj)");
    
    if (filePath == nullptr) {
        return;
    }
    
    Model model = Model("Imported", filePath);
    m_dgl->scene().addModel(model);
    
    updateViewport();
    updateObjectsList();
}
