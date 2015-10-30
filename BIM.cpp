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

#include "BIM.h"

BIM::BIM() {

}

BldElement::BldElement() {

}

BldElement::BldElement(int id, string guid, string name, string type,
                       const IfcGeomObjects::IfcGeomShapeModelObject *o):id(id),guid(guid),name(name),type(type),geomtool(new Geometry){
    BRep_Builder builder;
    builder.MakeCompound(shape);
    for (IfcGeom::IfcRepresentationShapeItems::const_iterator it = o->mesh().begin(); it != o->mesh().end(); ++ it) {
        TopoDS_Shape brep = it->Shape();
        gp_Trsf trsf = it->Placement().Trsf();
        brep.Move(trsf);
//        FIXME are the shells in the shape fixed by ifcopenshell?
        builder.Add(shape,brep);
    }
}

bool BldElement::GetShells(Geometry::ShellSet &shells) {
    return geomtool->GetShells(shape,shells);
}

bool BldElement::GetFaces(Geometry::FaceSet &faces) {
    return geomtool->GetFaces(shape,faces);
}
