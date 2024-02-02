#include "slicer.h"
#include "trianglemesh.h"
#include <fstream>
#include <string>
#include <iostream>

#include "myvector.h"
#include "linesegment.h"
#include "plane.h"
#include "triangle.h"


int import_if_not_binary(const char *stlFile, TriangleMesh *mesh, float scaleAdjustment)
{
    std::ifstream inFile(stlFile);
    if (!inFile.good())
    {
        return 1;
    }
    char title[80];
    std::string facetOrSolid0{};
    std::string facetOrSolid1{};
    float normal0{}, normal1{}, normal2, point0{};
    float point1{}, point2{}, point3{}, point4{}, point5{}, point6{}, point7{}, point8{};
    inFile.read(title, 80);
    while (!inFile.eof())
    {
        inFile >> facetOrSolid0;
        if(facetOrSolid0 =="facet")
        {
            inFile >> facetOrSolid1 >> normal0 >> normal1 >> normal2; // normal xyz
            inFile >> facetOrSolid0 >> facetOrSolid1; // outer loop
            inFile >> facetOrSolid0 >> point0 >> point1 >> point2; //vertex 1
            inFile >> facetOrSolid0 >> point3 >> point4 >> point5; //vertex 2
            inFile >> facetOrSolid0 >> point6 >> point7 >> point8; //vetex 3
            inFile >> facetOrSolid0;
            inFile >> facetOrSolid0;
            Triangle newTriangle(MyVector(normal0 * scaleAdjustment, normal1 * scaleAdjustment, normal2 * scaleAdjustment),
                                 MyVector(point0 * scaleAdjustment, point1 * scaleAdjustment, point2 * scaleAdjustment),
                                 MyVector(point3 * scaleAdjustment, point4 * scaleAdjustment, point5 * scaleAdjustment),
                                 MyVector(point6 * scaleAdjustment, point7 *scaleAdjustment, point8 * scaleAdjustment));
            mesh->push_back(newTriangle);
        }
        else if(facetOrSolid0 == "endsolid")
        {
            break;
        }
    }
    inFile.close();
    return 0;
}

int import_if_binary(const char *stlFile, TriangleMesh *mesh, float scaleAdjustment)
{
    std::FILE *openFile{std::fopen(stlFile, "rb")};
    if(!openFile)
    {
        return 1;
    }
    char title[80];
    int nFaces{};
    fread(title, 80, 1, openFile);
    fread((void*)&nFaces, 4, 1, openFile);
    float verticies[12];
    unsigned short uint16{};
    for (size_t i{0}; i<nFaces; ++i)
    {
        for(size_t j{0}; j<12; ++j)
        {
            fread((void*)&verticies[j], sizeof(float), 1, openFile);
        }
        fread((void*)&uint16, sizeof(unsigned short), 1, openFile);
        Triangle newTriangle(MyVector(verticies[0] * scaleAdjustment, verticies[1] * scaleAdjustment, verticies[2] * scaleAdjustment),
                MyVector(verticies[3] * scaleAdjustment, verticies[4] * scaleAdjustment, verticies[5] * scaleAdjustment),
                MyVector(verticies[6] * scaleAdjustment, verticies[7] * scaleAdjustment, verticies[8] * scaleAdjustment),
                MyVector(verticies[9] * scaleAdjustment, verticies[10] * scaleAdjustment, verticies[11] * scaleAdjustment));
        if(!degenerate(newTriangle))
        {
            mesh->push_back(newTriangle);
        }
    }
    fclose(openFile);
    return 0;
}

void triangle_mesh_slicer(TriangleMesh *mesh, std::vector<std::vector<LineSegment>> *slicedWithLineSegments,
                         const float &layerThickness, Plane &plane, const std::vector<Triangle> &meshingLoop,
                         size_t &i, const float &z0)
{
    std::vector<LineSegment> sliceLineSegments;
    plane.set_distance(z0 + (float)i*layerThickness);
    for (size_t t{0}; t<meshingLoop.size(); ++t)
    {
        const Triangle &tempTriangle = meshingLoop[t];
        LineSegment tempSegment{};
        plane.set_distance(z0+(float)i*layerThickness);
        if (tempTriangle.intersect_plane(plane, tempSegment) == 0)
        {
            sliceLineSegments.push_back(tempSegment);
        }
    }
    slicedWithLineSegments->push_back(sliceLineSegments);
}

bool degenerate (Triangle triangle)
{
   if (triangle.v[0].distance_between(triangle.v[0], triangle.v[1]) < 0.000001)
   {
       return true;
   }
   if (triangle.v[1].distance_between(triangle.v[1], triangle.v[2]) < 0.000001)
   {
       return true;
   }
   if (triangle.v[2].distance_between(triangle.v[2], triangle.v[0]) < 0.000001)
   {
       return true;
   }
   return false;
}

int is_file_binary(const char *fileName)
{
    std::ifstream inFile(fileName);
    std::string firstLine{}, secondLine{};
    int invalidFile{-1};
    int ASCIIFile{1};
    int binaryFile{0};
    if (!inFile.good())
    {
        return invalidFile;
    }
    getline(inFile, firstLine);
    getline(inFile, secondLine);
    if(firstLine.find("solid") != std::string::npos && secondLine.find("facet")!=std::string::npos)
    {
        return ASCIIFile;
    }
    if(firstLine.find("xml")!=std::string::npos && secondLine.find("amf")!=std::string::npos)
    {
        return ASCIIFile;
    }
    return binaryFile;
}
