#ifndef TRIANGLEMESH_H
#define TRIANGLEMESH_H

#include "myvector.h"
#include <vector>
#include "triangle.h"


class TriangleMesh
{
public:
    TriangleMesh();
//    ~TriangleMesh();
    void normalize();
    size_t size();
    void push_back(Triangle &t);
    std::vector<Triangle> get_mesh();
    MyVector mesh_pointA2B_distance();
    MyVector get_bottom_left_vertex();
    MyVector get_upper_right_vertex();


protected:
    std::vector<Triangle> mesh;
    MyVector bottomLeftVertex{MyVector(0, 0, 0)};
    MyVector upperRightVertex{MyVector(0, 0, 0)};
};


#endif // TRIANGLEMESH_H
