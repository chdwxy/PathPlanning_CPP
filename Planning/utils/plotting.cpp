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
    scale = 5;
    rows = 500;
    cols = 500;
    // img = cv::Mat::zeros(rows * scale, cols * scale, CV_8UC3);
    img = cv::Mat(rows, cols, CV_8UC3, cv::Scalar(255, 255, 255));
    // img.setTo(cv::Scalar(255, 255, 255));
    drawGrid();
}

void Plotting::drawGrid() const {
    for (int i = 0; i < rows; ++i) {
        cv::line(img, cv::Point(0, i), cv::Point(cols, i), cv::Scalar(200, 200, 200));
    }
    for (int i = 0; i < cols; ++i) {
        cv::line(img, cv::Point(i, 0), cv::Point(i, rows), cv::Scalar(200, 200, 200));
    }
}

void Plotting::drawPath(const std::vector<std::pair<int, int>>& path, const cv::Scalar& color) const {
    for (const auto& p : path) {
        img.at<cv::Vec3b>(p.second, p.first) = cv::Vec3b(color[0], color[1], color[2]);
    }
}

void Plotting::drawClosed(const std::vector<std::pair<int, int>>& closed, const cv::Scalar& color) const {
    for (const auto& c : closed) {
        img.at<cv::Vec3b>(c.second, c.first) = cv::Vec3b(color[0], color[1], color[2]);
    }
}

void Plotting::animationBiAStar(const std::vector<std::pair<int, int>>& path1,
                                const std::vector<std::pair<int, int>>& path2,
                                const std::vector<std::pair<int, int>>& path3,
                                const std::vector<std::pair<int, int>>& closed_fore,
                                const std::vector<std::pair<int, int>>& closed_back,
                                const std::string& filename) const {
    cv::VideoWriter writer(filename, cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), 10, img.size());

    for (size_t i = 0; i < std::max(closed_fore.size(), closed_back.size()); ++i) {
        if (i < closed_fore.size()) {
            drawClosed({closed_fore[i]}, cv::Scalar(255, 0, 0));
        }
        if (i < closed_back.size()) {
            drawClosed({closed_back[i]}, cv::Scalar(0, 0, 255));
        }
        writer.write(img);
        cv::imshow("Bi-Directional A* Search", img);
        cv::waitKey(100);
    }

    drawPath(path1, cv::Scalar(0, 255, 0));
    drawPath(path2, cv::Scalar(0, 255, 0));
    drawPath(path3, cv::Scalar(0, 255, 0));

    writer.write(img);
    cv::imshow("Bi-Directional A* Search", img);
    cv::waitKey(0);
    writer.release();
}

void Plotting::animationBiAStarTest(const std::vector<std::pair<int, int>>& path,
                                const std::vector<std::pair<int, int>>& closed_fore,
                                const std::vector<std::pair<int, int>>& closed_back,
                                const std::string& filename) const {
    cv::VideoWriter writer(filename, cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), 10, img.size());

    for (size_t i = 0; i < std::max(closed_fore.size(), closed_back.size()); ++i) {
        if (i < closed_fore.size()) {
            drawClosed({closed_fore[i]}, cv::Scalar(255, 0, 0));
        }
        if (i < closed_back.size()) {
            drawClosed({closed_back[i]}, cv::Scalar(0, 0, 255));
        }
        writer.write(img);
        cv::imshow("Bi-Directional A* Search", img);
        cv::waitKey(100);
    }

    drawPath(path, cv::Scalar(0, 255, 0));

    writer.write(img);
    cv::imshow("Bi-Directional A* Search", img);
    cv::waitKey(0);
    writer.release();
}

// void Plotting::plot_path(const std::vector<std::pair<int, int>>& path, const std::vector<std::vector<std::pair<int, int>>>& visited, const std::string& title) {
//     for (const auto& step : path) {
//         cv::circle(img, cv::Point(step.second * scale, step.first * scale), scale, cv::Scalar(0, 0, 255), -1);
//         cout << "Drawing circle at: (" << step.second * scale << ", " << step.first * scale << ") with radius: " << scale << std::endl;
//     }

//     for (const auto& visit : visited) {
//         for (const auto& step : visit) {
//             cv::circle(img, cv::Point(step.second * scale, step.first * scale), scale, cv::Scalar(0, 255, 0), -1);
//             cout << "Drawing circle at: (" << step.second * scale << ", " << s_start.first * scale << ") with radius: " << scale << std::endl;
//         }
//     }

//     cv::circle(img, cv::Point(s_start.second * scale, s_start.first * scale), scale, cv::Scalar(255, 0, 0), -1);
//     cv::circle(img, cv::Point(s_goal.second * scale, s_goal.first * scale), scale, cv::Scalar(0, 255, 255), -1);
//     cout << "Drawing circle at: (" << s_start.second * scale << ", " << s_start.first * scale << ") with radius: " << scale << std::endl;

//     cv::imshow(title, img);
//     cv::waitKey(0);
// }

void Plotting::plot_path(const std::vector<std::pair<int, int>>& path,  const std::vector<std::pair<int, int>>& visited, const std::string& title) {
    for (const auto& step : path) {
        cv::circle(img, cv::Point(step.second * scale, step.first * scale), scale, cv::Scalar(0, 0, 255), -1);
        cout << "Drawing circle at: (" << step.second * scale << ", " << step.first * scale << ") with radius: " << scale << std::endl;
    }

    for (const auto& step : visited) {
        // for (const auto& step : visit) {
            cv::circle(img, cv::Point(step.second * scale, step.first * scale), scale, cv::Scalar(0, 255, 0), -1);
            cout << "Drawing circle at: (" << step.second * scale << ", " << s_start.first * scale << ") with radius: " << scale << std::endl;
        // }
    }

    cv::circle(img, cv::Point(s_start.second * scale, s_start.first * scale), scale, cv::Scalar(255, 0, 0), -1);
    cv::circle(img, cv::Point(s_goal.second * scale, s_goal.first * scale), scale, cv::Scalar(0, 255, 255), -1);
    cout << "Drawing circle at: (" << s_start.second * scale << ", " << s_start.first * scale << ") with radius: " << scale << std::endl;

    cv::imshow(title, img);
    cv::waitKey(0);
}

void Plotting::animation_ara_star(const std::vector<std::vector<std::pair<int, int>>>& path, const std::vector<std::vector<std::pair<int, int>>>& visited, const std::string& title) {
    img.setTo(cv::Scalar(255, 255, 255)); // Clear the image

    for (const auto& visit : visited) {
        for (const auto& step : visit) {
            cv::circle(img, cv::Point(step.second * scale, step.first * scale), scale, cv::Scalar(0, 255, 0), -1);
            cout << "Drawing circle at: (" << step.second * scale << ", " << step.first * scale << ") with radius: " << scale << std::endl;
            cv::imshow(title, img);
            cv::waitKey(50); // Wait 50 ms
        }
    }

    for (const auto& path_step : path) {
        for (const auto& step : path_step) {
            cv::circle(img, cv::Point(step.second * scale, step.first * scale), scale, cv::Scalar(0, 0, 255), -1);
            cout << "Drawing circle at: (" << step.second * scale << ", " << step.first * scale << ") with radius: " << scale << std::endl;
            cv::imshow(title, img);
            cv::waitKey(100); // Wait 100 ms
        }
    }

    cv::circle(img, cv::Point(s_start.second * scale, s_start.first * scale), scale, cv::Scalar(255, 0, 0), -1);
    cv::circle(img, cv::Point(s_goal.second * scale, s_goal.first * scale), scale, cv::Scalar(0, 255, 255), -1);

    cout << "Drawing circle at: (" << s_start.second * scale << ", " << s_start.first * scale << ") with radius: " << scale << std::endl;

    cv::imshow(title, img);
    cv::waitKey(0);
}

void Plotting::animation_lrta(const std::vector<std::vector<std::pair<int, int>>>& path, const std::vector<std::vector<std::pair<int, int>>>& visited, const std::string& title) {
    img.setTo(cv::Scalar(255, 255, 255)); // Clear the image

    for (const auto& visit : visited) {
        for (const auto& step : visit) {
            cv::circle(img, cv::Point(step.second * scale, step.first * scale), scale, cv::Scalar(0, 255, 0), -1);
            cout << "Drawing circle at: (" << step.second * scale << ", " << step.first * scale << ") with radius: " << scale << std::endl;
            cv::imshow(title, img);
            cv::waitKey(50); // Wait 50 ms
        }
    }

    for (const auto& path_step : path) {
        for (const auto& step : path_step) {
            cv::circle(img, cv::Point(step.second * scale, step.first * scale), scale, cv::Scalar(0, 0, 255), -1);
            cout << "Drawing circle at: (" << step.second * scale << ", " << step.first * scale << ") with radius: " << scale << std::endl;
            cv::imshow(title, img);
            cv::waitKey(100); // Wait 100 ms
        }
    }

    cv::circle(img, cv::Point(s_start.second * scale, s_start.first * scale), scale, cv::Scalar(255, 0, 0), -1);
    cv::circle(img, cv::Point(s_goal.second * scale, s_goal.first * scale), scale, cv::Scalar(0, 255, 255), -1);

    cout << "Drawing circle at: (" << s_start.second * scale << ", " << s_start.first * scale << ") with radius: " << scale << std::endl;

    cv::imshow(title, img);
    cv::waitKey(0);
}

// void Plotting::animationBiAStar(const std::vector<std::pair<int, int>>& path,
//                                 const std::vector<std::pair<int, int>>& visitedFore,
//                                 const std::vector<std::pair<int, int>>& visitedBack,
//                                 const std::string& title) const {
//     std::cout << title << std::endl;
//     std::cout << "Path: ";
//     for (const auto& p : path) {
//         std::cout << "(" << p.first << "," << p.second << ") ";
//     }
//     std::cout << std::endl;
// }


