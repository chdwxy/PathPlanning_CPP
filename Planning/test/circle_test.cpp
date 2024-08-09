#include <opencv2/opencv.hpp>
#include <string>

int main() {
    // 创建一个 500x500 的白色图像
    cv::Mat img = cv::Mat::zeros(500, 500, CV_8UC3);
    img.setTo(cv::Scalar(255, 255, 255));

    // 视频文件名
    std::string filename = "output.avi";

    // 创建视频写入器
    cv::VideoWriter writer(filename, cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), 10, img.size());

    // 检查视频写入器是否成功打开
    if (!writer.isOpened()) {
        std::cerr << "无法打开视频文件进行写入: " << filename << std::endl;
        return -1;
    }

    // 写入 100 帧
    for (int i = 0; i < 100; ++i) {
        // 绘制一个动态变化的圆
        cv::circle(img, cv::Point(i * 5, 250), 40, cv::Scalar(0, 0, 255), -1);

        // 写入当前帧
        writer.write(img);

        // 显示当前帧
        cv::imshow("Frame", img);
        cv::waitKey(100); // 等待 100 毫秒
    }

    // 释放视频写入器
    writer.release();

    return 0;
}
