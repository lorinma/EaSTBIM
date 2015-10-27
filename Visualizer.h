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
// Created by ling on 23/10/15.
//

#ifndef EASTBIM_VISUALIZER_H
#define EASTBIM_VISUALIZER_H

#include <iostream>
#include "pcl/visualization/pcl_visualizer.h"
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>

using namespace std;
namespace EastBIM {
    class Visualizer : public virtual pcl::visualization::PCLVisualizer {
    public:
        Visualizer();

        string GUID();

        template<typename PointT>
        bool addPointCloudColor(const typename pcl::PointCloud<PointT>::ConstPtr cloud, double r = 0.0, double g = 0.0,
                                double b = 0.0, double size = 1.0, string name = "", int viewport = 0);
    };
}



#endif //EASTBIM_VISUALIZER_H
