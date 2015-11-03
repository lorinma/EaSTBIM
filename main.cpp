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
//TODO operator class check relation
//TODO convert topo to mesh

//#include <fcl/shape/geometric_shapes.h>
//#include <fcl/shape/geometric_shapes_utility.h>
//#include <fcl/narrowphase/narrowphase.h>
//#include <fcl/collision.h>
//#include <boost/foreach.hpp>

//using namespace fcl;
using namespace std;
int main (int argc, char** argv)
{
//    IO data;
//    boost::ptr_vector<string> ifcfiles;
//    data.GetIfcFiles(ifcfiles);
//    BIM::Ptr bim(new BIM);
//    data.LoadIfcModel(ifcfiles.at(0),bim);
//
//    Visualizer viewer;
//    for (BIM::Element_set::iterator it=bim->elements.begin();it!=bim->elements.end();++it){
//        Box box;
//        it->GetMVBB(box);
//        viewer.AddTopoShapeWithProperty(it->shape);
//        viewer.AddBoxWithProperty(box,255);
//    }
//    viewer.spin();
//

//    boost::shared_ptr<fcl::Box> box0(new fcl::Box(1,1,1));
//    boost::shared_ptr<fcl::Box> box1(new fcl::Box(1,1,1));
//    fcl::GJKSolver_libccd solver;
//    fcl::Vec3f contact_points;
//    fcl::FCL_REAL penetration_depth;
//    fcl::Vec3f normal;
//
//    fcl::Transform3f tf0, tf1;
//    tf0.setIdentity();
//    tf0.setTranslation(fcl::Vec3f(.9,0,0));
//    tf0.setQuatRotation(fcl::Quaternion3f(.6, .8, 0, 0));
//    tf1.setIdentity();
//
//    bool res = solver.shapeIntersect(*box0, tf0, *box1, tf1, &contact_points, &penetration_depth, &normal);
//
//    cout << "contact points: " << contact_points << endl;
//    cout << "pen depth: " << penetration_depth << endl;
//    cout << "normal: " << normal << endl;
//    cout << "result: " << res << endl;
//
//    static const int num_max_contacts = std::numeric_limits<int>::max();
//    static const bool enable_contact = true;
//    fcl::CollisionResult result;
//    fcl::CollisionRequest request(num_max_contacts,
//                                  enable_contact);
//
//
//    fcl::CollisionObject co0(box0, tf0);
//    fcl::CollisionObject co1(box1, tf1);
//
//    fcl::collide(&co0, &co1, request, result);
//    vector<fcl::Contact> contacts;
//    result.getContacts(contacts);
//
//    cout << contacts.size() << " contacts found" << endl;
//    BOOST_FOREACH(fcl::Contact& contact, contacts) {
//                    cout << "position: " << contact.pos << endl;
//                }

//    PointCloudPtr cloud(new PointCloud);
//    data.ReadPts("damaged beam.pts",cloud);
//    viewer.addPointCloudColor<pcl::PointXYZ>(cloud);

//    data.ReadIfc("house.ifc");
}
