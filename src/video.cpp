#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>
#include "../include/process.hpp"
#include "../include/mainProcess.hpp"
#include "../include/parameter.hpp"

cv::VideoCapture cap;
cv::VideoWriter writer;

int main()
{
#ifdef _WIN32
    std::cout << "运行平台 : WINDOWS\n";
#else
    std::cout << "运行平台 : MAC\n";
#endif
    std::cout << "程序开始运行\n";
    std::cout << "OpenCV Version : " << CV_VERSION << "\n";
    std::cout << "保存路径为 : " << savePath << '\n';

    createTrackbars();

#ifdef _WIN32
    cap.open(1);
#else
    cap.open(0);
#endif

    if (!cap.isOpened())
    {
        std::cout << "摄像头启动失败!\n";
        return -1;
    }

    startProcess(cap, writer);

    cv::destroyAllWindows();
    cap.release();
    writer.release();

    std::cout << "程序正常结束" << std::endl;
    return 0;
}