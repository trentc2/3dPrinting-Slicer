#include "gtest/gtest.h"
#include "triangle.h"
#include "triangle.cpp"
#include "myvector.h"
#include "myvector.cpp"
#include "plane.h"
#include "plane.cpp"
#include "linesegment.h"
#include "linesegment.cpp"


TEST (TestInitialization, WhenConstructingTrianglesExpectTrue)
{
    Triangle testT{Triangle(MyVector(1, 0, 0), MyVector(1, 1, 1), MyVector(1, 2, 1), MyVector(1, 1, 1))};
    Triangle testT2{Triangle(MyVector(1, 0, 0), MyVector(1, 1, 1), MyVector(1, 2, 1), MyVector(1, 1, 1))};
    EXPECT_TRUE(testT == testT2);
}

TEST (TestOperatorOverload_MinusEqual, WhenEqualAndSubtracting_ExpectMinusSubtracted)
{
    Triangle t1{Triangle(MyVector(1, 0, 0), MyVector(1, 1, 1), MyVector(1, 2, 3), MyVector(1, 1, 1))};
    MyVector v1{MyVector(1, 1, 1)};
    Triangle goldT{Triangle(MyVector(1, 0, 0), MyVector(0, 0, 0), MyVector(0, 1, 2), MyVector(0, 0, 0))};
    EXPECT_TRUE((t1-=v1) == goldT);
}

TEST (TestFindingItersections, WhenFindingIntersections_ExpectInteresections)
{
    Triangle testT{Triangle(MyVector(1, 0, 0), MyVector(2, 0, 0), MyVector(0, 0, 0), MyVector(0, 2, 0))};
    Plane plane{Plane()};
    plane.set_normal(MyVector(1, 0, 0));
    plane.set_distance(1);
    std::vector<MyVector> intersectPoints{};
    testT.find_intersections(plane, intersectPoints);
    EXPECT_TRUE(intersectPoints.size() == 2);
    EXPECT_TRUE(MyVector(1, 0, 0) == intersectPoints[0]);
    EXPECT_TRUE(MyVector(1, 1, 0) == intersectPoints[1]);
}

TEST (TestIntersectingPlane, WhenFindingSlicedPlane_ExpectLineSegmentOnPlane)
{
    Triangle testT{Triangle(MyVector(1, 0, 0), MyVector(2, 0, 0), MyVector(0, 0, 0), MyVector(0, 2, 0))};
    Plane plane{Plane()};
    plane.set_normal(MyVector(1, 0, 0));
    plane.set_distance(1);
    LineSegment seg{LineSegment()};
    testT.intersect_plane(plane, seg);
    LineSegment goldSegment{LineSegment(MyVector(1, 0, 0), MyVector(1, 1, 0), 0)};
    EXPECT_TRUE(goldSegment == seg);
}
