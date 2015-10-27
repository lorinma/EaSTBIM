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
// Created by ling on 27/10/15.
//

#ifndef EASTBIM_GEOMETRY_H
#define EASTBIM_GEOMETRY_H

#include <boost/smart_ptr/shared_ptr.hpp>
#include "boost/ptr_container/ptr_vector.hpp"
#include "TopoDS.hxx"
#include <iostream>
using namespace std;
namespace EastBIM {
    class Geometry {
    public:
        typedef boost::shared_ptr<Geometry> Ptr;
        typedef vector<TopoDS_Shell> ShellSet;
        Geometry();
        bool GetShells(const TopoDS_Shape& brep, ShellSet& shells);
    };
}


#endif //EASTBIM_GEOMETRY_H
