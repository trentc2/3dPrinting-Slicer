cmake_minimum_required(VERSION 3.5)
project(Slicer_Final_Trenton_colton)

FIND_PACKAGE(Qt5 COMPONENTS GUI Widgets 3DRender 3DInput 3DExtras 3DCore Concurrent REQUIRED)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
SET(CMAKE_INCLUDE_CURRENT_DIR ON)

SET(CMAKE_AUTOMOC ON)
SET(CMAKE_AUTOUIC ON)
SET(CMAKE_AUTORCC ON)


add_executable(${PROJECT_NAME}
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindowutility.cpp
    mainwindowutility.h
    mainwindowform.ui
    myvector.cpp
    myvector.h
    plane.cpp
    plane.h
    slicer.cpp
    slicer.h
    linesegment.cpp
    linesegment.h
    triangle.cpp
    triangle.h
    trianglemesh.h
    trianglemesh.cpp
    trackballcameracontroller.cpp
    trackballcameracontroller.h
    models/models.qrc
)

target_link_libraries(${PROJECT_NAME}
    Qt5::Widgets
    Qt5::Gui
    Qt5::3DRender
    Qt5::3DCore
    Qt5::3DInput
    Qt5::3DExtras
    Qt5::Concurrent
)

FIND_PACKAGE(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})


add_executable(Slicer_Final_Trenton_colton_vector_unitTest
    MyVectorUnitTest.cpp
    )

target_link_libraries(Slicer_Final_Trenton_colton_vector_unitTest  ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES} Qt5::3DCore)

add_executable(Slicer_Final_Trenton_colton_plane_unitTest
   PlaneUnitTest.cpp
    )

target_link_libraries(Slicer_Final_Trenton_colton_plane_unitTest  ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES} Qt5::3DCore)

add_executable(Slicer_Final_Trenton_colton_LineSegment_unitTest
   LineSegmentUnitTest.cpp
    )

target_link_libraries(Slicer_Final_Trenton_colton_LineSegment_unitTest  ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES} Qt5::3DCore)

add_executable(Slicer_Final_Trenton_colton_Triangle_unitTest
   TriangleUnitTest.cpp
    )

target_link_libraries(Slicer_Final_Trenton_colton_Triangle_unitTest  ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES} Qt5::3DCore)

add_executable(Slicer_Final_Trenton_colton_TriangleMesh_unitTest
   TriangleMeshUnitTest.cpp
    )

target_link_libraries(Slicer_Final_Trenton_colton_TriangleMesh_unitTest  ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES} Qt5::3DCore)

add_executable(Slicer_Final_Trenton_colton_Slicer_unitTest
   SlicerUnitTest.cpp
    )

target_link_libraries(Slicer_Final_Trenton_colton_Slicer_unitTest  ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES} Qt5::3DCore)
