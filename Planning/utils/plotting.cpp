#include "plotting.hpp"
#include <opencv2/opencv.hpp>

Plotting::Plotting(std::pair<int, int> s_start, std::pair<int, int> s_goal)
    : s_start(s_start), s_goal(s_goal) {}

void Plotting::animation_ara_star(const std::vector<std::vector<std::pair<int, int>>>& path, 
                                  const std::vector<std::vector<std::pair<int, int>>>& visited, 
                                  const std::string& title) {
    int scale = 10;
    cv::Mat img(600, 600, CV_8UC3, cv::Scalar(255, 255, 255));
    for (const auto& step : visited) {
        for (const auto& point : step) {
            cv::circle(img, cv::Point(point.second * scale, point.first * scale), 2, cv::Scalar(0, 0, 255), -1);
        }
        cv::imshow(title, img);
        cv::waitKey(100);
    }

    for (const auto& p : path) {
        for (size_t i = 0; i < p.size() - 1; ++i) {
            cv::line(img, cv::Point(p[i].second * scale, p[i].first * scale), 
                          cv::Point(p[i + 1].second * scale, p[i + 1].first * scale), 
                          cv::Scalar(0, 255, 0), 2);
        }
    }
    cv::imshow(title, img);
    cv::waitKey(0);
}
