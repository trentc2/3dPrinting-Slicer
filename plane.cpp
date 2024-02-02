#include "plane.h"
#include "myvector.h"

Plane::Plane()
{
    mNormal = MyVector(0, 0, 1);
}

float Plane::distance()
{
    return mDistance;
}

float Plane::distance_to_point(const MyVector &point)const
{
    return point.dot(mNormal)-mDistance;
}

void Plane::set_normal(MyVector normal)
{
    mNormal = normal;
}

MyVector Plane::normal()
{
    return mNormal;
}

void Plane::set_distance(float distance)
{
    mDistance = distance;
}
