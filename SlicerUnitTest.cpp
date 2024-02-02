#include "gtest/gtest.h"
#include "slicer.h"
#include "slicer.cpp"
#include "myvector.h"
#include "myvector.cpp"
#include "plane.h"
#include "plane.cpp"
#include "linesegment.h"
#include "linesegment.cpp"
#include "triangle.h"
#include "triangle.cpp"
#include "trianglemesh.h"
#include "trianglemesh.cpp"
#include <vector>
//#include <filesystem>

TEST (TestFileTypeForImport, IfFileASCIIExcpect_1)
{
    // ***** Change file path to a test file **** //
    const char* fileName{"D:/Documents/MBA Classes/Software Development/FinalProject/FinalProject/models/20mm_cube.stl"};
    int goldDigit{is_file_binary(fileName)};
    EXPECT_EQ(1, goldDigit);
}


TEST (TestFileTypeForImport, IfFileIsBinaryExcpect_0)
{
    // ***** Change file path to a test file **** //
    const char* fileName{"D:/Documents/MBA Classes/Software Development/FinalProject/FinalProject/models/Screw large.stl"};
    int goldDigit{is_file_binary(fileName)};
    EXPECT_EQ(0, goldDigit);
}

TEST (TestFileTypeForImport, IfFileIsCorrupt_Expectn1)
{
    // ***** Change file path to a test file **** //
    const char* fileName{"D:/Documents/MBA Classes/Software Development/FinalProject/FinalProject/models/20mm_cube_corrupt.stl"};
    int goldDigit{is_file_binary(fileName)};
    EXPECT_EQ(0, goldDigit);
}


TEST(ImportingFileIfASCII, WhenImportingFileCorrectlyExpect_0)
{
    TriangleMesh *mesh{new TriangleMesh};
    float scale{1.0f};

    // ***** Change file path to a test file **** //
    const char* fileName{"D:/Documents/MBA Classes/Software Development/FinalProject/FinalProject/models/20mm_cube.stl"};
    int goldDigit{import_if_not_binary(fileName, mesh, scale)};
    EXPECT_EQ(0, goldDigit);
}


TEST(ImportingFileIfBinary, WhenImportingFileCorrectlyExpect_0)
{
    TriangleMesh *mesh{new TriangleMesh};
    float scale{1.0f};

    // ***** Change file path to a test file **** //
    const char* fileName{"D:/Documents/MBA Classes/Software Development/FinalProject/FinalProject/models/Screw large.stl"};
    int goldDigit{import_if_binary(fileName, mesh, scale)};
    EXPECT_EQ(0, goldDigit);
}
