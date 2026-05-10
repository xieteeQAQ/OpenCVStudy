#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>
#include <vector>
#include "../include/process.hpp"
#include "../include/mainProcess.hpp"
#include "../include/parameter.hpp"
#ifdef _WIN32
#include <windows.h>
#endif

// 以免忘记windows的编译操作
// 记得改路径
// 记得创建image
// cmake -B build -A x64 -DOpenCV_DIR="E:/opencv/build"
// cmake --build build --config Release

cv::VideoCapture cap;
cv::VideoWriter writer;

int main(int argc, char *argv[])
{
#ifdef _WIN32
    // 设置控制台输出为UTF-8
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    // 启用虚拟终端序列支持
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut != INVALID_HANDLE_VALUE)
    {
        DWORD dwMode = 0;
        if (GetConsoleMode(hOut, &dwMode))
        {
            dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
            SetConsoleMode(hOut, dwMode);
        }
    }
    std::cout << "运行平台 : WINDOWS\n";
#else
    std::cout << "运行平台 : MAC\n";
#endif
    std::cout << "程序开始运行\n";
    std::cout << "OpenCV Version : " << CV_VERSION << "\n";
    std::cout << "保存路径为 : " << savePath << '\n';

    createTrackbars();

#ifdef _WIN32
    cap.open(0);
#else
    cap.open(0);
#endif

    for (size_t i = 0; i < argc; i++)
    {
        std::string s = argv[i];
        
        if (s == "-debug")
        {
            std::cout << "摄像头画面宽度 : " << cap.get(cv::CAP_PROP_FRAME_WIDTH) << "\n";
            std::cout << "摄像头画面高度 : " << cap.get(cv::CAP_PROP_FRAME_HEIGHT) << "\n";
        }
    }

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