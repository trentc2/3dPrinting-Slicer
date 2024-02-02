#include "linesegment.h"
#include "myvector.h"
#include <vector>

LineSegment::LineSegment(MyVector p0, MyVector p1, int i)
{
    v[0] = p0;
    v[1] = p1;
    index = i;
}

LineSegment::LineSegment()
{
    v[1] = MyVector(0, 0, 0);
    v[0] = MyVector(0, 0, 0);
    index = 0;
}

bool operator==(const LineSegment &seg1, const LineSegment &seg2)
{
    return ((seg1.v[0] == seg2.v[0]) && (seg1.v[1] == seg2.v[1]));
}
