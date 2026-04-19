# 指定最低 CMake 版本
cmake_minimum_required(VERSION 3.10)
# 设置项目名称
project(OpenCV_Demo)

# 设置 C++ 标准为 C++11 或更高
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 查找系统中安装的 OpenCV 库
# 如果 Homebrew 安装的路径未被自动找到，可以尝试设置 OpenCV_DIR 变量
set(OpenCV_DIR "/opt/homebrew/Cellar/opencv/4.13.0_8/lib/cmake/opencv4/OpenCVConfig.cmake") # Apple Silicon Macs
find_package(OpenCV REQUIRED)

# 打印 OpenCV 的包含目录和库文件（便于调试）
message(STATUS "OpenCV include dirs: ${OpenCV_INCLUDE_DIRS}")
message(STATUS "OpenCV libraries: ${OpenCV_LIBS}")

# 声明一个可执行文件，由 main.cpp 生成
add_executable(${PROJECT_NAME} ./src/main.cpp)

# 为目标可执行文件链接 OpenCV 库
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})