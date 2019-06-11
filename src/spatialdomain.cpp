#include <sstream>
#include <iostream>
#include <cmath>
#include <exception>
#include "../include/spatialdomain.hpp"

SpatialDom::SpatialDom(std::string filepath) : 
m_directory{"./.."},
m_matType{CV_32FC3},
m_filepath{filepath}
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

    m_sourceImg.convertTo(m_sourceImg, m_matType);
}

void SpatialDom::blockinesMeasure(){
    // TODO: XIN
}

void SpatialDom::activityMeasure(){
    // iterates over picture tmp holds rgb channels
    // cv::Mat test = cv::Mat(m_sourceImg.rows, m_sourceImg.cols, m_matType, cv::Scalar(0, 0, 0));
    for (unsigned int row = 0; row < m_sourceImg.rows; row++) {
        cv::Vec3f *ptr = m_sourceImg.ptr<cv::Vec3f>(row);
        for (unsigned int col = 0; col < m_sourceImg.cols; col++) {
            cv::Vec3f tmp = cv::Vec3f(ptr[col][0], ptr[col][1], ptr[col][2]);     
        }
    }
}

void SpatialDom::zeroCrossing(){
    // TODO: Whos fastes
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