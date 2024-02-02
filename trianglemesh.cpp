#include "trianglemesh.h"
#include "myvector.h"
#include "triangle.h"
#include "linesegment.h"
#include <vector>
//#include <glm/glm.hpp>

TriangleMesh::TriangleMesh()
{
    bottomLeftVertex = {999999, 999999, 999999};
    upperRightVertex = {-999999, -999999, -999999};
}

void TriangleMesh::normalize()
{
    MyVector halfBbox = (upperRightVertex - bottomLeftVertex) / 2.0f;
    MyVector startPoint = bottomLeftVertex + halfBbox*MyVector(1, 1, 0);
//    startPoint.set_z(0.0f);
    for (size_t i{0}; i<mesh.size(); i++)
    {
        Triangle &triangle = mesh[i];
        triangle -= startPoint;
    }
    bottomLeftVertex = halfBbox * MyVector(-1, -1, 0);
    upperRightVertex = halfBbox * MyVector(1, 1, 2);
}

size_t TriangleMesh::size()
{
    return mesh.size();
}

void TriangleMesh::push_back(Triangle &triangle)
{
    mesh.push_back(triangle);
    for (size_t j{0}; j<3; j++)
    {
        if (triangle.v[j].get_x() < bottomLeftVertex.get_x())
            bottomLeftVertex.set_x(triangle.v[j].get_x());
        if (triangle.v[j].get_y() < bottomLeftVertex.get_y())
            bottomLeftVertex.set_y(triangle.v[j].get_y());
        if (triangle.v[j].get_z() < bottomLeftVertex.get_z())
            bottomLeftVertex.set_z(triangle.v[j].get_z());
        if (triangle.v[j].get_x() > upperRightVertex.get_x())
            upperRightVertex.set_x(triangle.v[j].get_x());
        if (triangle.v[j].get_y() > upperRightVertex.get_y())
            upperRightVertex.set_y(triangle.v[j].get_y());
        if (triangle.v[j].get_z() > upperRightVertex.get_z())
            upperRightVertex.set_z(triangle.v[j].get_z());
    }
}

std::vector<Triangle> TriangleMesh::get_mesh()
{
    return mesh;
}

MyVector TriangleMesh::mesh_pointA2B_distance()
{
    return MyVector(upperRightVertex.get_x()-bottomLeftVertex.get_x(), upperRightVertex.get_y()-bottomLeftVertex.get_y(), upperRightVertex.get_z()-bottomLeftVertex.get_z());
}

MyVector TriangleMesh::get_bottom_left_vertex()
{
    return bottomLeftVertex;
}

MyVector TriangleMesh::get_upper_right_vertex()
{
    return upperRightVertex;
}
