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

#include <gp_Quaternion.hxx>
#include "Transform.h"

Transform::Transform(): geomtool(new Geometry){

}

void Transform::Translate(TopoDS_Shape &shape, const Eigen::Vector3f &t) {
    gp_Trsf trsf;
    trsf.SetTranslation(gp_Vec(t[0],t[1],t[2]));
    shape.Move(trsf);
}

void Transform::Move(TopoDS_Shape &shape, const Eigen::Affine3f &m) {
    gp_Trsf trsf;
    Eigen::Vector3f t = m.translation();
    Eigen::Quaternionf r = Eigen::Quaternionf(m.rotation());
    trsf.SetTranslation(gp_Vec(t[0],t[1],t[2]));
    trsf.SetRotation(gp_Quaternion(r.x(),r.y(),r.z(),r.w()));
    shape.Move(trsf);
}

void Transform::Rotate(TopoDS_Shape &shape, const Eigen::Quaternionf &r) {
    gp_Trsf trsf;
    trsf.SetRotation(gp_Quaternion(r.x(),r.y(),r.z(),r.w()));
    shape.Move(trsf);
}

void Transform::Rotate(TopoDS_Shape &shape, const Eigen::Matrix3f &r) {
    Eigen::Quaternionf q = Eigen::Quaternionf(r);
    Rotate(shape,q);
}
