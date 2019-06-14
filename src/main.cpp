#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <opencv2/opencv.hpp>
#include "../include/spatialdomain.hpp"

int main(int argc, char **argv) {

    // std::cout << "Major version : " << CV_MAJOR_VERSION << std::endl;
    // std::cout << "Minor version : " << CV_MINOR_VERSION << std::endl;
    // std::cout << "OpenCV version : " << CV_VERSION << std::endl;
    // std::cout << "Subminor version : " << CV_SUBMINOR_VERSION << std::endl;
    // std::cout << "Build info : " << cv::getBuildInformation().c_str() << std::endl;

    if (argc != 2){
        printf("usage: $./Quality <Image_Path>\n");
        return -1;
    }

    try {
        SpatialDom s(argv[1]);
        s.activityMeasure();
        //s.saveImg("test.jpg");
    }
    catch (const std::exception &){
        std::cout << "exiting application." << std::endl;
        return -1;
    }
   
    return 0;
}