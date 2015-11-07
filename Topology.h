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

//TODO collison test after transform

#ifndef EASTBIM_TOPOLOGY_H
#define EASTBIM_TOPOLOGY_H

#include "Geometry.h"
//#include <fcl/collision_object.h>
#include <fcl/collision_node.h>
#include <fcl/collision.h>
#include "fcl/BV/BV.h"
#include "fcl/shape/geometric_shapes.h"
#include "fcl/narrowphase/narrowphase.h"
#include "fcl/traversal/traversal_node_bvhs.h"
#include "fcl/traversal/traversal_node_setup.h"
class Topology {
public:
    typedef boost::shared_ptr<Topology> Ptr;
    Geometry::Ptr geomtool;
    Topology();
    bool Collide(const TopoDS_Shape& shape1,const TopoDS_Shape& shape2);
};


#endif //EASTBIM_TOPOLOGY_H
