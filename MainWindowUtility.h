#ifndef MAINWINDOWUTILITY_H
#define MAINWINDOWUTILITY_H

#include <QVector3D>
#include <Qt3DCore>


void create_vector(QVector3D point1, QVector3D point2, QColor color, Qt3DCore::QEntity *parent);

void set_position_as_float(float *& array, QVector3D position);

void import_model_file(QString fileName, Qt3DCore::QEntity* parent, Qt3DCore::QEntity *modelEntity,
                       Qt3DCore::QTransform *modelTransform, float scale, float buildBox);

void create_model_file(QString fileName, Qt3DCore::QEntity* parent);



#endif // MAINWINDOWUTILITY_H
