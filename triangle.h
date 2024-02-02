#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "myvector.h"
#include "plane.h"
#include "linesegment.h"
#include <vector>


class Triangle
{
public:
    Triangle(MyVector norm, MyVector p0, MyVector p1, MyVector p2);
    ~Triangle();

    int intersect_plane(Plane &plane, LineSegment &seg)const;
    void find_intersections(Plane &plane, std::vector<MyVector> &intersectPoints)const;

    Triangle& operator-=(const MyVector &v1);
    friend bool operator==(const Triangle &t1, const Triangle &t2);
    bool operator<(const Triangle &t1);


    MyVector normal{};
    std::vector<MyVector> v{MyVector(0, 0, 0), MyVector(0, 0,0), MyVector(0, 0,0)};
//    MyVector v0{};
//    MyVector v1{};
//    MyVector v2{};
};

#endif // TRIANGLE_H
