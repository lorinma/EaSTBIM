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
// Created by ling on 07/11/15.
//

#ifndef EASTBIM_TRANSFORM_H
#define EASTBIM_TRANSFORM_H

#include "Geometry.h"
class Transform {
public:
    Geometry::Ptr geomtool;
    typedef boost::shared_ptr<Transform> Ptr;
    Transform();
//TODO   decompose
    void Translate(TopoDS_Shape& shape, const Eigen::Vector3f& t);
    void Rotate(TopoDS_Shape& shape, const Eigen::Matrix3f& r);
    void Move(TopoDS_Shape& shape, const Eigen::Affine3f& m);
    void Rotate(TopoDS_Shape &shape, const Eigen::Quaternionf &r);
};


#endif //EASTBIM_TRANSFORM_H
