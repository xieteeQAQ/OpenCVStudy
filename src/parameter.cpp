#include"../include/parameter.hpp"

std::string savePath = "/Users/xietee/program/OpenCVStudy/image";

int enCanny = 0;
int enGray = 0;
int enGaussianBlur = 0;
int colorRecognition = 0;

int blur_slider = 2;
int sigma_slider = 0;
int low = 50;
int high = 180;

int enHSV = 0;
int h_min = 0;
int h_max = 179;
int s_min = 0;
int s_max = 255;
int v_min = 0;
int v_max = 255;
int areaSize = 5000;

bool shotDelay = false;
bool delayisStarted = false;
double shotStartTime = 0;
double delaySeconds = 3;

bool recording = false;
double FPS = 30.0;
double recordStartTime = 0;
