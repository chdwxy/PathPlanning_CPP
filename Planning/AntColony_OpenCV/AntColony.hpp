// #ifndef ANT_COLONY_H
// #define ANT_COLONY_H

// #include <vector>
// #include <opencv2/opencv.hpp>
// #include <set>
// #include "env.hpp"

// class AntColony {
// public:
//     AntColony(int numAnts, int numCities, double alpha, double beta, double evaporation, double q);
//     void initialize();
//     void optimize(int iterations);
//     void printBestPath();
//     // void visualize(int delay);

// private:
//     int numAnts;
//     int numCities;
//     double alpha;
//     double beta;
//     double evaporation;
//     double q;
//     std::vector<std::vector<double>> pheromones;
//     std::vector<std::vector<double>> distances;
//     std::vector<int> bestPath;
//     double bestPathLength;
//     Env env;
//     cv::Mat map; // OpenCV 图像用于可视化
//     std::vector<std::vector<int>> paths; // 保存所有路径

//     void initializePheromones();
//     void initializeDistances();
//     void moveAnts();
//     void updatePheromones();
//     double calculatePathLength(const std::vector<int>& path);
//     void drawPaths(const std::vector<int>& path, const std::string& windowName);
// };

// #endif // ANT_COLONY_H



// #ifndef ANT_COLONY_H
// #define ANT_COLONY_H

// #include <vector>
// #include <opencv2/opencv.hpp>

// class AntColony {
// public:
//     AntColony(int numAnts, int numCities, double alpha, double beta, double evaporation, double q);
//     void initialize();
//     void optimize(int iterations);
//     void printBestPath();
//     void visualize(int delay);

// private:
//     int numAnts;
//     int numCities;
//     double alpha;
//     double beta;
//     double evaporation;
//     double q;
//     std::vector<std::vector<double>> pheromones;
//     std::vector<std::vector<double>> distances;
//     std::vector<int> bestPath;
//     double bestPathLength;
//     std::vector<std::vector<int>> paths; // 保存所有路径

//     void initializePheromones();
//     void initializeDistances();
//     void moveAnts();
//     void updatePheromones();
//     double calculatePathLength(const std::vector<int>& path);
//     void drawPath(cv::Mat& img, const std::vector<int>& path, const cv::Scalar& color);
// };

// #endif // ANT_COLONY_H



#ifndef ANT_COLONY_OPENCV_H
#define ANT_COLONY_OPENCV_H

#include <vector>
#include <set>
// #include "env.hpp"
#include "../utils/env.hpp"
#include <opencv2/opencv.hpp>

class AntColony {
public:
    AntColony(int numAnts, int numCities, double alpha, double beta, double evaporation, double q);
    void initialize();
    void optimize(int iterations);
    void printBestPath();
    void visualize(int delay);
    void drawPaths(const std::vector<int>& path, const std::string& windowName);

private:
    int numAnts;
    int numCities;
    double alpha;
    double beta;
    double evaporation;
    double q;
    std::vector<std::vector<double>> pheromones;
    std::vector<std::vector<double>> distances;
    std::vector<int> bestPath;
    double bestPathLength;
    Env env; // Add the environment as a member
    std::vector<std::vector<int>> paths; // Store paths for visualization
    cv::Mat map; // For OpenCV visualization

    void initializePheromones();
    void initializeDistances();
    void moveAnts();
    void updatePheromones();
    double calculatePathLength(const std::vector<int>& path);
    void drawPath(cv::Mat& img, const std::vector<int>& path, const cv::Scalar& color);
};

#endif // ANT_COLONY_OPENCV_H
