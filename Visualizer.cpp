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

#include "Visualizer.h"

string EastBIM::Visualizer::GUID() {
    stringstream s;
    s << boost::uuids::random_generator()();
    return s.str();
}

template<typename PointT>
bool EastBIM::Visualizer::addPointCloudColor(const typename pcl::PointCloud<PointT>::ConstPtr cloud, double r, double g,
                                             double b, double size, string name, int viewport) {
    if (!name.length())
        name = GUID();
    setBackgroundColor(255, 255, 255);
    pcl::visualization::PointCloudColorHandlerCustom<PointT> color(cloud, r, g, b);
    addPointCloud<PointT>(cloud, color, name, viewport);
    return setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, size, name, viewport);
}

EastBIM::Visualizer::Visualizer() {

}
