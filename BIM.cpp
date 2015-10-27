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
// Created by ling on 22/10/15.
//

#include "BIM.h"

EastBIM::BIM::BIM() {

}

EastBIM::BldElement::BldElement() {

}

EastBIM::BldElement::BldElement(int id, string guid, string name, string type,
                                const IfcGeomObjects::IfcGeomShapeModelObject *o):id(id),guid(guid),name(name),type(type),geomtool(new Geometry){
    BRep_Builder builder;
    builder.MakeCompound(compound);
    int count =0;
    for (IfcGeom::IfcRepresentationShapeItems::const_iterator it = o->mesh().begin(); it != o->mesh().end(); ++ it) {
        TopoDS_Shape shape = it->Shape();
        gp_Trsf trsf = it->Placement().Trsf();
        shape.Move(trsf);
//        shapes.push_back(shape);
//        builder.Add(compound,shape);
        geomtool->GetShells(shape,shells);
        count++;
    }
    if(count>=1)
        cout<<"element: "<<boost::lexical_cast<string>(id)<<" has "<<boost::lexical_cast<string>(count)<<" solids"<<endl;
    if(count < 1)
        cout<<"error! no solid is found in this building element"<<endl;
}
