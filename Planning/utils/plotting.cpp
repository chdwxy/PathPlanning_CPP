#include "plotting.hpp"
#include <opencv2/opencv.hpp>

// Plotting::Plotting(std::pair<int, int> s_start, std::pair<int, int> s_goal)
//     : s_start(s_start), s_goal(s_goal) {}

// void Plotting::animation_ara_star(const std::vector<std::vector<std::pair<int, int>>>& path, 
//                                   const std::vector<std::vector<std::pair<int, int>>>& visited, 
//                                   const std::string& title) {
//     int scale = 10;
//     cv::Mat img(600, 600, CV_8UC3, cv::Scalar(255, 255, 255));
//     for (const auto& step : visited) {
//         for (const auto& point : step) {
//             cv::circle(img, cv::Point(point.second * scale, point.first * scale), 2, cv::Scalar(0, 0, 255), -1);
//         }
//         cv::imshow(title, img);
//         cv::waitKey(100);
//     }

//     for (const auto& p : path) {
//         for (size_t i = 0; i < p.size() - 1; ++i) {
//             cv::line(img, cv::Point(p[i].second * scale, p[i].first * scale), 
//                           cv::Point(p[i + 1].second * scale, p[i + 1].first * scale), 
//                           cv::Scalar(0, 255, 0), 2);
//         }
//     }
//     cv::imshow(title, img);
//     cv::waitKey(0);
// }



Plotting::Plotting(std::pair<int, int> start, std::pair<int, int> goal) : s_start(start), s_goal(goal) {
    scale = 10;
    rows = 50;
    cols = 50;
    img = cv::Mat::zeros(rows * scale, cols * scale, CV_8UC3);
    img.setTo(cv::Scalar(255, 255, 255));
}

void Plotting::plot_path(const std::vector<std::pair<int, int>>& path, const std::vector<std::vector<std::pair<int, int>>>& visited, const std::string& title) {
    for (const auto& step : path) {
        cv::circle(img, cv::Point(step.second * scale, step.first * scale), scale / 2, cv::Scalar(0, 0, 255), -1);
    }

    for (const auto& visit : visited) {
        for (const auto& step : visit) {
            cv::circle(img, cv::Point(step.second * scale, step.first * scale), scale / 3, cv::Scalar(0, 255, 0), -1);
        }
    }

    cv::circle(img, cv::Point(s_start.second * scale, s_start.first * scale), scale, cv::Scalar(255, 0, 0), -1);
    cv::circle(img, cv::Point(s_goal.second * scale, s_goal.first * scale), scale, cv::Scalar(0, 255, 255), -1);

    cv::imshow(title, img);
    cv::waitKey(0);
}

void Plotting::animation_ara_star(const std::vector<std::vector<std::pair<int, int>>>& path, const std::vector<std::vector<std::pair<int, int>>>& visited, const std::string& title) {
    img.setTo(cv::Scalar(255, 255, 255)); // Clear the image

    for (const auto& visit : visited) {
        for (const auto& step : visit) {
            cv::circle(img, cv::Point(step.second * scale, step.first * scale), scale / 3, cv::Scalar(0, 255, 0), -1);
            cv::imshow(title, img);
            cv::waitKey(50); // Wait 50 ms
        }
    }

    for (const auto& path_step : path) {
        for (const auto& step : path_step) {
            cv::circle(img, cv::Point(step.second * scale, step.first * scale), scale / 2, cv::Scalar(0, 0, 255), -1);
            cv::imshow(title, img);
            cv::waitKey(100); // Wait 100 ms
        }
    }

    cv::circle(img, cv::Point(s_start.second * scale, s_start.first * scale), scale, cv::Scalar(255, 0, 0), -1);
    cv::circle(img, cv::Point(s_goal.second * scale, s_goal.first * scale), scale, cv::Scalar(0, 255, 255), -1);

    cv::imshow(title, img);
    cv::waitKey(0);
}

void Plotting::animationBiAStar(const std::vector<std::pair<int, int>>& path,
                                const std::vector<std::pair<int, int>>& visitedFore,
                                const std::vector<std::pair<int, int>>& visitedBack,
                                const std::string& title) const {
    std::cout << title << std::endl;
    std::cout << "Path: ";
    for (const auto& p : path) {
        std::cout << "(" << p.first << "," << p.second << ") ";
    }
    std::cout << std::endl;
}

