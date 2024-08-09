// bidirectional_a_star.h
#ifndef BIDIRECTIONAL_A_STAR_H
#define BIDIRECTIONAL_A_STAR_H

#include <vector>
#include <utility>
#include <map>
#include <set>
#include <queue>
#include <cmath>
#include "env.hpp"

class BidirectionalAStar {
public:
    BidirectionalAStar(std::pair<int, int> s_start, std::pair<int, int> s_goal, std::string heuristic_type);

    std::tuple<std::vector<std::pair<int, int>>, std::vector<std::pair<int, int>>, std::vector<std::pair<int, int>>> 
    searching();

private:
    void init();
    std::vector<std::pair<int, int>> get_neighbor(std::pair<int, int> s);
    std::vector<std::pair<int, int>> extract_path(std::pair<int, int> s_meet);
    double f_value_fore(std::pair<int, int> s);
    double f_value_back(std::pair<int, int> s);
    double h(std::pair<int, int> s, std::pair<int, int> goal);
    double cost(std::pair<int, int> s_start, std::pair<int, int> s_goal);
    bool is_collision(std::pair<int, int> s_start, std::pair<int, int> s_end);

    std::pair<int, int> s_start, s_goal;
    std::string heuristic_type;

    Env env;
    std::vector<std::pair<int, int>> motions;
    std::vector<std::pair<int, int>> obstacles;

    using PII = std::pair<int, int>;
    using PQElement = std::pair<double, PII>;

    std::priority_queue<PQElement, std::vector<PQElement>, std::greater<PQElement>> open_fore, open_back;
    std::set<PII> closed_fore, closed_back;
    std::map<PII, PII> parent_fore, parent_back;
    std::map<PII, double> g_fore, g_back;
};

#endif // BIDIRECTIONAL_A_STAR_H
