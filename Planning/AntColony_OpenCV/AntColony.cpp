// #include "AntColony.hpp"
// #include <iostream>
// #include <cmath>
// #include <limits>
// #include <algorithm>
// #include <random>

// AntColony::AntColony(int numAnts, int numCities, double alpha, double beta, double evaporation, double q)
//     : numAnts(numAnts), numCities(numCities), alpha(alpha), beta(beta), evaporation(evaporation), q(q) {
//     initialize();
//     map = cv::Mat::zeros(600, 600, CV_8UC3); // 初始化 OpenCV 图像
// }

// void AntColony::initialize() {
//     initializePheromones();
//     initializeDistances();
//     bestPathLength = std::numeric_limits<double>::max();
// }

// void AntColony::initializePheromones() {
//     pheromones.resize(numCities, std::vector<double>(numCities, 1.0));
// }

// void AntColony::initializeDistances() {
//     distances.resize(numCities, std::vector<double>(numCities));
//     std::random_device rd;
//     std::mt19937 gen(rd());
//     std::uniform_real_distribution<> dis(1.0, 100.0);

//     for (int i = 0; i < numCities; ++i) {
//         for (int j = i + 1; j < numCities; ++j) {
//             double distance = dis(gen);
//             distances[i][j] = distances[j][i] = distance;
//         }
//     }
// }

// void AntColony::optimize(int iterations) {
//     for (int iter = 0; iter < iterations; ++iter) {
//         moveAnts();
//         updatePheromones();
//         drawPaths(bestPath, "Ant Colony Optimization");
//         cv::waitKey(300); // 等待一段时间，以便观察每一步的变化
//         // visualize(500); // 每次迭代后可视化
//     }
//     // cv::destroyAllWindows(); // 关闭所有 OpenCV 窗口
// }

// void AntColony::moveAnts() {
//     std::vector<int> path(numCities);
//     std::iota(path.begin(), path.end(), 0);

//     for (int k = 0; k < numAnts; ++k) {
//         std::random_shuffle(path.begin(), path.end());
//         double pathLength = calculatePathLength(path);
//         paths.push_back(path); // 记录路径

//         if (pathLength < bestPathLength) {
//             bestPath = path;
//             bestPathLength = pathLength;
//         }
//     }
// }

// double AntColony::calculatePathLength(const std::vector<int>& path) {
//     double length = 0.0;
//     for (int i = 0; i < numCities - 1; ++i) {
//         length += distances[path[i]][path[i + 1]];
//     }
//     length += distances[path[numCities - 1]][path[0]];
//     return length;
// }

// void AntColony::updatePheromones() {
//     for (auto& row : pheromones) {
//         for (auto& pheromone : row) {
//             pheromone *= (1.0 - evaporation);
//         }
//     }

//     for (int i = 0; i < numCities - 1; ++i) {
//         int from = bestPath[i];
//         int to = bestPath[i + 1];
//         pheromones[from][to] += q / bestPathLength;
//         pheromones[to][from] += q / bestPathLength;
//     }
//     int from = bestPath[numCities - 1];
//     int to = bestPath[0];
//     pheromones[from][to] += q / bestPathLength;
//     pheromones[to][from] += q / bestPathLength;
// }

// void AntColony::drawPaths(const std::vector<int>& path, const std::string& windowName) {
//     map.setTo(cv::Scalar(0, 0, 0)); // 清空图像
//     std::vector<cv::Point> points(numCities);
//     for (int i = 0; i < numCities; ++i) {
//         points[i] = cv::Point(rand() % map.cols, rand() % map.rows);
//         cv::circle(map, points[i], 5, cv::Scalar(0, 255, 0), -1);
//     }
//     for (int i = 0; i < numCities - 1; ++i) {
//         cv::line(map, points[path[i]], points[path[i + 1]], cv::Scalar(255, 0, 0), 2);
//     }
//     cv::line(map, points[path[numCities - 1]], points[path[0]], cv::Scalar(255, 0, 0), 2);

//     cv::imshow(windowName, map);
// }

// void AntColony::printBestPath() {
//     std::cout << "Best Path: ";
//     for (int city : bestPath) {
//         std::cout << city << " ";
//     }
//     std::cout << "\nBest Path Length: " << bestPathLength << std::endl;
// }





// #include "AntColony.hpp"
// #include <iostream>
// #include <cmath>
// #include <limits>
// #include <algorithm>
// #include <random>
// #include <opencv2/opencv.hpp>

// AntColony::AntColony(int numAnts, int numCities, double alpha, double beta, double evaporation, double q)
//     : numAnts(numAnts), numCities(numCities), alpha(alpha), beta(beta), evaporation(evaporation), q(q) {
//     initialize();
// }

// void AntColony::initialize() {
//     initializePheromones();
//     initializeDistances();
//     bestPathLength = std::numeric_limits<double>::max();
//     paths.clear(); // 清空路径记录
// }

// void AntColony::initializePheromones() {
//     pheromones.resize(numCities, std::vector<double>(numCities, 1.0));
// }

// void AntColony::initializeDistances() {
//     distances.resize(numCities, std::vector<double>(numCities));
//     std::random_device rd;
//     std::mt19937 gen(rd());
//     std::uniform_real_distribution<> dis(1.0, 100.0);

//     for (int i = 0; i < numCities; ++i) {
//         for (int j = i + 1; j < numCities; ++j) {
//             double distance = dis(gen);
//             distances[i][j] = distances[j][i] = distance;
//         }
//     }
// }

// void AntColony::optimize(int iterations) {
//     for (int iter = 0; iter < iterations; ++iter) {
//         moveAnts();
//         updatePheromones();
//         visualize(500); // 每次迭代后可视化
//     }
// }

// void AntColony::moveAnts() {
//     std::vector<int> path(numCities);
//     std::iota(path.begin(), path.end(), 0);

//     for (int k = 0; k < numAnts; ++k) {
//         std::random_shuffle(path.begin(), path.end());
//         double pathLength = calculatePathLength(path);
//         paths.push_back(path); // 记录路径

//         if (pathLength < bestPathLength) {
//             bestPath = path;
//             bestPathLength = pathLength;
//         }
//     }
// }

// double AntColony::calculatePathLength(const std::vector<int>& path) {
//     double length = 0.0;
//     for (int i = 0; i < numCities - 1; ++i) {
//         length += distances[path[i]][path[i + 1]];
//     }
//     length += distances[path[numCities - 1]][path[0]];
//     return length;
// }

// void AntColony::updatePheromones() {
//     for (auto& row : pheromones) {
//         for (auto& pheromone : row) {
//             pheromone *= (1.0 - evaporation);
//         }
//     }

//     for (int i = 0; i < numCities - 1; ++i) {
//         int from = bestPath[i];
//         int to = bestPath[i + 1];
//         pheromones[from][to] += q / bestPathLength;
//         pheromones[to][from] += q / bestPathLength;
//     }
//     int from = bestPath[numCities - 1];
//     int to = bestPath[0];
//     pheromones[from][to] += q / bestPathLength;
//     pheromones[to][from] += q / bestPathLength;
// }

// void AntColony::printBestPath() {
//     std::cout << "Best Path: ";
//     for (int city : bestPath) {
//         std::cout << city << " ";
//     }
//     std::cout << "\nBest Path Length: " << bestPathLength << std::endl;
// }

// void AntColony::visualize(int delay) {
//     int scale = 20;
    // cv::Mat img(600, 800, CV_8UC3, cv::Scalar(255, 255, 255)); // 白色背景

//     // 画所有路径
//     for (const auto& path : paths) {
//         drawPath(img, path, cv::Scalar(200, 200, 200)); // 灰色表示尝试过的路径
//     }

//     // 画最优路径
//     drawPath(img, bestPath, cv::Scalar(0, 0, 255)); // 红色表示最优路径

//     // 画城市
//     for (int i = 0; i < numCities; ++i) {
//         cv::circle(img, cv::Point(distances[i][0] * scale, distances[i][1] * scale), 5, cv::Scalar(0, 0, 0), cv::FILLED);
//     }

//     cv::imshow("Ant Colony Optimization", img);
//     cv::waitKey(delay);
// }

// void AntColony::drawPath(cv::Mat& img, const std::vector<int>& path, const cv::Scalar& color) {
//     int scale = 20;
//     for (size_t i = 0; i < path.size() - 1; ++i) {
//         cv::line(img, cv::Point(distances[path[i]][0] * scale, distances[path[i]][1] * scale),
//                  cv::Point(distances[path[i + 1]][0] * scale, distances[path[i + 1]][1] * scale), color, 2);
//     }
//     cv::line(img, cv::Point(distances[path.back()][0] * scale, distances[path.back()][1] * scale),
//              cv::Point(distances[path[0]][0] * scale, distances[path[0]][1] * scale), color, 2);
// }




#include "AntColony.hpp"
#include <iostream>
#include <cmath>
#include <limits>
#include <algorithm>
#include <random>

AntColony::AntColony(int numAnts, int numCities, double alpha, double beta, double evaporation, double q)
    : numAnts(numAnts), numCities(numCities), alpha(alpha), beta(beta), evaporation(evaporation), q(q), env() {
    initialize();
    map = cv::Mat::zeros(env.y_range * 10, env.x_range * 10, CV_8UC3); // Initialize OpenCV image with white background
}

void AntColony::initialize() {
    initializePheromones();
    initializeDistances();
    bestPathLength = std::numeric_limits<double>::max();
}

void AntColony::initializePheromones() {
    pheromones.resize(numCities, std::vector<double>(numCities, 1.0));
}

void AntColony::initializeDistances() {
    distances.resize(numCities, std::vector<double>(numCities));
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(1.0, 100.0);

    for (int i = 0; i < numCities; ++i) {
        for (int j = i + 1; j < numCities; ++j) {
            double distance = dis(gen);
            distances[i][j] = distances[j][i] = distance;
        }
    }
}

void AntColony::optimize(int iterations) {
    for (int iter = 0; iter < iterations; ++iter) {
        moveAnts();
        updatePheromones();
        drawPaths(bestPath, "Ant Colony Optimization");
        cv::waitKey(300); // Wait for a short time to observe changes at each step
    }
    cv::waitKey(0); // Wait indefinitely until a key is pressed to close the window
}

void AntColony::moveAnts() {
    std::vector<int> path(numCities);
    std::iota(path.begin(), path.end(), 0);

    for (int k = 0; k < numAnts; ++k) {
        std::random_shuffle(path.begin(), path.end());
        double pathLength = calculatePathLength(path);
        paths.push_back(path); // Store the path

        if (pathLength < bestPathLength) {
            bestPath = path;
            bestPathLength = pathLength;
        }
    }
}

double AntColony::calculatePathLength(const std::vector<int>& path) {
    double length = 0.0;
    for (int i = 0; i < numCities - 1; ++i) {
        length += distances[path[i]][path[i + 1]];
    }
    length += distances[path[numCities - 1]][path[0]];
    return length;
}

void AntColony::updatePheromones() {
    for (auto& row : pheromones) {
        for (auto& pheromone : row) {
            pheromone *= (1.0 - evaporation);
        }
    }

    for (int i = 0; i < numCities - 1; ++i) {
        int from = bestPath[i];
        int to = bestPath[i + 1];
        pheromones[from][to] += q / bestPathLength;
        pheromones[to][from] += q / bestPathLength;
    }
    int from = bestPath[numCities - 1];
    int to = bestPath[0];
    pheromones[from][to] += q / bestPathLength;
    pheromones[to][from] += q / bestPathLength;
}

void AntColony::drawPaths(const std::vector<int>& path, const std::string& windowName) {
    map.setTo(cv::Scalar(255, 255, 255)); // 清空图像并设置为白色背景
    int scale = 10;
    std::vector<cv::Point> points(numCities);
    for (int i = 0; i < numCities; ++i) {
        points[i] = cv::Point(rand() % (env.x_range * scale), rand() % (env.y_range * scale));
        cv::circle(map, points[i], 5, cv::Scalar(0, 255, 0), -1);
    }
    for (int i = 0; i < numCities - 1; ++i) {
        cv::line(map, points[path[i]], points[path[i + 1]], cv::Scalar(255, 0, 0), 2);
    }
    cv::line(map, points[path[numCities - 1]], points[path[0]], cv::Scalar(255, 0, 0), 2);

    // 绘制障碍物
    for (const auto& obstacle : env.obs) {
        cv::rectangle(map, cv::Point(obstacle.first * scale, obstacle.second * scale),
                      cv::Point((obstacle.first + 1) * scale, (obstacle.second + 1) * scale), cv::Scalar(0, 0, 0), cv::FILLED);
    }

    cv::imshow(windowName, map);
    cv::waitKey(1); // 稍微等待，以便观察每一步的变化
}

void AntColony::visualize(int delay) {
    int scale = 10;
    cv::Mat img(env.y_range * scale, env.x_range * scale, CV_8UC3, cv::Scalar(255, 255, 255)); // 白色背景

    // 绘制所有尝试的路径
    for (const auto& path : paths) {
        drawPath(img, path, cv::Scalar(200, 200, 200)); // 灰色表示尝试过的路径
    }

    // 绘制最优路径
    drawPath(img, bestPath, cv::Scalar(0, 0, 255)); // 红色表示最优路径

    // 绘制城市节点
    for (int i = 0; i < numCities; ++i) {
        cv::circle(img, cv::Point(rand() % (env.x_range * scale), rand() % (env.y_range * scale)), 5, cv::Scalar(0, 255, 0), -1);
    }

    // 绘制障碍物
    for (const auto& obstacle : env.obs) {
        cv::rectangle(img, cv::Point(obstacle.first * scale, obstacle.second * scale),
                      cv::Point((obstacle.first + 1) * scale, (obstacle.second + 1) * scale), cv::Scalar(0, 0, 0), cv::FILLED);
    }

    cv::imshow("Ant Colony Optimization", img);
    cv::waitKey(delay);
}

void AntColony::drawPath(cv::Mat& img, const std::vector<int>& path, const cv::Scalar& color) {
    int scale = 10;
    std::vector<cv::Point> points(numCities);
    for (int i = 0; i < numCities; ++i) {
        points[i] = cv::Point(rand() % (env.x_range * scale), rand() % (env.y_range * scale));
    }
    for (int i = 0; i < numCities - 1; ++i) {
        cv::line(img, points[path[i]], points[path[i + 1]], color, 2);
    }
    cv::line(img, points[path[numCities - 1]], points[path[0]], color, 2);
}

void AntColony::printBestPath() {
    std::cout << "Best Path: ";
    for (int city : bestPath) {
        std::cout << city << " ";
    }
    std::cout << "\nBest Path Length: " << bestPathLength << std::endl;
}