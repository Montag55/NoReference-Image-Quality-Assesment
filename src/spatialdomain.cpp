#include <sstream>
#include <iostream>
#include <cmath>
#include <exception>
#include "../include/spatialdomain.hpp"

SpatialDom::SpatialDom(std::string filepath) : 
m_directory{"./.."},
m_matType{CV_32FC3},
m_filepath{filepath},
m_blockSize{8}
{   
    if(validFileformat() == true){
        m_sourceImg = cv::imread(m_filepath.c_str(), 1);
    }
    else{
        std::cout << "Error: image is not a JPEG." << std::endl;
        throw std::exception();
    }
    
    if (!m_sourceImg.data) {
        std::cout << "\nError: no source image data.\n" << std::endl;
        throw std::exception();
    }

    // convert to 32bit float instead of 8bit pixel
    m_sourceImg.convertTo(m_sourceImg, m_matType);
    // convert it to single channel, monochrome
    cvtColor(m_sourceImg, m_sourceImg, 6);
}

void SpatialDom::blockinesMeasure(){
    // TODO: XIN
}

void SpatialDom::activityMeasure(){
    
    float totalHorizontalDiff = 0.0f;
    float totalVerticalDiff = 0.0f;
    
    for (unsigned int i = 1; i < m_sourceImg.rows; i++) {
        float *ptr = m_sourceImg.ptr<float>(i);
        for (unsigned int j = 1; j < m_sourceImg.cols; j++) {
            if (j < m_sourceImg.cols - 1)
                totalHorizontalDiff += abs(horizontalDifference(i, j));
            if (i < m_sourceImg.rows - 1)
                totalVerticalDiff += abs(verticalDifference(i, j));
        }
    }

    m_H_activity = (1 / (m_blockSize - 1)) * ((m_blockSize / (m_sourceImg.rows * (m_sourceImg.cols - 1)) * totalHorizontalDiff) - m_H_blockiness);
    m_V_activity = (1 / (m_blockSize - 1)) * ((m_blockSize / (m_sourceImg.cols * (m_sourceImg.rows - 1)) * totalVerticalDiff) - m_V_blockiness);
}

void SpatialDom::zeroCrossing(){
    // TODO: Whos fastes
}

float SpatialDom::horizontalDifference(int i, int j){
    float d_h = m_sourceImg.ptr<float>(i)[j] - m_sourceImg.ptr<float>(i)[j - 1];
    return d_h;
}

float SpatialDom::verticalDifference(int i, int j){
    float d_v = m_sourceImg.ptr<float>(i)[j] - m_sourceImg.ptr<float>(i-1)[j];
    return d_v;
}

float SpatialDom::assesQuality(){
    float D = (m_H_blockiness + m_V_blockiness) / 2;
    float A = (m_H_activity + m_V_activity) / 2;
    float Z = (m_H_zerocross + m_V_zerocross) / 2;
    
    float alpha = -245.9f;
    float beta = 261.9f;
    float gamma1 = -0.0240f;
    float gamma2 = 0.0160f;
    float gamma3 = 0.0054f;

    return (alpha + beta * pow(D, gamma1) * pow(A, gamma2) * pow(Z, gamma3));
}

void SpatialDom::saveImg(cv::Mat img, std::string filename){
    if (cv::imwrite(m_directory + "/" + filename, img))
    {
        std::cout << "Saved image to: " << m_directory << "/" << filename << std::endl;
    }
    else
    {
        std::cout << "Error: could not save image to: " << m_directory << "/" << filename << "." << std::endl;
        throw std::exception();
    }
}

void SpatialDom::saveImg(std::string filename){
    if (cv::imwrite(m_directory + "/" + filename, m_sourceImg))
    {
        std::cout << "Saved image to: " << m_directory << "/" << filename << std::endl;
    }
    else
    {
        std::cout << "Error: could not save image to: " << m_directory << "/" << filename << "." << std::endl;
        throw std::exception();
    }
}

bool SpatialDom::validFileformat(){
    std::string fileformat;
    std::stringstream ss(m_filepath);
    std::string token;

    while (std::getline(ss, token, '.')){
        fileformat = token;
    }

    if(fileformat == "jpg" || fileformat == "jpeg"){
        return true;
    }

    return false;
}

SpatialDom::~SpatialDom() {}