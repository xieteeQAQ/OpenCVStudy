#include "../include/mainProcess.hpp"
#include <opencv2/opencv.hpp>
#include "../include/parameter.hpp"
#include "../include/func.hpp"
#include "../include/process.hpp"

void startProcess(cv::VideoCapture &cap, cv::VideoWriter &writer)
{
    cv::Mat frame;

    while (true)
    {

        cap >> frame;
        if (frame.empty())
        {
            std::cout << "帧为空!\n";
            break;
        }
        cv::Mat result;
        cv::Mat display;
        double now = cv::getTickCount() / cv::getTickFrequency();

        if (colorRecognition == 1)
        {
            colorRecognize(frame, result);
        }
        else
        {
            process(frame, result);
        }

        if (result.empty())
        {
            showEorrorImg(frame);
            if (cv::waitKey(1) == 'q')
            {
                std::cout << "result为空!\n";
                break;
            }
            continue;
        }

        if (result.channels() != 3)
        {
            display = getBGR(result).clone();
        }
        else
        {
            display = result.clone();
        }

        if (recording)
        {
            if (writer.isOpened())
                writer.write(getBGR(result));
            else if (!writer.isOpened())
                std::cout << "录像未打开!\n";
            else if (getBGR(result).channels() != 3)
                std::cout << "录像通道数不为3!\n";
        }

        if (delayisStarted && (now - shotStartTime >= delaySeconds))
        {
            delayisStarted = false;
            saveImg(result);
        }

        putTexts(display, now);
        cv::imshow("result", display);

        int key = cv::waitKey(1);
        int isBreak = keyCheck(result, writer, key, now);
        if (isBreak)
            break;
    }
}