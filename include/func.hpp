#pragma once
#include <opencv2/opencv.hpp>
#include "../include/parameter.hpp"

bool isEmpty(cv::Mat& input);

cv::Mat getGray(const cv::Mat& input);

cv::Mat getHSV(const cv::Mat& input);

cv::Mat getBGR(const cv::Mat &input);

void saveImg(const cv::Mat &img);

std::string getSaveName(const int &type, const bool &putPrefix = 1);

std::string getSaveName(const std::string format, const bool &putPrefix = 1);

std::string getSaveName();