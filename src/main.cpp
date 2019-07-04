#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <opencv2/opencv.hpp>
#include "../include/spatialdomain.hpp"

int main(int argc, char **argv) {

    if (argc != 2){
        printf("usage: $./Quality <Image_Path>\n");
        return -1;
    }

    try {
        SpatialDom s(argv[1]);
        std::cout << "Quality: " << s.assessQuality() << std::endl;
    }
    catch (const std::exception &){
        std::cout << "exiting application." << std::endl;
        return -1;
    }

	// std::cout << "Please input image for assessment:" << std::endl;
	// std::string filePath;
	// std::cin >> filePath;
	// SpatialDom s(filePath);
	// std::cout << "Quality: " << s.assessQuality()<< std::endl;
	// //s.saveImg("test.jpg");
	// system("pause");

    return 0;
}