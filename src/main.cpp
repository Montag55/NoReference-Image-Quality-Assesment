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
        float quality = s.assessQuality();
        std::cout << "Estimated Quality: " << quality << std::endl;
    }
    catch (const std::exception &){
        std::cout << "exiting application." << std::endl;
        return -1;
    }

    return 0;
}