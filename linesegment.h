#ifndef LINESEGMENT_H
#define LINESEGMENT_H

#include "myvector.h"
#include <vector>

class LineSegment
{
public:
    LineSegment(MyVector p0, MyVector p1, int i);
    LineSegment();
//    ~LineSegment();

    friend bool operator==(const LineSegment &seg1, const LineSegment &seg2);

    std::vector<MyVector> v{MyVector(0, 0, 0), MyVector(0, 0,0)};
//    MyVector v1{};
//    MyVector v0{};
    int index{};
    bool vertical{};
};

#endif // LINESEGMENT_H
