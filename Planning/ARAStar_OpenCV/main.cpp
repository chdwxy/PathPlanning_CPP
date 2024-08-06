// #include "arastar.hpp"
// #include <iostream>

// int main() {
//     std::pair<int, int> s_start = {5, 5};
//     std::pair<int, int> s_goal = {45, 45};
//     double epsilon = 2.5;
//     std::string heuristic_type = "euclidean";

//     AraStar arastar(s_start, s_goal, epsilon, heuristic_type);
//     auto paths = arastar.searching();

//     for (const auto& path : paths) {
//         std::cout << "Path: ";
//         for (const auto& p : path) {
//             std::cout << "(" << p.first << ", " << p.second << ") ";
//         }
//         std::cout << std::endl;
//     }

//     return 0;
// }


// #include "arastar.hpp"
// #include <iostream>

// int main() {
//     std::pair<int, int> s_start = {5, 5};
//     std::pair<int, int> s_goal = {45, 25};
//     double epsilon = 2.5;
//     std::string heuristic_type = "euclidean";

//     AraStar arastar(s_start, s_goal, epsilon, heuristic_type);
//     auto paths = arastar.searching();

//     for (const auto& path : paths) {
//         std::cout << "Path: ";
//         for (const auto& p : path) {
//             std::cout << "(" << p.first << ", " << p.second << ") ";
//         }
//         std::cout << std::endl;
//     }

//     return 0;
// }



// #include "arastar.hpp"
// #include "../utils/plotting.hpp"
// #include <opencv2/opencv.hpp>

// int main() {
//     // 初始化起点和终点
//     std::pair<int, int> s_start(5, 5);
//     std::pair<int, int> s_goal(45, 45);

//     // 创建空白地图
//     cv::Mat map = cv::Mat::zeros(500, 500, CV_8UC3);
//     map.setTo(cv::Scalar(255, 255, 255)); // 设置背景为白色

//     // 初始化AraStar对象
//     AraStar arastar(s_start, s_goal, 2.5, "euclidean");
//     arastar.setMap(map); // 设置地图

//     // 搜索路径
//     auto path = arastar.searching();

//     // 动态绘制ARA*搜索过程
//     for (const auto& visited_each : arastar.getVisited()) {
//         for (const auto& v : visited_each) {
//             arastar.draw_dynamic(v, visited_each);
//         }
//     }

//     // 绘制最终路径
//     arastar.draw_paths();

//     return 0;
// }


#include "arastar.hpp"
#include <iostream>

int main() {
    std::pair<int, int> s_start = {5, 5};
    std::pair<int, int> s_goal = {45, 25};
    double epsilon = 2.5;
    std::string heuristic_type = "euclidean";

    AraStar arastar(s_start, s_goal, epsilon, heuristic_type);
    auto paths = arastar.searching();

    for (const auto& path : paths) {
        std::cout << "Path: ";
        for (const auto& p : path) {
            std::cout << "(" << p.first << ", " << p.second << ") ";
        }
        std::cout << std::endl;
    }

    return 0;
}
