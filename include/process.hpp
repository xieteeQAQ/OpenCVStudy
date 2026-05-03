#pragma once

#include <iostream>
#include <opencv2/opencv.hpp>
#include "../include/func.hpp"

void process(const cv::Mat &input, cv::Mat &output);

void createTrackbars();

void putTexts(cv::Mat &input, double &time);

void showEorrorImg(cv::Mat falseImg);

void colorRecognize(const cv::Mat &input, cv::Mat &output);

void putSettingTexts(cv::Mat &input, std::string text, const double fontScale, const int thickness, const int condition, int rowNum);

int keyCheck(const cv::Mat &img, cv::VideoWriter &writer, const int &key, double &now);