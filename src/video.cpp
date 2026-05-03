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
    std::cout << "程序开始运行\n";
    std::cout << "OpenCV Version : " << CV_VERSION << "\n";
    std::cout << "保存路径为 : " << savePath << '\n';

    createTrackbars();

    cap.open(0);
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