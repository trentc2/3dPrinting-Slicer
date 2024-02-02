#include "mainwindow.h"
#include <vector>
#include "ui_mainwindowform.h"
#include <Qt3DExtras/qt3dwindow.h>
#include <Qt3DExtras/qfirstpersoncameracontroller.h>
#include <Qt3DRender/qpointlight.h>
#include <Qt3DRender/qcamera.h>
#include <Qt3DRender/qattribute.h>
#include <Qt3DRender/qbuffer.h>
#include <Qt3DCore/qentity.h>
#include <Qt3DRender/qcameralens.h>
#include <Qt3DExtras/qforwardrenderer.h>
#include <Qt3DCore/qtransform.h>
#include <Qt3DExtras/QPhongMaterial>
#include <QFileDialog>
#include <QMessageBox>
#include <QProgressBar>

#include "trackballcameracontroller.h"
#include "MainWindowUtility.h"
#include "slicer.h"
#include "myvector.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , mMainWindowUI(new Ui::MainWindowForm)
{
    mMainWindowUI->setupUi(this);

    slicingProgress = mMainWindowUI->progressBar;

    this->create_3d_window();

    create_root_entity();

    create_camera();

    create_light();

    create_coord_axis();
}

MainWindow::~MainWindow()
{
    delete mMainWindowUI;
}

void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}

void MainWindow::create_3d_window()
{
    mView = new Qt3DExtras::Qt3DWindow();
    mView->defaultFrameGraph()->setClearColor(QColor(QRgb(0x000000)));
    QGridLayout *gridLayout = new QGridLayout(this->mMainWindowUI->graphicsFrame);
    QWidget *container = QWidget::createWindowContainer(mView);
    gridLayout->addWidget(container,0,0);
}

void MainWindow::create_camera()
{
    Qt3DRender::QCamera *cameraEntity = mView->camera();
    cameraEntity->lens()->setPerspectiveProjection(45.0f, 16.0f/9.0f, 0.1f, 1000.0f);
    cameraEntity->setPosition(QVector3D(2.0f * buildBoxSize, 2.0f * buildBoxSize, 1.0f * buildBoxSize));
    cameraEntity->setViewCenter(QVector3D(0.0f, 0.0f, buildBoxSize/2.0f));
    cameraEntity->setUpVector(QVector3D(0, 0, 1.0f));

    TrackballCameraController* camController= new TrackballCameraController(mRootEntity);
    camController->setCamera(cameraEntity);
}

void MainWindow::create_light()
{
    Qt3DCore::QEntity *lightEntity = new Qt3DCore::QEntity(mRootEntity);
    Qt3DRender::QPointLight *light = new Qt3DRender::QPointLight(lightEntity);
    light->setColor(Qt::white);
    light->setIntensity(.7f);
    lightEntity->addComponent(light);
    Qt3DCore::QTransform *lightTransform = new Qt3DCore::QTransform(lightEntity);
    lightTransform->setTranslation(QVector3D(2.0f * buildBoxSize, 2.0f * buildBoxSize, 0.0f));
    lightEntity->addComponent(lightTransform);
}

void MainWindow::create_root_entity()
{
    mRootEntity = new Qt3DCore::QEntity();
    mView->setRootEntity(mRootEntity);
}

void MainWindow::create_coord_axis()
{
    create_vector({buildBoxSize/2, -buildBoxSize/2, 0.0f}, {-buildBoxSize/2, -buildBoxSize/2, 0.0f}, Qt::white, mRootEntity);
    create_vector({-buildBoxSize/2, buildBoxSize/2, 0.0f}, {-buildBoxSize/2, -buildBoxSize/2, 0.0f}, Qt::white, mRootEntity);
    create_vector({-buildBoxSize/2, -buildBoxSize/2, buildBoxSize}, {-buildBoxSize/2, -buildBoxSize/2, 0.0f}, Qt::white, mRootEntity);

    create_vector({buildBoxSize/2, buildBoxSize/2, buildBoxSize}, {-buildBoxSize/2, buildBoxSize/2, buildBoxSize}, Qt::white, mRootEntity);
    create_vector({-buildBoxSize/2, buildBoxSize/2, 0.0f}, {-buildBoxSize/2, buildBoxSize/2, buildBoxSize}, Qt::white, mRootEntity);
    create_vector({-buildBoxSize/2, -buildBoxSize/2, buildBoxSize}, {-buildBoxSize/2, buildBoxSize/2, buildBoxSize}, Qt::white, mRootEntity);

    create_vector({buildBoxSize/2, buildBoxSize/2, buildBoxSize}, {buildBoxSize/2, buildBoxSize/2, 0.0f}, Qt::white, mRootEntity);
    create_vector({-buildBoxSize/2, buildBoxSize/2, 0.0f}, {buildBoxSize/2, buildBoxSize/2, 0.0f}, Qt::white, mRootEntity);
    create_vector({buildBoxSize/2, -buildBoxSize/2, 0.0f}, {buildBoxSize/2, buildBoxSize/2, 0.0f}, Qt::white, mRootEntity);

    create_vector({buildBoxSize/2, buildBoxSize/2, buildBoxSize}, {buildBoxSize/2, -buildBoxSize/2, buildBoxSize}, Qt::white, mRootEntity);
    create_vector({-buildBoxSize/2, -buildBoxSize/2, buildBoxSize}, {buildBoxSize/2, -buildBoxSize/2, buildBoxSize}, Qt::white, mRootEntity);
    create_vector({buildBoxSize/2, -buildBoxSize/2, 0.0f}, {buildBoxSize/2, -buildBoxSize/2, buildBoxSize}, Qt::white, mRootEntity);
}

void MainWindow::dialog_open_file()
{
    QString fileName = QFileDialog::getOpenFileName(
                this,
                tr("Open 3D Model"),
                QDir::currentPath(),
                "All Files (*.*);;3D Models (*.stl, *.obj, *.amf, *.3df)");
    if(modelEntity != nullptr)
    {
        modelEntity->setParent((Qt3DCore::QEntity *) nullptr);
    }
    modelEntity = new Qt3DCore::QEntity(mRootEntity);
    modelTransform = new Qt3DCore::QTransform();
    import_model_file(fileName, mRootEntity, modelEntity, modelTransform, modelScale, buildBoxSize);
    fileNameString = fileName.toStdString();
}


void MainWindow::on_actionOpen_triggered()
{
    dialog_open_file();
}


void MainWindow::on_sliceObjectButton_clicked()
{
    const char* tempFileName = fileNameString.c_str();
    if(mesh != nullptr)
    {
        delete mesh;
    }
    mesh = new TriangleMesh;
    slicedWithLineSegments = new std::vector<std::vector<LineSegment>>;
    int fileBinary{is_file_binary(tempFileName)};
    if(fileBinary==-1)
    {
        QMessageBox errorBox;
        errorBox.setText("Error Slicing File");
        errorBox.exec();
    }
    else
    {
        if(fileBinary == 1)
        {
            import_if_not_binary(tempFileName, mesh, modelScale);
        }
        else
        {
            import_if_binary(tempFileName, mesh, modelScale);
        }
        mesh->normalize();
        this->begin_slicing();
    }

}

int MainWindow::begin_slicing()
{
    Plane plane{};
    plane.set_normal(MyVector(0, 0, 1));
    const MyVector distanceBoundingBox = mesh->mesh_pointA2B_distance();
    const size_t numberSlices = 1 + (int)(distanceBoundingBox.get_z()/layerThickness);
    const std::vector<Triangle> &meshingLoop = mesh->get_mesh();
    const float z0 = mesh->get_bottom_left_vertex().get_z();
    for (size_t i{0}; i<numberSlices; ++i)
    {
        triangle_mesh_slicer(mesh, slicedWithLineSegments, layerThickness, plane, meshingLoop, i, z0);
        int progress = ((float)i/(float)numberSlices) * 100;
        slicingProgress->setValue(progress);
    }
    slicingProgress->setValue(100);
    return 0;
}

void MainWindow::on_selectFileToImport_clicked()
{
    dialog_open_file();
}

void MainWindow::update_model_scale()
{
    modelScale = modelScaleInput * in2mm;
    if(modelTransform != nullptr)
    {
        modelTransform->setScale3D({modelScale, modelScale, modelScale});
    }
}


void MainWindow::on_objectScale_valueChanged(double arg1)
{
    modelScaleInput = arg1;
    this->update_model_scale();
}


void MainWindow::on_checkBox_toggled(bool checked)
{
    if(checked == true)
    {
        in2mm = 25.4f;
    }
    else
    {
        in2mm = 1.0f;
    }
    this->update_model_scale();
}


void MainWindow::on_layerThickness_valueChanged(double arg1)
{
    layerThickness = float(arg1);
}


void MainWindow::on_previewSlices_clicked()
{
    mMainWindowUI->generatingPreview->setText("#####---Generating Preview---#####");
    if(modelEntity != nullptr)
    {
        modelEntity->setParent((Qt3DCore::QNode *) nullptr);
        size_t outerLoop{slicedWithLineSegments->size()};
        for(size_t i{0}; i<outerLoop; ++i)
        {
            size_t innerLoop{slicedWithLineSegments->operator[](i).size()};
            for(size_t j{0}; j<innerLoop; ++j)
            {
                LineSegment &segment = slicedWithLineSegments->operator[](i)[j];
                create_vector(segment.v[0].to_qvector(), segment.v[1].to_qvector(), Qt::red, mRootEntity);
            }

        }
        mMainWindowUI->generatingPreview->setText("Preview Generated");
    }
    else
    {
        mMainWindowUI->generatingPreview->setText("- - -");
    }
}

