#include "../include/func.hpp"
#include "../include/parameter.hpp"
#include <iostream>
#include <ctime>
#include <string>

bool isEmpty(const cv::Mat &input)
{
    if (input.empty())
    {
        std::cout << "图片为空!\n";
        return true;
    }
    else
    {
        return false;
    }
}

cv::Mat getGray(const cv::Mat &input)
{
    cv::Mat gray;
    if (input.channels() == 1)
    {
        return input.clone();
    }
    else if (input.channels() == 3)
    {
        cv::cvtColor(input, gray, cv::COLOR_BGR2GRAY);
        return gray;
    }
    else if (input.channels() == 4)
    {
        cv::cvtColor(input, gray, cv::COLOR_HSV2BGR);
        return gray;
    }
    else
    {
        gray = input.clone();
    }
    return gray;
}

cv::Mat getHSV(const cv::Mat &input)
{
    cv::Mat HSV;
    if (input.channels() == 4)
    {
        return input.clone();
    }
    else if (input.channels() == 3)
    {
        cv::cvtColor(input, HSV, cv::COLOR_BGR2HSV);
        return HSV;
    }
    else
    {
        HSV = input.clone();
    }
    return HSV;
}

cv::Mat getBGR(const cv::Mat &input)
{
    cv::Mat BGR;
    if (input.channels() == 3)
    {
        return input.clone();
    }
    else if (input.channels() == 1)
    {
        cv::cvtColor(input, BGR, cv::COLOR_GRAY2BGR);
        return BGR;
    }
    else if (input.channels() == 4)
    {
        cv::cvtColor(input, BGR, cv::COLOR_HSV2BGR);
        return BGR;
    }
    else
    {
        BGR = input.clone();
    }
    return BGR;
}

void saveImg(const cv::Mat &img)
{
    std::string name = getSaveName(IMAGE);
    cv::imwrite(savePath + '/' + name, img);
    std::cout << "已保存图片 : " << name << "\n";
}

std::string getSaveName(const int &type, const bool &putPrefix)
{
    time_t now = time(0);
    std::string name = std::to_string(now);

    if (type == IMAGE)
    {
        if (putPrefix)
            name = "CVshot_" + name;
        name += ".jpg";
    }
    else if (type == VIDEO)
    {
        if (putPrefix)
            name = "CVrecord_" + name;
        name += ".mp4";
    }
    else
        std::cout << "储存类型错误!";
    return name;
}

std::string getSaveName(const std::string format, const bool &putPrefix)
{
    time_t now = time(0);
    std::string name = std::to_string(now);

    if (putPrefix)
        name = "CVshot_" + name;
    
    name += '.' + format;

    return name;
}

std::string getSaveName()
{
    return std::to_string(time(0));
}