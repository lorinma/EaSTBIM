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
//    if(count>=1)
//        cout<<"element: has "<<boost::lexical_cast<string>(count)<<" shells"<<endl;
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
//    if(count>=1)
//        cout<<"element: has "<<boost::lexical_cast<string>(count)<<" faces"<<endl;
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
//    if(count>=1)
//        cout<<"element: has "<<boost::lexical_cast<string>(count)<<" vertices"<<endl;
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

bool Geometry::GetMVBB(const Geometry::VertexSet &vertices, Box &box) {
    ApproxMVBB::Vector3List v;
    for (Geometry::VertexSet::const_iterator it = vertices.begin(); it!=vertices.end();++it){
        pcl::PointXYZ p;
        Vertex2Point(*it,p);
        v.emplace_back(p.x,p.y,p.z);
    }
    ApproxMVBB::Matrix3Dyn points(3,v.size());
    for(int i=0;i<v.size();i++)
        points.col(i)=v[i];
    //NOTE parameters see:https://github.com/gabyx/ApproxMVBB
    ApproxMVBB::OOBB oobb = ApproxMVBB::approximateMVBB(points,0.001,8,5,0,5);
    Eigen::Vector3f centroid(
            (const float &) ((oobb.m_minPoint.x()+oobb.m_maxPoint.x())/2),
            (const float &) ((oobb.m_minPoint.y()+oobb.m_maxPoint.y())/2),
            (const float &) ((oobb.m_minPoint.z()+oobb.m_maxPoint.z())/2));
    //upper/lower point in OOBB frame
    double width = oobb.m_maxPoint.x()-oobb.m_minPoint.x();
    double height = oobb.m_maxPoint.y()-oobb.m_minPoint.y();
    double depth = oobb.m_maxPoint.z()-oobb.m_minPoint.z();
    if (width<=0 || height<=0 ||depth<=0)
        return false;
//    coordinate transformation A_IK matrix from OOBB frame K to world frame I
    Eigen::Quaternionf q;
    q.x()= (float) oobb.m_q_KI.x();
    q.y()= (float) oobb.m_q_KI.y();
    q.z()= (float) oobb.m_q_KI.z();
    q.w()= (float) oobb.m_q_KI.w();
    centroid=q.matrix()*centroid;
//    a translation to apply to the cube from 0,0,0
    box.centroid=centroid;
//    a quaternion-based rotation to apply to the cube
    box.quanternion=q.inverse();
    box.depth=depth;
    box.height=height;
    box.width=width;
    return true;
}

Box::Box() {

}

bool Geometry::GetMVBB(const TopoDS_Shape &brep, Box &box) {
    VertexSet vertices;
    if (GetVertices(brep,vertices)== false)
        return false;
    return GetMVBB(vertices,box);
}

void Geometry::Face2BVHMesh(const TopoDS_Face &face, BVHMeshPtr model) {
    TopLoc_Location loc;
    Handle_Poly_Triangulation tri = BRep_Tool::Triangulation(face,loc);
    if ( ! tri.IsNull() ) {
        const TColgp_Array1OfPnt& nodes = tri->Nodes();
// set mesh triangles and vertice indices
        std::vector<fcl::Vec3f> vertices;
        //index from 1
        for (int i=1;i<=nodes.Length();i++){
            fcl::Vec3f v(nodes(i).X(),nodes(i).Y(),nodes(i).Z());
            vertices.push_back(v);
        }
        const Poly_Array1OfTriangle& triangleInices = tri->Triangles();
// code to set the vertices and triangles
        std::vector<fcl::Triangle> triangles;
        for (int i=1;i<=triangleInices.Length();i++){
            int i1=0, i2=0, i3=0;
            triangleInices(i).Get(i1,i2,i3);
            fcl::Triangle t(i1,i2,i3);
            triangles.push_back(t);
        }
        model->addSubModel(vertices, triangles);
    }

}

void Geometry::Shape2BVHMesh(const TopoDS_Shape &shape, BVHMeshPtr model) {
    model->beginModel();
    BRepMesh_IncrementalMesh(shape, IfcGeom::GetValue(IfcGeom::GV_DEFLECTION_TOLERANCE));
    FaceSet faces;
    GetFaces(shape,faces);
    for (auto face=faces.begin();face!=faces.end();++face){
        Face2BVHMesh(*face,model);
    }
    model->endModel();
}
