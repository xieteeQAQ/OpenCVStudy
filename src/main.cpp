#include <iostream>
#include <opencv2/opencv.hpp>
#include "../include/tools.hpp"
// #include <ApplicationServices/ApplicationServices.h>

int main()
{
    std::cout << "程序开始运行\n";
    std::cout << "OpenCV Version : " << CV_VERSION << "\n";

    cv::Mat img = cv::imread("../image/cao.jpg");
    if (isEmpty(img))
        return -1;

    cv::namedWindow("cao", cv::WINDOW_AUTOSIZE);
    cv::Mat img2 = img.clone();
    cv::Mat img3;
    cv::resize(img, img2, cv::Size(), 0.6, 0.6, cv::INTER_LINEAR);
    cv::moveWindow("cao", ((2880 - img2.rows) / 2) - 250, (1107 - img2.cols) / 2);

    cv::GaussianBlur(img2, img3, cv::Size(5, 5), 1.5);

    // for(int y = 0; y < img2.rows; ++y)
    // {
    //     for(int x = 0; x < img2.cols; ++x)
    //     {
    //         cv::Vec3b pixel = img2.at<cv::Vec3b>(y, x);

    //         pixel[0] /= 2;
    //         pixel[1] /= 2;
    //         pixel[2] /= 2;

    //         img2.at<cv::Vec3b>(y, x) = pixel;
    //     }
    // }

    cv::imshow("t", img2);
    cv::imshow("cao", img3);

    while(true)
    {
        if(cv::waitKey(30) == 'q')
         break;
    }
    cv::destroyAllWindows();
    
    std::cout << "程序正常结束" << std::endl;
    return 0;
}