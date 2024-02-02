#include "gtest/gtest.h"
#include "myvector.h"
#include <vector>
#include "triangle.h"
#include "myvector.cpp"
#include "triangle.cpp"
#include "trianglemesh.h"
#include "trianglemesh.cpp"
#include "plane.h"
#include "plane.cpp"
#include "linesegment.h"
#include "linesegment.cpp"

void create_mesh(TriangleMesh &newMesh)
{
    Triangle t1{Triangle(MyVector(1, 0, 0), MyVector(0, 0, 0), MyVector(1, 0, 0), MyVector(0, 1, 0))};
    Triangle t2{Triangle(MyVector(1, 0, 0), MyVector(1, 0, 0), MyVector(0, 1, 0), MyVector(1, 1, 0))};
    Triangle t3{Triangle(MyVector(1, 0, 0), MyVector(1, 1, 0), MyVector(1, 2, 0), MyVector(0, 1, 0))};
    newMesh.push_back(t1);
    newMesh.push_back(t2);
    newMesh.push_back(t3);
}

TEST (TestGettingMesh, WhenGettingMesh_ExpectMeshBack)
{
    TriangleMesh tMesh{TriangleMesh()};
    create_mesh(tMesh);
    std::vector<Triangle> meshes = tMesh.get_mesh();
    EXPECT_TRUE(meshes[0] == Triangle(MyVector(1, 0, 0), MyVector(0, 0, 0), MyVector(1, 0, 0), MyVector(0, 1, 0)));
}

TEST (TestGettingMeshSize, WhenGettingMeshSize_ExpectSizeBack)
{
    TriangleMesh tMesh{TriangleMesh()};
    create_mesh(tMesh);
    std::size_t meshSize{tMesh.size()};
    std::size_t goldSize{3};
    EXPECT_EQ(goldSize, meshSize);
}


TEST (TestNormalizingMesh, WhenNormalizingMesh_ExpectObjectCentered)
{
    TriangleMesh tMesh{TriangleMesh()};
    create_mesh(tMesh);
    tMesh.normalize();
    MyVector goldLeftVertex(MyVector(-0.5, -1, 0));
    MyVector goldRightVertex(MyVector(0.5, 1, 0));
    EXPECT_TRUE(goldLeftVertex == tMesh.get_bottom_left_vertex());
    EXPECT_TRUE(goldRightVertex == tMesh.get_upper_right_vertex());
}


TEST (TestGettingVectorDistanceBetweenTheTwoVertexesOfObject, WhenGettingDistance_ExpectVectorDistance)
{
    TriangleMesh tMesh{TriangleMesh()};
    create_mesh(tMesh);
    MyVector distance{tMesh.mesh_pointA2B_distance()};
    MyVector goldDistance{MyVector(1, 2, 0)};
    EXPECT_TRUE(distance == goldDistance);
}
