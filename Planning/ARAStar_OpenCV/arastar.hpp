// #ifndef ARASTAR_H
// #define ARASTAR_H

// #include <vector>
// #include <set>
// #include <map>
// #include <utility>
// #include <string>
// #include <opencv2/opencv.hpp>
// #include "env.hpp"

// class AraStar {
// public:
//     AraStar(std::pair<int, int> s_start, std::pair<int, int> s_goal, double e, std::string heuristic_type);
//     std::vector<std::vector<std::pair<int, int>>> searching();

// private:
//     std::pair<int, int> s_start;
//     std::pair<int, int> s_goal;
//     double e;
//     std::string heuristic_type;
//     Env env;
//     cv::Mat map; // OpenCV 图像矩阵

//     std::map<std::pair<int, int>, double> g;
//     std::map<std::pair<int, int>, double> OPEN;
//     std::set<std::pair<int, int>> CLOSED;
//     std::map<std::pair<int, int>, std::pair<int, int>> PARENT;
//     std::map<std::pair<int, int>, double> INCONS;
//     std::vector<std::vector<std::pair<int, int>>> path;
//     std::vector<std::vector<std::pair<int, int>>> visited;

//     std::vector<std::pair<int, int>> u_set;
//     std::set<std::pair<int, int>> obs;

//     void init();
//     std::vector<std::vector<std::pair<int, int>>> ImprovePath();
//     std::pair<std::pair<int, int>, double> calc_smallest_f();
//     std::set<std::pair<int, int>> get_neighbor(std::pair<int, int> s);
//     double update_e();
//     double f_value(std::pair<int, int> x);
//     std::vector<std::pair<int, int>> extract_path();
//     double h(std::pair<int, int> s);
//     double cost(std::pair<int, int> s_start, std::pair<int, int> s_goal);
//     bool is_collision(std::pair<int, int> s_start, std::pair<int, int> s_end);
//     void draw_paths(); // 用于绘制路径的方法
//     void draw_dynamic(std::pair<int, int> current, const std::vector<std::pair<int, int>>& visited_each);
// };

// #endif // ARASTAR_H



// #ifndef ARASTAR_H
// #define ARASTAR_H

// #include <vector>
// #include <set>
// #include <map>
// #include <utility>
// #include <string>
// #include <opencv2/opencv.hpp>
// #include "env.hpp"

// class AraStar {
// public:
//     AraStar(std::pair<int, int> s_start, std::pair<int, int> s_goal, double e, std::string heuristic_type);
//     std::vector<std::vector<std::pair<int, int>>> searching();

// private:
//     std::pair<int, int> s_start;
//     std::pair<int, int> s_goal;
//     double e;
//     std::string heuristic_type;
//     Env env;
//     cv::Mat map;

//     std::map<std::pair<int, int>, double> g;
//     std::map<std::pair<int, int>, double> OPEN;
//     std::set<std::pair<int, int>> CLOSED;
//     std::map<std::pair<int, int>, std::pair<int, int>> PARENT;
//     std::map<std::pair<int, int>, double> INCONS;
//     std::vector<std::vector<std::pair<int, int>>> path;
//     std::vector<std::vector<std::pair<int, int>>> visited;

//     std::vector<std::pair<int, int>> u_set;
//     std::set<std::pair<int, int>> obs;

//     void init();
//     std::vector<std::vector<std::pair<int, int>>> ImprovePath();
//     std::pair<std::pair<int, int>, double> calc_smallest_f();
//     std::set<std::pair<int, int>> get_neighbor(std::pair<int, int> s);
//     double update_e();
//     double f_value(std::pair<int, int> x);
//     std::vector<std::pair<int, int>> extract_path();
//     double h(std::pair<int, int> s);
//     double cost(std::pair<int, int> s_start, std::pair<int, int> s_goal);
//     bool is_collision(std::pair<int, int> s_start, std::pair<int, int> s_end);
//     void draw_paths();
//     void draw_dynamic(std::pair<int, int> current, const std::vector<std::pair<int, int>>& visited_each);
// };

// #endif // ARASTAR_H




// #ifndef ARASTAR_HPP
// #define ARASTAR_HPP

// #include <vector>
// #include <set>
// #include <map>
// #include <utility>
// #include <cmath>
// #include <opencv2/opencv.hpp>
// #include "../utils/env.hpp"

// class AraStar {
// public:
//     AraStar(std::pair<int, int> s_start, std::pair<int, int> s_goal, double e, std::string heuristic_type);
//     std::vector<std::vector<std::pair<int, int>>> searching();
//     std::vector<std::vector<std::pair<int, int>>> ImprovePath();
//     void draw_paths();
//     void draw_dynamic(std::pair<int, int> current, const std::vector<std::pair<int, int>>& visited_each);
//     void setMap(const cv::Mat& input_map);

//     std::vector<std::vector<std::pair<int, int>>> getVisited() const { return visited; }

// private:
//     std::pair<int, int> s_start, s_goal;
//     std::string heuristic_type;
//     Env env;
//     std::vector<std::pair<int, int>> u_set;
//     std::set<std::pair<int, int>> obs;
//     double e;
//     std::map<std::pair<int, int>, double> g;
//     std::map<std::pair<int, int>, double> OPEN;
//     std::set<std::pair<int, int>> CLOSED;
//     std::map<std::pair<int, int>, double> INCONS;
//     std::map<std::pair<int, int>, std::pair<int, int>> PARENT;
//     std::vector<std::vector<std::pair<int, int>>> path;
//     std::vector<std::vector<std::pair<int, int>>> visited;
//     cv::Mat map;

//     void init();
//     std::pair<std::pair<int, int>, double> calc_smallest_f();
//     std::set<std::pair<int, int>> get_neighbor(std::pair<int, int> s);
//     double update_e();
//     double f_value(std::pair<int, int> x);
//     std::vector<std::pair<int, int>> extract_path();
//     double h(std::pair<int, int> s);
//     double cost(std::pair<int, int> s_start, std::pair<int, int> s_goal);
//     bool is_collision(std::pair<int, int> s_start, std::pair<int, int> s_end);
// };

// #endif // ARASTAR_HPP






#ifndef ARASTAR_H
#define ARASTAR_H

#include <vector>
#include <set>
#include <map>
#include <utility>
#include <string>
#include <opencv2/opencv.hpp>
// #include "env.hpp"
#include "../utils/env.hpp"

class AraStar {
public:
    AraStar(std::pair<int, int> s_start, std::pair<int, int> s_goal, double e, std::string heuristic_type);
    std::vector<std::vector<std::pair<int, int>>> searching();

private:
    std::pair<int, int> s_start;
    std::pair<int, int> s_goal;
    double e;
    std::string heuristic_type;
    Env env;
    cv::Mat map; // OpenCV 图像矩阵

    std::map<std::pair<int, int>, double> g;
    std::map<std::pair<int, int>, double> OPEN;
    std::set<std::pair<int, int>> CLOSED;
    std::map<std::pair<int, int>, std::pair<int, int>> PARENT;
    std::map<std::pair<int, int>, double> INCONS;
    std::vector<std::vector<std::pair<int, int>>> path;
    std::vector<std::vector<std::pair<int, int>>> visited;

    std::vector<std::pair<int, int>> u_set;
    std::set<std::pair<int, int>> obs;

    void init();
    std::vector<std::vector<std::pair<int, int>>> ImprovePath();
    std::pair<std::pair<int, int>, double> calc_smallest_f();
    std::set<std::pair<int, int>> get_neighbor(std::pair<int, int> s);
    double update_e();
    double f_value(std::pair<int, int> x);
    std::vector<std::pair<int, int>> extract_path();
    double h(std::pair<int, int> s);
    double cost(std::pair<int, int> s_start, std::pair<int, int> s_goal);
    bool is_collision(std::pair<int, int> s_start, std::pair<int, int> s_end);
    void draw_paths(); // 用于绘制路径的方法
};

#endif // ARASTAR_H
