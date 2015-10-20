#include "IO.h"
int main (int argc, char** argv)
{
    EastBIM::IO data;
    PointCloudPtr cloud(new PointCloud);
    data.ReadPts("damaged beam.pts",cloud);
}
