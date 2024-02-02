#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <Qt3DExtras/QConeMesh>
#include <Qt3DCore/qentity.h>
#include <Qt3DExtras/qt3dwindow.h>
#include <Qt3DCore/qtransform.h>
#include <QVector>
#include <QProgressBar>

#include "trackballcameracontroller.h"
#include "trianglemesh.h"

namespace Ui {
class MainWindowForm;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


public slots:
    void on_actionExit_triggered();

protected:
    void create_3d_window();
    void create_light();
    void create_camera();
    void create_root_entity();
    void dialog_open_file();

private slots:
    void on_actionOpen_triggered();
    void on_sliceObjectButton_clicked();
    void on_selectFileToImport_clicked();
    void on_objectScale_valueChanged(double arg1);
    void on_checkBox_toggled(bool checked);
    void on_layerThickness_valueChanged(double arg1);

    void on_previewSlices_clicked();

private:
    Ui::MainWindowForm *mMainWindowUI;
    Qt3DExtras::Qt3DWindow *mView{nullptr};
    Qt3DCore::QEntity *mRootEntity{nullptr};
    Qt3DCore::QEntity *modelEntity{nullptr};
    Qt3DCore::QTransform *modelTransform{nullptr};
    Qt3DCore::QNode *cameraParent{nullptr};
    std::string fileNameString{};
    TriangleMesh *mesh{nullptr};
    std::vector<std::vector<LineSegment>> *slicedWithLineSegments{nullptr};
    QProgressBar *slicingProgress{};

    float modelScale{1.0f};
    float modelScaleInput{1.0f};
    float in2mm{1.0f};
    float layerThickness{0.1f};
    float buildBoxSize{127.0f};


    void create_coord_axis();
    int MainWindow::begin_slicing();
    void update_model_scale();
};

#endif // MAINWINDOW_H

