#include "triangle.h"
#include "myvector.h"
#include "plane.h"
#include <vector>

Triangle::Triangle(MyVector norm, MyVector p0, MyVector p1, MyVector p2)
{
    normal = norm;
    v[0] = p0;
    v[1] = p1;
    v[2] = p2;
}

Triangle::~Triangle()
{

}

Triangle& Triangle::operator-=(const MyVector &v1)
{
    v[0] -= v1;
    v[1] -= v1;
    v[2] -= v1;
    return  *this;
}

bool operator==(const Triangle &t1, const Triangle &t2)
{
    if ((t2.v[0] == t1.v[0]) && (t1.v[1] == t2.v[1]) && (t1.v[2] == t2.v[2]))
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Triangle::find_intersections(Plane &plane, std::vector<MyVector> &intersectPoints)const
{
    size_t lines[] = {0,1,1,2,2,0};
    for (size_t n{0}; n<3; n++)
    {
        const MyVector &pointA{v[lines[n*2+0]]};
        const MyVector &pointB{v[lines[n*2+1]]};
        const float distancePointA{plane.distance_to_point(pointA)};
        const float distancePointB{plane.distance_to_point(pointB)};
        if(distancePointA*distancePointB < 0)
        {
            float intersectionFactor{distancePointA / (distancePointA - distancePointB)};
            MyVector bMinusA = pointB-pointA;
            intersectPoints.push_back(pointA+bMinusA*intersectionFactor);
        }
        else if(0 == distancePointA) //plane falls right on one of the three triangle verticies
        {
            if (intersectPoints.size()<2)
                intersectPoints.push_back(pointA);
        }
        else if (0==distancePointB)
        {
            if(intersectPoints.size()<2)
                intersectPoints.push_back(pointB);
        }
    }
}

int Triangle::intersect_plane(Plane &plane, LineSegment &seg)const
{
    size_t countFront{0};
    size_t countBack{0};
    float distance{};

    for (size_t j{0}; j< 3; j++)
    {
        distance = plane.distance_to_point(v[j]);
        if (distance< 0)
            countBack++;
        else
            countFront++;
    }
    if(countBack == 3)
        return -1;
    else if (countFront == 3)
        return 1;
    std::vector<MyVector> intersectPoints{};
    this->find_intersections(plane, intersectPoints);
    if(intersectPoints.size() == 2)
    {
        seg.v[0] = intersectPoints[0];
        seg.v[1] = intersectPoints[1];
        return 0;
    }
    return -2;
}
