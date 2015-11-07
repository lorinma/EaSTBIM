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

#include "Topology.h"

Topology::Topology():geomtool(new Geometry) {

}

bool Topology::Collide(const TopoDS_Shape &shape1, const TopoDS_Shape &shape2) {
    Geometry::BVHMeshPtr m1(new Geometry::BVHMesh);
    Geometry::BVHMeshPtr m2(new Geometry::BVHMesh);
    geomtool->Shape2BVHMesh(shape1,m1);
    geomtool->Shape2BVHMesh(shape2,m2);
    // Given two objects o1 and o2
    fcl::CollisionObject* o1(new fcl::CollisionObject(m1));
    fcl::CollisionObject* o2(new fcl::CollisionObject(m2));
// set the collision request structure, here we just use the default setting
    fcl::CollisionRequest request;
// result will be returned via the collision result structure
    fcl::CollisionResult result;
// perform collision test
    fcl::collide(o1, o2, request, result);
    return result.isCollision();
}


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