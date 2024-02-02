#ifndef SLICER_H
#define SLICER_H

#include "trianglemesh.h"
#include <vector>
#include "linesegment.h"

void triangle_mesh_slicer(TriangleMesh *mesh, std::vector<std::vector<LineSegment>> *slicedWithLineSegments,
                         const float &layerThickness, Plane &plane, const std::vector<Triangle> &meshingLoop,
                         size_t &i, const float &z0);
int import_if_binary(const char *stlFile, TriangleMesh *mesh, float scaleAdjustment);
int import_if_not_binary(const char *stlFile, TriangleMesh *mesh, float scaleAdjustment);

bool degenerate (Triangle triangle);
int is_file_binary(const char *fileName);


#endif // SLICER_H
