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
// Created by ling on 19/10/15.
//

#include "IO.h"
#include "Visualizer.h"
#include "Topology.h"
#include "Transform.h"

using namespace std;
int main (int argc, char** argv)
{
    IO data;
    boost::ptr_vector<string> ifcfiles;
    data.GetIfcFiles(ifcfiles);
    BIM::Ptr bim(new BIM);
    data.LoadIfcModel(ifcfiles.at(0),bim);

    Transform::Ptr move(new Transform);
    move->Translate(bim->elements.at(0).shape,Eigen::Vector3f(1,1,0));


    Topology::Ptr topo(new Topology);
    cout<<topo->Collide(bim->elements.at(0).shape,bim->elements.at(0).shape_original);

//    Visualizer viewer;
////    for (BIM::Element_set::iterator it=bim->elements.begin();it!=bim->elements.end();++it){
////        Box box;
////        it->GetMVBB(box);
////        viewer.AddTopoShapeWithProperty(it->shape);
////        viewer.AddBoxWithProperty(box,255);
////    }
////    viewer.spin();
////
//viewer.AddTopoShapeWithProperty(bim->elements.at(0).shape);
//    viewer.AddTopoShapeWithProperty(bim->elements.at(0).shape_original,255);
//    viewer.spin();

//    PointCloudPtr cloud(new PointCloud);
//    data.ReadPts("damaged beam.pts",cloud);
//    viewer.addPointCloudColor<pcl::PointXYZ>(cloud);

//    data.ReadIfc("house.ifc");
}
