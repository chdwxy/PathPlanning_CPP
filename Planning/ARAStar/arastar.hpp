#ifndef ARASTAR_HPP
#define ARASTAR_HPP

#include <vector>
#include <set>
#include <map>
#include <utility>
#include <cmath>
// #include "env.hpp"
#include "../utils/env.hpp"


class AraStar {
public:
    AraStar(std::pair<int, int> s_start, std::pair<int, int> s_goal, double e, std::string heuristic_type);
    std::vector<std::vector<std::pair<int, int>>> searching();
    // std::pair<std::vector<std::vector<std::pair<int, int>>>, std::vector<std::pair<int, int>>> searching();
    std::vector<std::vector<std::pair<int, int>>>  ImprovePath();

private:
    std::pair<int, int> s_start, s_goal;
    std::string heuristic_type;
    Env env;
    std::vector<std::pair<int, int>> u_set;
    std::set<std::pair<int, int>> obs;
    double e;
    std::map<std::pair<int, int>, double> g;
    std::map<std::pair<int, int>, double> OPEN;
    std::set<std::pair<int, int>> CLOSED;
    std::map<std::pair<int, int>, double> INCONS;
    std::map<std::pair<int, int>, std::pair<int, int>> PARENT;
    std::vector<std::vector<std::pair<int, int>>> path;
    std::vector<std::vector<std::pair<int, int>>> visited;
    // std::vector<std::vector<std::pair<int, int>>> path;
    // std::vector<std::pair<int, int>> visited;
    // std::vector<std::pair<int, int>> path;

    void init();
    
    std::pair<std::pair<int, int>, double> calc_smallest_f();
    std::set<std::pair<int, int>> get_neighbor(std::pair<int, int> s);
    double update_e();
    double f_value(std::pair<int, int> x);
    std::vector<std::pair<int, int>> extract_path();
    double h(std::pair<int, int> s);
    double cost(std::pair<int, int> s_start, std::pair<int, int> s_goal);
    bool is_collision(std::pair<int, int> s_start, std::pair<int, int> s_end);
};

#endif // ARASTAR_HPP
