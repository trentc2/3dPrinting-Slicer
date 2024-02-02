#include "mainwindow.h"
#include <vector>
//#include "ui_mainwindowform.h"
#include <Qt3DExtras/qt3dwindow.h>
#include <Qt3DExtras/qfirstpersoncameracontroller.h>
#include <Qt3DRender/qpointlight.h>
#include <Qt3DRender/qcamera.h>
#include <Qt3DRender/qattribute.h>
#include <Qt3DRender/qbuffer.h>
#include <Qt3DExtras/qforwardrenderer.h>
#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DRender/QMesh>
#include <QUrl>
#include "slicer.h"

#include <QDesktopServices>


void set_position_as_float(float *& array, QVector3D position)
{
    *array =  (float)position[0];
    array++;
    *array =  (float)position[1];
    array++;
    *array =  (float)position[2];
    array++;
}

void create_vector(QVector3D point1, QVector3D point2, QColor color, Qt3DCore::QEntity *parent)
{
    Qt3DRender::QGeometry *coordAxisEntity = new Qt3DRender::QGeometry(parent);

    QByteArray bufferBytes;
    int numberOfPoints{2};
    int numberOfComponents{3};
    int totalNumberOfBytes(numberOfPoints * numberOfComponents * sizeof(float));
    bufferBytes.resize(totalNumberOfBytes);
    float *positions = reinterpret_cast<float*>(bufferBytes.data());
    set_position_as_float(positions, point1);
    set_position_as_float(positions, point2);


    Qt3DRender::QBuffer *pointBuffer = new Qt3DRender::QBuffer(coordAxisEntity);
    pointBuffer->setData(bufferBytes);

    Qt3DRender::QAttribute *positionAttribute = new Qt3DRender::QAttribute(coordAxisEntity);
    positionAttribute->setName(Qt3DRender::QAttribute::defaultPositionAttributeName());
    positionAttribute->setVertexBaseType(Qt3DRender::QAttribute::Float);
    positionAttribute->setVertexSize(numberOfComponents);
    positionAttribute->setAttributeType(Qt3DRender::QAttribute::VertexAttribute);
    positionAttribute->setBuffer(pointBuffer);
    positionAttribute->setByteStride(numberOfComponents * sizeof(float));
    positionAttribute->setCount(numberOfPoints);

    coordAxisEntity->addAttribute(positionAttribute);

    QByteArray indexBytes;
    unsigned int numberOfPointsPerLine{2};
    unsigned int numberOfLines{1};
    indexBytes.resize(numberOfPointsPerLine* numberOfLines * sizeof(unsigned int));
    unsigned int *indices = reinterpret_cast<unsigned int*>(indexBytes.data());
    *indices++ = 0;
    *indices++ = 1;

    Qt3DRender::QBuffer *indexBuffer = new Qt3DRender::QBuffer(coordAxisEntity);
    indexBuffer->setData(indexBytes);

    Qt3DRender::QAttribute *indexAttribute = new Qt3DRender::QAttribute(coordAxisEntity);
    indexAttribute->setVertexBaseType(Qt3DRender::QAttribute::UnsignedInt);
    indexAttribute->setAttributeType(Qt3DRender::QAttribute::IndexAttribute);
    indexAttribute->setBuffer(indexBuffer);
    indexAttribute->setCount(numberOfPointsPerLine * numberOfLines);
    coordAxisEntity->addAttribute(indexAttribute);

    Qt3DRender::QGeometryRenderer *line = new Qt3DRender::QGeometryRenderer(parent);
    line->setGeometry(coordAxisEntity);
    line->setPrimitiveType(Qt3DRender::QGeometryRenderer::Lines);

    Qt3DExtras::QPhongMaterial *material = new Qt3DExtras::QPhongMaterial();
    material->setAmbient(color);

    Qt3DCore::QEntity *lineEntity = new Qt3DCore::QEntity(parent);
    lineEntity->addComponent(line);
    lineEntity->addComponent(material);
}

void import_model_file(QString fileName, Qt3DCore::QEntity* parent, Qt3DCore::QEntity *modelEntity,
                       Qt3DCore::QTransform *modelTransform,
                       float scale, float buildBox)
{
    Qt3DExtras::QPhongMaterial *material = new Qt3DExtras::QPhongMaterial();
    material->setAmbient(Qt::blue);
    material->setDiffuse(Qt::white);

    Qt3DRender::QMesh *modelMesh = new Qt3DRender::QMesh();
    modelMesh->setSource(QUrl::fromLocalFile(fileName));

    modelTransform->setTranslation(QVector3D(-buildBox/2+5, 50, 0));
    modelTransform->setRotation(QQuaternion::fromAxisAndAngle({0, 0, 0}, 25));
    modelTransform->setScale3D({scale, scale, scale});

    modelEntity->addComponent(modelMesh);
    modelEntity->addComponent(material);
    modelEntity->addComponent(modelTransform);
    modelEntity->setEnabled(true);
}

void slice_model_file(std::string fileName, Qt3DCore::QEntity* parent)
{

}
