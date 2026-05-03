#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>
#include <vector>
#include "../include/func.hpp"
#include "../include/process.hpp"
#include "../include/parameter.hpp"

void onTrackbar(int value, void *data)
{
    int *var = static_cast<int *>(data);
    *var = value;
}

void process(const cv::Mat &input, cv::Mat &output)
{
    cv::Mat frame = input.clone();
    cv::Mat result = frame.clone();

    int k = blur_slider * 2 + 1;
    double sigma = static_cast<double>(sigma_slider) / 10.0;

    if (enHSV == 1)
    {
        cv::Mat mask;
        cv::Mat control;
        cv::Mat result_HSV;
        control = getHSV(frame).clone();
        cv::inRange(control,
                    cv::Scalar(h_min, s_min, v_min),
                    cv::Scalar(h_max, s_max, v_max),
                    mask);

        cv::bitwise_and(frame, frame, result_HSV, mask);
        result = result_HSV;
    }
    if (enGray == 1)
    {
        cv::cvtColor(result, result, cv::COLOR_BGR2GRAY);
    }
    if (enGaussianBlur == 1)
    {
        cv::GaussianBlur(result, result, cv::Size(k, k), sigma);
    }
    if (enCanny == 1)
    {
        cv::Mat edges;
        cv::Mat gray;
        gray = getGray(result);
        cv::Canny(gray, edges, low, high);
        result = edges;
    }

    output = result.clone();
}

void colorRecognize(const cv::Mat &input, cv::Mat &output)
{
    cv::Mat hsv = input.clone();
    cv::Mat result = hsv.clone();
    cv::Mat mask;

    if (hsv.channels() != 4)
        cv::cvtColor(hsv, hsv, cv::COLOR_BGR2HSV);

    std::vector<std::vector<cv::Point>> contours;
    cv::Scalar lower(h_min, s_min, v_min);
    cv::Scalar upper(h_max, s_max, v_max);

    cv::inRange(hsv, lower, upper, mask);
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5));
    cv::morphologyEx(mask, mask, cv::MORPH_OPEN, kernel);
    cv::morphologyEx(mask, mask, cv::MORPH_CLOSE, kernel);
    cv::GaussianBlur(mask, mask, cv::Size(5, 5), 0);
    cv::findContours(mask, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    for (auto &cnt : contours)
    {
        cv::Rect rect = cv::boundingRect(cnt);
        if (rect.area() < areaSize)
            continue;
        cv::rectangle(result, rect, cv_color::GREEN, 2);

        std::string text = "x : " + std::to_string(rect.x) + " y : " + std::to_string(rect.y);
        cv::putText(result, text,
                    cv::Point(rect.x - 10, rect.y - 10),
                    cv::FONT_HERSHEY_SIMPLEX,
                    0.5,
                    cv_color::GREEN,
                    1);
    }

    output = result.clone();
}

void createTrackbars()
{
    cv::namedWindow("result", cv::WINDOW_NORMAL);
    cv::namedWindow("control", cv::WINDOW_NORMAL);
    cv::resizeWindow("control", 600, 110);
    cv::moveWindow("result", 600, 150);

    cv::createTrackbar("GRAY : ", "control", NULL, 1, onTrackbar, &enGray);
    cv::createTrackbar("EDGE : ", "control", NULL, 1, onTrackbar, &enCanny);
    cv::createTrackbar("BLUR : ", "control", NULL, 1, onTrackbar, &enGaussianBlur);
    cv::createTrackbar("HSV : ", "control", NULL, 1, onTrackbar, &enHSV);
    cv::createTrackbar("COLORRCOG : ", "control", NULL, 1, onTrackbar, &colorRecognition);

    cv::createTrackbar("EDGE LOW : ", "control", NULL, 400, onTrackbar, &low);
    cv::createTrackbar("EDGE HIGH : ", "control", NULL, 400, onTrackbar, &high);
    cv::createTrackbar("BLUR CK : ", "control", NULL, 20, onTrackbar, &blur_slider);
    cv::createTrackbar("BLUR SIGMA : ", "control", NULL, 100, onTrackbar, &sigma_slider);

    cv::createTrackbar("H_MIN : ", "control", NULL, 179, onTrackbar, &h_min);
    cv::createTrackbar("H_MAX : ", "control", NULL, 179, onTrackbar, &h_max);
    cv::createTrackbar("S_MIN : ", "control", NULL, 255, onTrackbar, &s_min);
    cv::createTrackbar("S_MAX : ", "control", NULL, 255, onTrackbar, &s_max);
    cv::createTrackbar("V_MIN : ", "control", NULL, 255, onTrackbar, &v_min);
    cv::createTrackbar("V_MAX : ", "control", NULL, 255, onTrackbar, &v_max);
    cv::createTrackbar("AREASIZE : ", "control", NULL, 20000, onTrackbar, &areaSize);

    cv::setTrackbarPos("EDGE LOW : ", "control", low);
    cv::setTrackbarPos("EDGE HIGH : ", "control", high);
    cv::setTrackbarPos("BLUR CK : ", "control", blur_slider);
    cv::setTrackbarPos("BLUR SIGMA : ", "control", sigma_slider);
    cv::setTrackbarPos("colorRecognition : ", "control", colorRecognition);

    cv::setTrackbarPos("H_MIN : ", "control", h_min);
    cv::setTrackbarPos("H_MAX : ", "control", h_max);
    cv::setTrackbarPos("S_MIN : ", "control", s_min);
    cv::setTrackbarPos("S_MAX : ", "control", s_max);
    cv::setTrackbarPos("V_MIN : ", "control", v_min);
    cv::setTrackbarPos("V_MAX : ", "control", v_max);
    cv::setTrackbarPos("AREASIZE : ", "control", areaSize);
}

void putTexts(cv::Mat &input, double &now)
{
    double Setting_text_size = 1.0;
    int Setting_text_thickness = 2;

    std::string Setting_shotDelay_text = "Delayed Photo";
    putSettingTexts(input, Setting_shotDelay_text, Setting_text_size, Setting_text_thickness, shotDelay, 0);

    std::string Setting_colorRrcognize_text = "colorRrcognize";
    putSettingTexts(input, Setting_colorRrcognize_text, Setting_text_size, Setting_text_thickness, colorRecognition, 1);

    if (delayisStarted)
    {
        int count = 3 - (now - shotStartTime) + 1;
        int baseline = 0;
        if (count < 1)
            count = 1;
        std::string count_text = std::to_string(count);
        cv::Size Setting_shotDelay_textSize = cv::getTextSize(Setting_shotDelay_text + " : ON",
                                                              cv::FONT_HERSHEY_SIMPLEX,
                                                              Setting_text_size,
                                                              Setting_text_thickness,
                                                              &baseline);
        cv::putText(input,
                    count_text,
                    cv::Point(Setting_shotDelay_textSize.width + 45, 52),
                    cv::FONT_HERSHEY_SIMPLEX,
                    Setting_text_size + 0.1,
                    cv_color::RED,
                    Setting_text_thickness + 2);
    }

    if (recording)
    {
        double elapsed = now - recordStartTime;

        int hours = static_cast<int>(elapsed) / 360;
        int minutes = static_cast<int>(elapsed) / 60;
        int seconds = static_cast<int>(elapsed) % 60;

        std::string timeText;
        if (hours == 0)
            timeText = cv::format("%02d:%02d", minutes, seconds);
        else 
            timeText = cv::format("%02d:%02d:%02d", hours, minutes, seconds);
        std::string text = std::string("REC ") + timeText;

        int baseline = 0;
        cv::Size size = cv::getTextSize(text,
                        cv::FONT_HERSHEY_SIMPLEX,
                        Setting_text_size,
                        Setting_text_thickness,
                        &baseline
        );

        int x = input.cols - size.width - 20;
        int y = 40;

        cv::circle(input, cv::Point(x - 20, y - 10), 9, cv::Scalar(0,0,255), -1);
        cv::putText(input,
                    text,
                    cv::Point(x, y),
                    cv::FONT_HERSHEY_SIMPLEX,
                    Setting_text_size,
                    cv_color::WHITE,
                    Setting_text_thickness
        );
    }
}

void putSettingTexts(cv::Mat &input, std::string text, const double fontScale, const int thickness, const int condition, int rowNum)
{
    int baseline = 0;
    cv::Size size = cv::getTextSize(text,
                                    cv::FONT_HERSHEY_SIMPLEX,
                                    fontScale,
                                    thickness,
                                    &baseline);

    if (condition)
        text += " : ON";
    else
        text += " : OFF";
    cv::putText(input,
                text,
                cv::Point(30, 40 + (size.height * 2 * rowNum)),
                cv::FONT_HERSHEY_SIMPLEX,
                fontScale,
                cv_color::WHITE,
                thickness);
}

int keyCheck(const cv::Mat &img, cv::VideoWriter &writer, const int &key, double &now)
{
    if (key == 'q')
        return 1;
    else if (key == 's' && shotDelay == false)
    {
        saveImg(img);
    }
    else if (key == 's' && shotDelay == true)
    {
        delayisStarted = true;
        shotStartTime = now;
    }
    else if (key == 't')
    {
        if (shotDelay == false)
        {
            std::cout << "延时摄影已打开!\n";
            shotDelay = true;
        }
        else
        {
            std::cout << "延时摄影已关闭!\n";
            shotDelay = false;
        }
    }

    else if (key == 'r')
    {
        if (recording == false)
        {
            recordStartTime = cv::getTickCount() / cv::getTickFrequency();
            std::string name = getSaveName(VIDEO);
            recording = true;
            int fourcc = cv::VideoWriter::fourcc('m', 'p', '4', 'v');
            writer.open(savePath + '/' + name, fourcc, FPS, img.size());
            std::cout << "录像开始\n";
        }
    }
    else if (key == 'e')
    {
        if (recording == true)
        {
            recording = false;
            writer.release();
            std::cout << "录像结束\n";
        }
    }

    return 0;
}

void showEorrorImg(cv::Mat falseImg)
{
    int baseline = 0;
    std::string errorText = "There is something wrong with program QAQ";
    cv::Mat errorImg(falseImg.rows, falseImg.cols, CV_8UC1, cv_color::BLACK);
    cv::Size errorTextSize = cv::getTextSize(errorText,
                                             cv::FONT_HERSHEY_SIMPLEX,
                                             2,
                                             3,
                                             &baseline);
    cv::putText(errorImg,
                errorText,
                cv::Point(errorImg.cols / 2 - (errorTextSize.width / 2), errorImg.rows / 2),
                cv::FONT_HERSHEY_SIMPLEX,
                2,
                cv::Scalar(0, 0, 0),
                3);
    cv::imshow("result", errorImg);
}