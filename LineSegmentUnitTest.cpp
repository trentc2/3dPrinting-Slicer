#include "gtest/gtest.h"
#include "linesegment.h"
#include "linesegment.cpp"
#include "myvector.h"
#include "myvector.cpp"

TEST(WhenInitializingLineSegment, ExpectLineSegmentInitilized)
{
    MyVector vt1{MyVector(1, 3, 4)};
    MyVector vt2{MyVector(1, 2, 3)};
    int i{5};
    LineSegment testSeg{LineSegment(vt1, vt2, i)};
    EXPECT_TRUE(testSeg.v[0] == vt1);
    EXPECT_TRUE(testSeg.v[1] == vt2);
    EXPECT_TRUE(testSeg.index == i);
}

TEST(WhenInitializingLineSegment, ExpectLineSegmentInitilized2)
{
    MyVector v1{MyVector(0, 0, 0)};
    MyVector v2{MyVector(0, 0, 0)};
    int i{0};
    LineSegment testSeg{LineSegment()};
    EXPECT_TRUE(testSeg.v[0] == v1);
    EXPECT_TRUE(testSeg.v[1] == v2);
    EXPECT_TRUE(testSeg.index == i);
}
