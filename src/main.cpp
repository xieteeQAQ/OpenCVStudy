#include <iostream>
#include <opencv2/opencv.hpp>

int main() {
    std::cout << "程序开始运行" << std::endl;
    std::cout << "OpenCV 版本: " << CV_VERSION << std::endl;
    
    // 创建一个简单的图像
    cv::Mat img(300, 400, CV_8UC3, cv::Scalar(255, 0, 0)); // 蓝色背景
    
    if (img.empty()) {
        std::cout << "图像创建失败" << std::endl;
        return -1;
    }
    
    std::cout << "图像创建成功，大小: " << img.cols << "x" << img.rows << std::endl;
    
    cv::imshow("测试窗口", img);
    std::cout << "窗口已创建，请按任意键关闭..." << std::endl;
    
    cv::waitKey(0);  // 等待按键
    cv::destroyAllWindows();
    
    std::cout << "程序正常结束" << std::endl;
    return 0;
}