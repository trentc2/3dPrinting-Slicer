#include "gtest/gtest.h"
#include "myvector.h"
#include "myvector.cpp"

TEST(TestSettingX, WhenSettingX_ExpectXToChange)
{
    MyVector vectorTest(2.5, 2.5, 2.5);
    MyVector goldVector(70, 2.5, 2.5);
    vectorTest.set_x(70);
    EXPECT_TRUE(vectorTest == goldVector);
}

TEST(TestGettingX, WhenGettingX_ExpectX)
{
    MyVector vectorTest(5, 2.5, 2.5);
    float goldDigit{5};
    EXPECT_TRUE(vectorTest.get_x() ==goldDigit);
}

TEST(TestSettingY, WhenSettingY_ExpectYtoChange)
{
    MyVector vectorTest(2.5, 2.5, 2.5);
    MyVector goldVector(2.5, -70, 2.5);
    vectorTest.set_y(-70);
    EXPECT_TRUE(vectorTest == goldVector);
}

TEST(TestGettingY, WhenGettingY_ExpectY)
{
    MyVector vectorTest(5, 2.5, 2.5);
    float goldDigit{2.5};
    EXPECT_TRUE(vectorTest.get_y() == goldDigit);
}

TEST(TestSettingZ, WhenSettingZ_ExpectZToChange)
{
    MyVector vectorTest(2.5, 2.5, 2.5);
    MyVector goldVector(2.5, 2.5, 70);
    vectorTest.set_z(70);
    EXPECT_TRUE(vectorTest == goldVector);
}

TEST(TestGettingZ, WhenGettingZ_ExpectZ)
{
    MyVector vectorTest(2, 2.5, 5);
    float goldDigit{5};
    EXPECT_TRUE(vectorTest.get_z()== goldDigit);
}

TEST(TestDotProduct, WhenDotting2_n3_4and_5_6_7expect20)
{
    MyVector v1(2, -3, 4);
    MyVector v2(5, 6, 7);
    double goldDigit{20};
    EXPECT_TRUE(v1.dot(v2) == goldDigit);
}

TEST(TestDotProduct, WhenDotting1_n1_1and_0_0_0expect0)
{
    MyVector v1(1, -1, 1);
    MyVector v2(0, 0, 0);
    double goldDigit{0};
    EXPECT_TRUE(v1.dot(v2) == goldDigit);
}

TEST(TestMagnitude, WhenGettingMagnitude_ExpectMagnitudeBack)
{
    MyVector v1(5, 8, 9);
    double goldDigit{sqrt(25+64+81)};
    EXPECT_TRUE(v1.magnitude() == goldDigit);
}

TEST(TestCrossProduct, WhenCrossing_ExpectVectorCrossed_ExpectEqual)
{
    MyVector v1(10.5, 6, 111);
    MyVector v2(5, 6, 7);
    MyVector goldDigit(-624, 481.5, 33);
    EXPECT_TRUE(cross(v1, v2) == goldDigit);
}

TEST(TestNormalize, WhenNormalizeingVector_ExpectVectorNormalized)
{
    MyVector v1(55, 62, 17);
    v1.normalize();
    MyVector goldVector(0.6500800561098412f, 0.7328175177965482f, 0.20093383552486f);
    EXPECT_TRUE(v1 == goldVector);
}

TEST(TestDistanceBetweenPoint, WhenTesting_0sInOneVector_ExpectDistanceBack)
{
    MyVector v1(0, 0, 0);
    MyVector v2(5, 5, 5);
    double distance{MyVector::distance_between(v1, v2)};
    double goldDistance{pow(75, 0.5)};
    EXPECT_EQ(distance, goldDistance);
}

TEST(TestDistanceBetweenPoint, WhenTestingDistance_ExpectNegativeToBeHandled)
{
    MyVector v1(-40, -20, -10);
    MyVector v2(5, 5, 5);
    double distance{MyVector::distance_between(v1, v2)};
    double goldDistance{pow(2875, .5)};
    EXPECT_EQ(distance, goldDistance);
}

TEST(TestMagnitude, WhenTestingDividby0_Expect0_NoErrors)
{
    MyVector v1(0, 0, 0);
    EXPECT_EQ(v1.magnitude(), 0);
}

TEST(TestNormalization, WhenTestingDividby0_Expect0)
{
    MyVector v1(0, 0, 0);
    v1.normalize();
    EXPECT_EQ(v1.magnitude(), 0);
}

TEST(TestOperatorOverlaod_Addition, WhenAddingVectors_ExpectAddingCorrectly)
{
    MyVector v1(5, -5, 5);
    MyVector v2(3, 3, -2);
    MyVector goldVector(8, -2, 3);
    EXPECT_TRUE(v1+v2 == goldVector);
}

TEST(TestOperatorOverload_Subtraction, WhenSubractingVectors_ExpectCorrectSubtraction)
{
    MyVector v1(5, -5, 5);
    MyVector v2(3, 3, -2);
    MyVector goldVector(2, -8, 7);
    EXPECT_TRUE(v1-v2 == goldVector);
}

TEST(TestOperatorOverload_Multiplication, WhenMultiplyingVectorAndInt_ExpectCorrectMultiplication)
{
    MyVector v1(5, -5, 5);
    v1 = v1 *5;
    MyVector goldVector(25, -25, 25);
    EXPECT_TRUE(v1 == goldVector);
}

TEST(TestOperatorOverload_Multiplication, WhenMultiplyingVectorAndFloat_ExpectCorrectMultiplication)
{
    MyVector v1(5, -5, 5);
    v1 = v1 * 5.5f;
    MyVector goldVector(27.5, -27.5, 27.5);
    EXPECT_TRUE(v1 == goldVector);
}

TEST(TestOperatorOverload_Multiplication, WhenVMultiplyingectorAndDouble_ExpectCorrectMultiplication)
{
    MyVector v1(5, -5, 5);
    v1 = v1 * double(5.5);
    MyVector goldVector(27.5, -27.5, 27.5);
    EXPECT_TRUE(v1 == goldVector);
}

TEST(TestOperatorOverload_Multiplication, WhenMultiplyingIntAndVector_ExpectCorrectMultiplication)
{
    MyVector v1(5, -5, 5);
    v1 = 5 * v1;
    MyVector goldVector(25, -25, 25);
    EXPECT_TRUE(v1 == goldVector);
}

TEST(TestOperatorOverload_Multiplication, WhenMultiplyingFloatAndVector_ExpectCorrectMultiplication)
{
    MyVector v1(5, -5, 5);
    v1 = 5.5f * v1;
    MyVector goldVector(27.5, -27.5, 27.5);
    EXPECT_TRUE(v1 == goldVector);
}

TEST(TestOperatorOverload_Multiplication, WhenMultiplyingDoubleAndVector_ExpectCorrectMultiplication)
{
    MyVector v1(5, -5, 5);
    v1 = double(5.5) * v1;
    MyVector goldVector(27.5, -27.5, 27.5);
    EXPECT_TRUE(v1 == goldVector);
}

TEST(TestOperatorOverlad_MultiplyVectors, WhenMultiplyingVectors_ExpectIndividualDigitsMultiplied)
{
    MyVector v1(5, 3, 2);
    MyVector v2(3, 3, 1);
    MyVector goldVector(15, 9, 2);
    EXPECT_TRUE(v1 == v2);
}

TEST(TestOperatorOverload_plus_equal, WhenAddingVectorToCurrentExpectEqual)
{
    MyVector v1(0, 0, 0);
    MyVector v2(1, 1, 1);
    v1 += v2;
    EXPECT_TRUE(v1 == v2);
}

TEST(TestOperatorOverload_plus_equal2, WhenAddingVectorToCurrentExpectEqual)
{
    MyVector v1(0, 0, 0);
    MyVector v2(-1, -1, -1);
    v1 += v2;
    EXPECT_TRUE(v1 == v2);
}

TEST(Testq_vectorConversion, WhenConvertingMyVectortoQVector_ExpectQVectorConverted)
{
    MyVector v1(5, 5, 5);
    QVector3D goldVector(5, 5, 5);
    EXPECT_TRUE(v1.to_qvector() == goldVector);
}

TEST(WhenDiviingByFloat, ExpectEachDigitDivided)
{
    MyVector v1(5, 5, 5);
    MyVector goldV(1, 1, 1);
    float digit{5};
    EXPECT_TRUE(goldV == v1/digit);
}
