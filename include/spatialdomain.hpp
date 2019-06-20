#ifndef SPATIALDOMAIN_HPP
#define SPAIALDOMAIN_HPP

#include <string>
#include <vector>
#include <opencv2/opencv.hpp>


class SpatialDom{
public:
    SpatialDom(std::string filepath);
    ~SpatialDom();
    void saveImg(cv::Mat img, std::string filename);
    void saveImg(std::string filename);
    void blockinesMeasure();
    void activityMeasure();
    void zeroCrossing();
    float assessQuality();
    float horizontalDifference(int i, int j);
    float verticalDifference(int i, int j);
    bool validFileformat();

protected: 
    std::string m_directory;
    cv::Mat m_sourceImg;
    int m_matType;
    std::string m_filepath;
    int m_blockSize;

    float m_H_blockiness;
    float m_V_blockiness;
    float m_H_activity;
    float m_V_activity;
    float m_H_zerocross;
    float m_V_zerocross;
};

#endif
