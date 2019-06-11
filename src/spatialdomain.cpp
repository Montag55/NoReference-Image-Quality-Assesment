#include <stdio.h>
#include <cmath>
#include "../include/spatialdomain.hpp"

SpatialDom::SpatialDom(std::string filepath):
m_directory {"./.."},
m_sourceImg { cv::imread(filepath.c_str(), 1)}
{   
    if (!m_sourceImg.data) {
        std::cout << "Error: no source image data." << std::endl;
    }
}

void SpatialDom::blockinesMeasure(){
    // TODO: XIN
}

void SpatialDom::activityMeasure(){
    // TODO: Lucas
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

void SpatialDom::saveImg(cv::Mat img, std::string filename)
{
    if (cv::imwrite(m_directory + "/" + filename, img))
    {
        std::cout << "Saved image to: " << m_directory << "/" << filename << std::endl;
    }
    else
    {
        std::cout << "Error: could not save image." << std::endl;
    }
}

void SpatialDom::saveImg(std::string filename)
{
    if (cv::imwrite(m_directory + "/" + filename, m_sourceImg))
    {
        std::cout << "Saved image to: " << m_directory << "/" << filename << std::endl;
    }
    else
    {
        std::cout << "Error: could not save image." << std::endl;
    }
}

SpatialDom::~SpatialDom() {}