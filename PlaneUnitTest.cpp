#include "gtest/gtest.h"
#include "plane.h"
#include "plane.cpp"
#include "myvector.h"
#include "myvector.cpp"

TEST(TestGettingPlaneDistance, WhenGettingDistance_ExpectDistance_0)
{
    Plane testPlane{Plane()};
    EXPECT_EQ(testPlane.distance(), 0.0f);
}

TEST(TestSettingDistance, WhenSettingDistance_ExpectDistanceSet)
{
    Plane testPlane{Plane()};
    float goldDigit{5.55f};
    testPlane.set_distance(goldDigit);
    EXPECT_EQ(testPlane.distance(), goldDigit);
}

TEST(TestSettingDistance, WhenSettingDistanceNegativeNumber_ExpectDistanceSet)
{
    Plane testPlane{Plane()};
    float goldDigit{-5.549f};
    testPlane.set_distance(goldDigit);
    EXPECT_EQ(testPlane.distance(), goldDigit);
}

TEST(TestGettingPlaneNormal, WhenGettingNormal_ExpectTheNormal)
{
    MyVector testNormal{MyVector(0, 0, 1)};
    Plane testPlane{Plane()};
    EXPECT_TRUE(testPlane.normal() == testNormal);
}

TEST(TestSettingNormaltoPlane, WhenSettingNormal_ExpectNormalSet)
{
    MyVector testNormal{MyVector(6, 2, 1)};
    Plane testPlane{Plane()};
    testPlane.set_normal(testNormal);
    EXPECT_TRUE(testPlane.normal() == testNormal);
}

TEST(TestGettingDistanceFromNormalToPoint, WhenGettingDistance_ExpectDistanceBetweenNormalandPoint)
{
    MyVector testPoint(5, 3, -1);
    Plane testPlane{Plane()};
    float goldNum{-1};
    EXPECT_EQ(goldNum, testPlane.distance_to_point(testPoint));
}

TEST(TestGettingDistanceFromNormalToPoint, WhenGettingDistance_ExpectDistanceBetweenNormalandPoint2)
{
    MyVector testPoint(5, 3, -1);
    Plane testPlane{Plane()};
    testPlane.set_normal(MyVector(5, 3, -4));
    testPlane.set_distance(4);
    float goldNum{34};
    EXPECT_EQ(goldNum, testPlane.distance_to_point(testPoint));
}
