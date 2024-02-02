#ifndef PLANE_H
#define PLANE_H

#include "myvector.h"

class Plane
{
public:
    Plane();
    float distance();
    float distance_to_point(const MyVector &point)const;
    void set_normal(MyVector normal);
    void set_distance(float distance);
    MyVector normal();

protected:
    MyVector mNormal{}; //normal vector of the plane
    float mDistance{};  //distance from origin to plane
    MyVector origin{MyVector(0, 0, 0)};
};

#endif // PLANE_H
