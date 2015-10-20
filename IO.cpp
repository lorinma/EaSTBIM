//
// Created by ling on 19/10/15.
//

#include <pcl/io/pcd_io.h>
#include "IO.h"

void EastBIM::IO::ReadPts(string filename,PointCloudPtr cloud) {
    //Read pts File
    ifstream inFile(filename, ios::in );
    int count,intensity,r,g,b;
    float px,py,pz;
    inFile >> count;
    while ( inFile >>  px >>  py >> pz >> intensity >> r >> g >> b ) //read each row
    {
        PointT basic_point;
        basic_point.x = px;
        basic_point.y = py;
        basic_point.z = pz;
        cloud->push_back(basic_point);
    }
    cloud->width = cloud->size();
    cloud->height= 1;
//    //Write to pcd file
//    pcl::io::savePCDFileASCII ("convertedPCD.pcd", *cloud);
//    cerr <<count<<" points, Saved " << cloud->size () << " data points to convertedPCD.pcd." << endl;
}

EastBIM::IO::IO() {

}
