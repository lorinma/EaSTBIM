cmake_minimum_required(VERSION 3.0)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
project(EaSTBIM)

#compile ifcparse
file(GLOB IfcParse_Source_File ./ifcopenshell/src/ifcparse/*.cpp)
add_library(IfcParse SHARED ${IfcParse_Source_File})

#compile ifcgeom
## Find Open CASCADE header files
find_package(OCE REQUIRED COMPONENTS TKPrim)
include_directories(${OCE_INCLUDE_DIRS})
set(OCE_LIBRARIES TKernel TKMath TKBRep TKGeomBase TKGeomAlgo TKG3d TKG2d TKShHealing TKTopAlgo TKMesh TKPrim TKBool TKBO TKFillet TKSTEP TKSTEPBase TKSTEPAttr TKXSBase TKSTEP209 TKIGES TKOffset)
file(GLOB IfcGeom_Source_File ./ifcopenshell/src/ifcgeom/*.cpp)
add_library(IfcGeom SHARED ${IfcGeom_Source_File})
target_link_libraries(IfcGeom IfcParse ${OCE_LIBRARIES})

#link pcl
find_package(PCL 1.7 REQUIRED)
include_directories(${PCL_INCLUDE_DIRS})
add_definitions(${PCL_DEFINITIONS})
link_directories(${PCL_LIBRARY_DIRS})

include_directories(./ifcopenshell/src)
set(SOURCE_FILES main.cpp IO.cpp IO.h BIM.cpp BIM.h Geometry.cpp Geometry.h Visualizer.cpp Visualizer.h)
add_executable(EastBIM ${SOURCE_FILES})
target_link_libraries(EastBIM ${PCL_LIBRARIES} IfcParse IfcGeom TKernel TKMath TKBRep TKGeomBase TKGeomAlgo TKG3d TKG2d TKShHealing TKTopAlgo TKMesh TKPrim TKBool TKBO TKFillet)
