#pragma once

#include <opencv2/opencv.hpp>
#include <string>


constexpr int IMAGE = 0;
constexpr int VIDEO = 1;

namespace cv_color
{
    const cv::Scalar WHITE = cv::Scalar(255, 255, 255);
    const cv::Scalar BLACK = cv::Scalar(0, 0, 0);
    const cv::Scalar RED = cv::Scalar(0, 0, 255);
    const cv::Scalar ORANGE = cv::Scalar(0, 127, 255);
    const cv::Scalar YELLOW = cv::Scalar(0, 255, 255);
    const cv::Scalar GREEN = cv::Scalar(0, 255, 0);
    const cv::Scalar CYAN = cv::Scalar(255, 255, 0);
    const cv::Scalar BLUE = cv::Scalar(255, 0, 0);
    const cv::Scalar PURPLE = cv::Scalar(128, 0, 128);
}

extern std::string savePath;

extern int enCanny;
extern int enGray;
extern int enGaussianBlur;
extern int colorRecognition;

extern int blur_slider;
extern int sigma_slider;
extern int low;
extern int high;

extern int enHSV;
extern int h_min;
extern int h_max;
extern int s_min;
extern int s_max;
extern int v_min;
extern int v_max;
extern int areaSize;

extern bool shotDelay;
extern bool delayisStarted;
extern double shotStartTime;
extern double delaySeconds;

extern bool recording;
extern double FPS;
extern double recordStartTime;