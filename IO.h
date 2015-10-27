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
// Created by ling on 19/10/15.
//

#ifndef EASTBIM_IO_H
#define EASTBIM_IO_H

#include "pcl/point_types.h"
#include "pcl/point_cloud.h"
#include <pcl/io/pcd_io.h>
#include <iostream>
#include <fstream>
#include "ifcparse/IfcParse.h"
#include "BIM.h"

namespace EastBIM
{
    class IO {
        typedef pcl::PointXYZ PointT;
        typedef pcl::PointCloud<PointT> PointCloud;
        typedef PointCloud::Ptr PointCloudPtr;
        using std::ifstream;
    public:
        IO();
        bool LoadIfcModel(string filename, BIM::Ptr model);
        void IfcGeometrySetup();

        void ReadPts(string filename, PointCloudPtr cloud);
        void ReadIfc(string filename);
    };
}


#endif //EASTBIM_IO_H
