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

#ifndef EASTBIM_VISUALIZER_H
#define EASTBIM_VISUALIZER_H

#include <iostream>
#include <pcl/visualization/pcl_visualizer.h>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <TopoDS_Face.hxx>
#include "Geometry.h"

using namespace std;
class Visualizer: public virtual pcl::visualization::PCLVisualizer{
private:
    Geometry::Ptr geomtool;
public:
    Visualizer();
    string GUID();

    template <typename PointT>
    bool AddPolygonWithProperty(const pcl::PlanarPolygon<PointT>& poly, double r=0.0, double g=0.0, double b=0.0, double size=1.0, string name="",int viewport=0){
        if (!name.length())
            name=GUID();
        setBackgroundColor(255,255,255);
        this->addPolygon<PointT>(poly,r,g,b,name,viewport);
        return this->setShapeRenderingProperties(pcl::visualization::PCL_VISUALIZER_LINE_WIDTH, size, name,viewport);
    }

    bool AddTopoShapeWithProperty(const TopoDS_Shape& shape, double r=0.0, double g=0.0, double b=0.0, double size=1.0, string name="",int viewport=0){
        Geometry::PolySet polys;
        geomtool->Shape2Polygons(shape,polys);
        for (Geometry::PolySet::iterator it=polys.begin();it!=polys.end();++it){
            AddPolygonWithProperty(*it,r,g,b,size,name,viewport);
        }
    }

    bool AddBoxWithProperty(const Box& shape, double r=0.0, double g=0.0, double b=0.0, double size=1.0, string name="",int viewport=0){
        if (!name.length())
            name=GUID();
        setBackgroundColor(255,255,255);
        this->addCube(shape.centroid,shape.quanternion,shape.width,shape.height,shape.depth,name,viewport);
        this->setShapeRenderingProperties(pcl::visualization::PCL_VISUALIZER_COLOR,r,g,b,name,viewport);
        return this->setShapeRenderingProperties(pcl::visualization::PCL_VISUALIZER_LINE_WIDTH, size, name,viewport);
    }
};


#endif //EASTBIM_VISUALIZER_H
