#include <stdio.h>
#include <string>
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


    SpatialDom s(argv[1]);
    s.saveImg("test.jpg");
   
    return 0;
}