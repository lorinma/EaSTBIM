/***************************************************************************
# *
# Copyright (c) 2015 *
# Ling Ma <bitly.com/cvlingma> *
# *
# This program is free software; you can redistribute it and/or modify *
# it under the terms of the GNU Lesser General Public License (LGPL) *
# as published by the Free Software Foundation; either version 2 of *
# the License, or (at your option) any later version. *
# for detail see the LICENCE text file. *
# *
# This program is distributed in the hope that it will be useful, *
# but WITHOUT ANY WARRANTY; without even the implied warranty of *
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the *
# GNU Library General Public License for more details. *
# *
# You should have received a copy of the GNU Library General Public *
# License along with this program; if not, write to the Free Software *
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 *
# USA *
# *
# **************************************************************************/

//
// Created by ling on 30/10/15.
//

#ifndef EASTBIM_GEOMETRY_H
#define EASTBIM_GEOMETRY_H

#include <TopoDS_Shell.hxx>
#include <TopoDS_Compound.hxx>
#include <boost/shared_ptr.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
#include <iostream>
#include <TopExp_Explorer.hxx>
#include <TopoDS.hxx>
#include <ShapeFix_Shell.hxx>
#include <boost/lexical_cast.hpp>
#include <pcl/geometry/planar_polygon.h>
#include <pcl/point_types.h>
#include <pcl/point_cloud.h>
#include <TopoDS_Face.hxx>
#include <BRepTools_WireExplorer.hxx>
#include <gp_Pnt.hxx>
#include <BRep_Tool.hxx>
#include "ApproxMVBB/ComputeApproxMVBB.hpp"

using namespace std;
class Box {
public:
    Eigen::Quaternionf quanternion;
    Eigen::Vector3f centroid;
    double width;
    double height;
    double depth;
    Box();
};

class Geometry {
public:
    typedef pcl::PointXYZ PointT;
    typedef pcl::PointCloud<PointT> PointCloud;
    typedef PointCloud::Ptr PointCloudPtr;
    typedef boost::shared_ptr<Geometry> Ptr;
    typedef boost::ptr_vector<TopoDS_Shell> ShellSet;
    typedef boost::ptr_vector<TopoDS_Face> FaceSet;
    typedef boost::ptr_vector<TopoDS_Vertex> VertexSet;
    typedef boost::ptr_vector<pcl::PlanarPolygon<PointT> > PolySet;

    Geometry();
    bool GetShells(const TopoDS_Shape &brep, ShellSet &shells);
    bool GetFaces(const TopoDS_Shape &brep, FaceSet &faces);
    bool GetVertices(const TopoDS_Shape &brep, VertexSet &vertices);
    void Vertex2Point(const TopoDS_Vertex &v, PointT& p);
    void Face2Polygon(const TopoDS_Face& f, pcl::PlanarPolygon<PointT>& poly);
    void Shape2Polygons(const TopoDS_Shape& s, PolySet& polys);
    bool GetMVBB(const VertexSet &vertices, Box& box);
    bool GetMVBB(const TopoDS_Shape &brep, Box& box);
};


#endif //EASTBIM_GEOMETRY_H
