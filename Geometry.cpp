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

#include <TopExp_Explorer.hxx>
#include <ShapeFix_Shell.hxx>
#include <boost/lexical_cast.hpp>
#include "Geometry.h"

EastBIM::Geometry::Geometry() {

}

bool EastBIM::Geometry::GetShells(const TopoDS_Shape &brep, EastBIM::Geometry::ShellSet &shells) {
    int shellInx=0;
    TopExp_Explorer Ex;
    bool hasShell=false;
    //some shape has more than one shell and can be divided into shells
    for (Ex.Init(brep,TopAbs_SHELL); Ex.More(); Ex.Next()) {
        TopoDS_Shell crt_shell = TopoDS::Shell(Ex.Current());
        ShapeFix_Shell FixShell;
        FixShell.Init(crt_shell);
        FixShell.FixFaceOrientation(crt_shell);
        FixShell.Perform();

        if(FixShell.NbShells()>0){
            hasShell=true;
            if(FixShell.NbShells()>1){ //case that more than 1 shell is not occured in all the experiments
                TopExp_Explorer ExShls;
                TopoDS_Compound shellComp = TopoDS::Compound(FixShell.Shape());
                for (ExShls.Init(shellComp,TopAbs_SHELL); ExShls.More(); ExShls.Next()) {
                    shells.push_back(TopoDS::Shell(ExShls.Current()));
                    cout<<"      shell "<<boost::lexical_cast<string>(++shellInx)<<":"<<endl;
                }
            }
            else{
                TopoDS_Shell aShell = FixShell.Shell();
                shells.push_back(aShell);
                cout<<"      shell "<<boost::lexical_cast<string>(++shellInx)<<":"<<endl;

            }
        }
    }
    return hasShell;
}
