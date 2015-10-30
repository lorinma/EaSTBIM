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

#ifndef EASTBIM_BIM_H
#define EASTBIM_BIM_H

#include "Geometry.h"
#include <ifcgeom/IfcGeomObjects.h>
#include <BRep_Builder.hxx>

class BldElement{
private:
    Geometry::Ptr geomtool;
public:
    typedef boost::shared_ptr<BldElement> Ptr;
    int id;
    string guid;
    string name;
    string type;
    TopoDS_Compound shape;
    BldElement();
    BldElement(int id, string guid, string name, string type, const IfcGeomObjects::IfcGeomShapeModelObject* o);
    bool GetShells(Geometry::ShellSet& shells);
    bool GetFaces(Geometry::FaceSet& faces);
};
class BIM {
public:
    typedef boost::shared_ptr<BIM> Ptr;
    typedef boost::ptr_vector<BldElement> Element_set;
    Element_set elements;
    BIM();
};


#endif //EASTBIM_BIM_H
