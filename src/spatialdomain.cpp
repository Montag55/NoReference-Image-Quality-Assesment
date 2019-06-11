#include <stdio.h>
#include "../include/spatialdomain.hpp"

SpatialDom::SpatialDom(std::string filepath):
m_directory {""},
m_sourceImg { cv::imread(filepath.c_str(), 1)}
{   
    if (!m_sourceImg.data) {
        std::cout << "Error: no source image data." << std::endl;
    }

    m_resolution = cv::Point(m_sourceImg.rows, m_sourceImg.cols);
}

void SpatialDom::saveImg(cv::Mat img, std::string filename){
    if (cv::imwrite(m_directory + "/" + filename, img)){
        std::cout << "Saved image to: " << m_directory << "/" << filename << std::endl;
    }
    else{
        std::cout << "Error: could not save image." << std::endl;
    }
}

void SpatialDom::saveImg(std::string filename){
    if (cv::imwrite(m_directory + "/" + filename, m_sourceImg)){
        std::cout << "Saved image to: " << m_directory << "/" << filename << std::endl;
    }
    else{
        std::cout << "Error: could not save image." << std::endl;
    }
}

SpatialDom::~SpatialDom(){}