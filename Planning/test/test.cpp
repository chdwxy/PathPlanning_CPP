#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {
    // 创建一个窗口
    namedWindow("Dynamic Circle", WINDOW_AUTOSIZE);

    // 定义图像大小和颜色
    int width = 800;
    int height = 600;
    Scalar backgroundColor(255, 255, 255); // 白色背景

    // 定义圆的初始位置和速度
    Point circleCenter(width / 2, height / 2);
    int radius = 50;
    int dx = 5; // 水平方向速度
    int dy = 5; // 垂直方向速度

    while (true) {
        // 创建一个空白图像
        Mat img(height, width, CV_8UC3, backgroundColor);

        // 画一个圆
        circle(img, circleCenter, radius, Scalar(0, 0, 255), -1); // 红色填充圆

        // 更新圆的位置
        circleCenter.x += dx;
        circleCenter.y += dy;

        // 检查边界并反弹
        if (circleCenter.x - radius < 0 || circleCenter.x + radius > width) {
            dx = -dx;
        }
        if (circleCenter.y - radius < 0 || circleCenter.y + radius > height) {
            dy = -dy;
        }

        // 显示图像
        imshow("Dynamic Circle", img);

        // 等待键盘输入（30ms），如果按下ESC键则退出
        if (waitKey(30) == 27) {
            break;
        }
    }

    return 0;
}
