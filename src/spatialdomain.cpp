#include <sstream>
#include <iostream>
#include <cmath>
#include <exception>
#include <algorithm>
#include "../include/spatialdomain.hpp"

SpatialDom::SpatialDom(std::string filepath) : 
m_matType{CV_32FC1},
m_filepath{filepath},
m_blockSize{8.0f}
{   
    if(validFileformat() == true){
        m_sourceImg = cv::imread(m_filepath.c_str(), 0);
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
    /**
     * Determines the blockiness, a measure describing differences between
     * compression block borders. All compression blocks (8x8 pixels) are 
     * compared to their neighbours. Differences along the borders are summed 
     * up horizontaly and verticaly. 
     */

    float totalHorizontalDiff = 0.0f;
	float totalVerticalDiff = 0.0f;

	unsigned int H_boundaryNum = floor(m_sourceImg.cols / m_blockSize) - 1;
	unsigned int V_boundaryNum = floor(m_sourceImg.rows / m_blockSize) - 1;

    for (unsigned int i = 1; i < m_sourceImg.rows; i++){
        for (unsigned int j = 1; j < floor(m_sourceImg.cols / m_blockSize); j++){
            totalHorizontalDiff += abs(horizontalDifference(i, j * m_blockSize));
        }
    }

    for (unsigned int i = 1; i < floor(m_sourceImg.rows / m_blockSize); i++){
        for (unsigned int j = 1; j < m_sourceImg.cols; j++){
            totalVerticalDiff += abs(verticalDifference(i * m_blockSize, j));
        }
    }
    m_H_blockiness = totalHorizontalDiff / ((float) m_sourceImg.rows * ((float) H_boundaryNum - 1));
    m_V_blockiness = totalVerticalDiff / ((float) m_sourceImg.cols * ((float) V_boundaryNum - 1));
}

void SpatialDom::activityMeasure(){
    /**
     *  Determines the horizontal and vertical activity within compresion blocks,
     *  to estimates the amount of blur within the compression blocks. This is done
     *  both horizontaly and verticaly.
     */

    float totalHorizontalDiff = 0.0f;
    float totalVerticalDiff = 0.0f;
    
    for (unsigned int i = 1; i < m_sourceImg.rows; i++) {
        for (unsigned int j = 1; j < m_sourceImg.cols; j++) {
            if (j < m_sourceImg.cols - 1)
                totalHorizontalDiff += abs(horizontalDifference(i, j));
            if (i < m_sourceImg.rows - 1)
                totalVerticalDiff += abs(verticalDifference(i, j));
        }
    }
    m_H_activity = (1 / (m_blockSize - 1)) * ((m_blockSize / ((float) m_sourceImg.rows * ((float) m_sourceImg.cols - 1)) * totalHorizontalDiff) - m_H_blockiness);
    m_V_activity = (1 / (m_blockSize - 1)) * ((m_blockSize / ((float) m_sourceImg.cols * ((float) m_sourceImg.rows - 1)) * totalVerticalDiff) - m_V_blockiness);
}

void SpatialDom::zeroCrossing(){
    /**
     * Determines the Zero crossing rate, being the amount of differences withing
     * the image. This is done both horizontaly and verticaly.
     */

	unsigned int H_ZCSum = 0;
	unsigned int V_ZCSum = 0;
	
	for (unsigned int i = 1; i < m_sourceImg.rows; i++) {
		for (unsigned int j = 1; j < m_sourceImg.cols; j++) {

            if (horizontalDifference(i, j) > 0 && j < m_sourceImg.cols - 2){
                H_ZCSum += 1;
			}
            if (verticalDifference(i, j) > 0 && i < m_sourceImg.rows - 2){
                V_ZCSum += 1;
			}
		}
	}
    m_H_zerocross = (float) H_ZCSum / (float) m_sourceImg.rows * ((float) m_sourceImg.cols - 2);
    m_V_zerocross = (float) V_ZCSum / (float) m_sourceImg.cols * ((float) m_sourceImg.rows - 2);
}

float SpatialDom::horizontalDifference(int i, int j){
    /**
     * Determines horizontal difference between two pixels
     */
    float d_h = m_sourceImg.ptr<float>(i)[j] - m_sourceImg.ptr<float>(i)[j - 1];
    return d_h;
}

float SpatialDom::verticalDifference(int i, int j){
    /**
     * Determines vertical difference between two pixels
     */
    float d_v = m_sourceImg.ptr<float>(i)[j] - m_sourceImg.ptr<float>(i-1)[j];
    return d_v;
}

float SpatialDom::assessQuality(){
    /**
     * calls each quality meassure and estimates the overall quality estimate by
     * computing a weighted sum of all horizantal and vertical measurements. If no
     * blocks are detected, no compression is detected and quality estimation is 
     * pointless. If no activity is detected (all blocks are uniform color), quality
     * estimation is pointless.
     */

	blockinesMeasure();
	activityMeasure();
	zeroCrossing();

    float D = (m_H_blockiness + m_V_blockiness) / 2;
    float A = (m_H_activity + m_V_activity) / 2;
    float Z = (m_H_zerocross + m_V_zerocross) / 2;

    if (D == 0){
        std::cout << "\nNo blocks - caused by jpeg compression - detected.\n" << std::endl;
        throw std::exception();
    }
    else if(A < 0){
        std::cout << "\nNo activity in blocks - caused by jpeg compression - detected.\n"<< std::endl;
        A = 0.0f;
    }
    else{
        printf("horizontal blokiness: %f, vertiacal blokiness: %f \n", m_H_blockiness, m_V_blockiness);
        printf("horizontal activity: %f, vertiacal activity: %f \n", m_H_activity, m_V_activity);
        printf("horizontal zeroCrossing: %f, vertiacal zeroCrossing: %f \n", m_H_zerocross, m_V_zerocross);
    }

    float alpha = -245.9f;
    float beta = 261.9f;
    float gamma1 = -0.0240f;
    float gamma2 = 0.0160f;
    float gamma3 = 0.0054f;


    return (alpha + beta * pow(D, gamma1) * pow(A, gamma2) * pow(Z, gamma3));
}

void SpatialDom::saveImg(cv::Mat img, std::string filename){
    /** 
     * overloaded convenience function to save an image.
     */
    
    size_t splitPoint;
	splitPoint = m_filepath.find_last_of("/\\");
	m_directory = m_filepath.substr(0, splitPoint);
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
    /** 
     * convenience function to save an image 
     */
    size_t splitPoint;
	splitPoint = m_filepath.find_last_of("/\\");
	m_directory = m_filepath.substr(0, splitPoint);
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
    /**
     * simply checks file suffix. If file is not .jpeg or .jpg 
     * image is not suitable for quaqlity assesment.
     */

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