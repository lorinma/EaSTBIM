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

#include "Geometry.h"
Geometry::Geometry() {

}

bool Geometry::GetShells(const TopoDS_Shape &brep, Geometry::ShellSet &shells) {
    TopExp_Explorer Ex;
    int count=0;
    for (Ex.Init(brep,TopAbs_SHELL); Ex.More(); Ex.Next()) {
        shells.push_back(new TopoDS_Shell);
        shells.at(shells.size()-1)= TopoDS::Shell(Ex.Current());
        count++;
    }
    if(count>=1)
        cout<<"element: has "<<boost::lexical_cast<string>(count)<<" shells"<<endl;
    if(count < 1)
        cout<<"error! no shell is found in this building element"<<endl;
    return count>0;
}

bool Geometry::GetFaces(const TopoDS_Shape &brep, Geometry::FaceSet &faces) {
    TopExp_Explorer Ex;
    int count=0;
    for (Ex.Init(brep,TopAbs_FACE); Ex.More(); Ex.Next()) {
        faces.push_back(new TopoDS_Face);
        faces.at(faces.size()-1)= TopoDS::Face(Ex.Current());
        count++;
    }
    if(count>=1)
        cout<<"element: has "<<boost::lexical_cast<string>(count)<<" faces"<<endl;
    if(count < 1)
        cout<<"error! no face is found in this building element"<<endl;
    return count>0;
}

bool Geometry::GetVertices(const TopoDS_Shape &brep, Geometry::VertexSet &vertices) {
    TopExp_Explorer anExp(brep, TopAbs_WIRE);
    int count=0;
    for (; anExp.More(); anExp.Next()){
        const TopoDS_Wire& w = TopoDS::Wire(anExp.Current());
        BRepTools_WireExplorer Ex;
        for (Ex.Init(w); Ex.More(); Ex.Next()) {
            //FIXME ifcopenshell already re-order the vertices, so no need to check the orientation, just use the natrual sequence, it works in most of the cases, but some exception still exists, e.g., part of the wall in the turkey building
            vertices.push_back(new TopoDS_Vertex);
            vertices.at(vertices.size()-1)=TopoDS::Vertex(Ex.CurrentVertex());
            count++;
        }
    }
    if(count>=1)
        cout<<"element: has "<<boost::lexical_cast<string>(count)<<" vertices"<<endl;
    if(count < 1)
        cout<<"error! no vertex is found in this building element"<<endl;
    return count>0;
}

void Geometry::Vertex2Point(const TopoDS_Vertex &v, PointT& p) {
    gp_Pnt aPoint = BRep_Tool::Pnt(v);
    double x, y, z;
    aPoint.Coord(x, y, z);
    p.x=float(x);
    p.y=float(y);
    p.z=float(z);
}

void Geometry::Face2Polygon(const TopoDS_Face &f, pcl::PlanarPolygon<PointT>& poly) {
    VertexSet vertices;
    GetVertices(f,vertices);
    PointCloud cloud;
    for (VertexSet::iterator it=vertices.begin();it!=vertices.end();++it ){
        PointT p;
        Vertex2Point(*it,p);
        cloud.push_back(p);
    }
    poly.setContour(cloud);
}

void Geometry::Shape2Polygons(const TopoDS_Shape &s, Geometry::PolySet &polys) {
FaceSet faces;
    GetFaces(s,faces);
    pcl::PlanarPolygon<PointT> poly;
    for (FaceSet::iterator it = faces.begin();it!=faces.end();++it) {
        polys.push_back(new pcl::PlanarPolygon<PointT>);
        Face2Polygon(*it,poly);
        polys.at(polys.size()-1)=poly;
    }
}
