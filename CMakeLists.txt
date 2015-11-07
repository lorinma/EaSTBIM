cmake_minimum_required(VERSION 2.6)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
project(EaSTBIM)

ADD_LIBRARY(Excel STATIC
        excel/BasicExcel.cpp
        excel/BasicExcel.hpp
        excel/ExcelFormat.cpp
        excel/ExcelFormat.h
)

#compile ifcparse
file(GLOB IfcParse_Source_File ./ifcopenshell/src/ifcparse/*.cpp)
add_library(IfcParse SHARED ${IfcParse_Source_File})


# Find Open CASCADE header files and compile ifcgeom
find_package(OCE REQUIRED COMPONENTS TKPrim)
include_directories(${OCE_INCLUDE_DIRS})
set(OCE_LIBRARIES TKernel TKMath TKBRep TKGeomBase TKGeomAlgo TKG3d TKG2d TKShHealing TKTopAlgo TKMesh TKPrim TKBool TKBO TKFillet TKSTEP TKSTEPBase TKSTEPAttr TKXSBase TKSTEP209 TKIGES TKOffset)
file(GLOB IfcGeom_Source_File ./ifcopenshell/src/ifcgeom/*.cpp)
add_library(IfcGeom SHARED ${IfcGeom_Source_File})
target_link_libraries(IfcGeom IfcParse ${OCE_LIBRARIES})

find_package(ApproxMVBB)
include_directories(${ApproxMVBB_INCLUDE_DIRS})

#link pcl
find_package(PCL 1.7 REQUIRED)
include_directories(${PCL_INCLUDE_DIRS})
add_definitions(${PCL_DEFINITIONS})
link_directories(${PCL_LIBRARY_DIRS})

#link fcl,libccd,octomap
find_package(octomap REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(CCD ccd)
pkg_check_modules(FCL fcl)
include_directories(${OCTOMAP_INCLUDE_DIRS} ${CCD_INCLUDE_DIRS} ${FCL_INCLUDE_DIRS})
link_directories(${OCTOMAP_LIBRARY_DIRS} ${CCD_LIBRARY_DIRS} ${FCL_LIBRARY_DIRS})

include_directories(./ifcopenshell/src)
set(SOURCE_FILES main.cpp IO.cpp IO.h BIM.cpp BIM.h Geometry.cpp Geometry.h Visualizer.cpp Visualizer.h Topology.cpp Topology.h Transform.cpp Transform.h)
add_executable(EastBIM ${SOURCE_FILES})
target_link_libraries(EastBIM ${OCTOMAP_LIBRARIES} ${CCD_LIBRARIES} ${FCL_LIBRARIES} ${PCL_LIBRARIES} ${ApproxMVBB_LIBRARY_REL} ${FCL_LIBRARIES} ${ApproxMVBB_LIBRARY_DGB} ${ApproxMVBB_LIBRARIES} IfcParse IfcGeom TKernel TKMath TKBRep TKGeomBase TKGeomAlgo TKG3d TKG2d TKShHealing TKTopAlgo TKMesh TKPrim TKBool TKBO TKFillet Excel)


