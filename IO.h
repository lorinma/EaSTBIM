//
// Created by ling on 19/10/15.
//

#ifndef EASTBIM_IO_H
#define EASTBIM_IO_H

#include "pcl/point_types.h"
#include "pcl/point_cloud.h"
#include <iostream>
#include <fstream>
using namespace std;
using std::ios;
using std::ifstream;
typedef pcl::PointXYZ PointT;
typedef pcl::PointCloud<PointT> PointCloud;
typedef PointCloud::Ptr PointCloudPtr;

namespace EastBIM
{
    class IO {
    public:
        IO();
        void ReadPts(string filename, PointCloudPtr cloud);
    };
}


#endif //EASTBIM_IO_H
