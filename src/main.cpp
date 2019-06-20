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

    /*if (argc != 2){
        printf("usage: $./Quality <Image_Path>\n");
        return -1;
    }

    try {
		std::cout << "Please input image for assessment:" << std::endl;
		std::string filePath;
		std::cin >> filePath;
        SpatialDom s(filePath);
        s.activityMeasure();
        s.saveImg("test.jpg");
    }
    catch (const std::exception &){
        std::cout << "exiting application." << std::endl;
        return -1;
    }*/

	std::cout << "Please input image for assessment:" << std::endl;
	std::string filePath;
	std::cin >> filePath;
	SpatialDom s(filePath);
	std::cout << "Quality: " << s.assessQuality()<< std::endl;
	//s.saveImg("test.jpg");
	system("pause");

    return 0;
}