// bidirectional_a_star.cpp
#include "bidirectional_a_star.hpp"
#include <algorithm>

BidirectionalAStar::BidirectionalAStar(std::pair<int, int> s_start, std::pair<int, int> s_goal, std::string heuristic_type) 
    : s_start(s_start), s_goal(s_goal), heuristic_type(heuristic_type) {
    motions = env.get_motions();
    obstacles = env.obs_map();
}

void BidirectionalAStar::init() {
    g_fore[s_start] = 0.0;
    g_fore[s_goal] = std::numeric_limits<double>::infinity();
    g_back[s_goal] = 0.0;
    g_back[s_start] = std::numeric_limits<double>::infinity();
    parent_fore[s_start] = s_start;
    parent_back[s_goal] = s_goal;
    open_fore.push({f_value_fore(s_start), s_start});
    open_back.push({f_value_back(s_goal), s_goal});
}

std::vector<std::pair<int, int>> BidirectionalAStar::get_neighbor(std::pair<int, int> s) {
    std::vector<std::pair<int, int>> neighbors;
    for (auto& m : motions) {
        std::pair<int, int> s_n = {s.first + m.first, s.second + m.second};
        if (std::find(obstacles.begin(), obstacles.end(), s_n) == obstacles.end()) {
            neighbors.push_back(s_n);
        }
    }
    return neighbors;
}

std::vector<std::pair<int, int>> BidirectionalAStar::extract_path(std::pair<int, int> s_meet) {
    std::vector<std::pair<int, int>> path, path_fore, path_back;
    std::pair<int, int> s = s_meet;

    while (s != s_start) {
        path_fore.push_back(s);
        s = parent_fore[s];
    }
    path_fore.push_back(s_start);
    std::reverse(path_fore.begin(), path_fore.end());

    s = s_meet;
    while (s != s_goal) {
        path_back.push_back(s);
        s = parent_back[s];
    }
    path_back.push_back(s_goal);

    path.insert(path.end(), path_fore.begin(), path_fore.end());
    path.insert(path.end(), path_back.begin() + 1, path_back.end());

    return path;
}

double BidirectionalAStar::f_value_fore(std::pair<int, int> s) {
    return g_fore[s] + h(s, s_goal);
}

double BidirectionalAStar::f_value_back(std::pair<int, int> s) {
    return g_back[s] + h(s, s_start);
}

double BidirectionalAStar::h(std::pair<int, int> s, std::pair<int, int> goal) {
    if (heuristic_type == "manhattan") {
        return std::abs(goal.first - s.first) + std::abs(goal.second - s.second);
    } else {
        return std::hypot(goal.first - s.first, goal.second - s.second);
    }
}

double BidirectionalAStar::cost(std::pair<int, int> s_start, std::pair<int, int> s_goal) {
    if (is_collision(s_start, s_goal)) {
        return std::numeric_limits<double>::infinity();
    }
    return std::hypot(s_goal.first - s_start.first, s_goal.second - s_start.second);
}

bool BidirectionalAStar::is_collision(std::pair<int, int> s_start, std::pair<int, int> s_end) {
    if (std::find(obstacles.begin(), obstacles.end(), s_start) != obstacles.end() || 
        std::find(obstacles.begin(), obstacles.end(), s_end) != obstacles.end()) {
        return true;
    }
    if (s_start.first != s_end.first && s_start.second != s_end.second) {
        std::pair<int, int> s1 = {std::min(s_start.first, s_end.first), std::min(s_start.second, s_end.second)};
        std::pair<int, int> s2 = {std::max(s_start.first, s_end.first), std::max(s_start.second, s_end.second)};
        if (std::find(obstacles.begin(), obstacles.end(), s1) != obstacles.end() ||
            std::find(obstacles.begin(), obstacles.end(), s2) != obstacles.end()) {
            return true;
        }
    }
    return false;
}

std::tuple<std::vector<std::pair<int, int>>, std::vector<std::pair<int, int>>, std::vector<std::pair<int, int>>> 
BidirectionalAStar::searching() {
    init();
    std::pair<int, int> s_meet;

    while (!open_fore.empty() && !open_back.empty()) {
        auto [_, s_fore] = open_fore.top();
        open_fore.pop();
        if (parent_back.find(s_fore) != parent_back.end()) {
            s_meet = s_fore;
            break;
        }
        closed_fore.insert(s_fore);
        for (auto& s_n : get_neighbor(s_fore)) {
            double new_cost = g_fore[s_fore] + cost(s_fore, s_n);
            if (g_fore.find(s_n) == g_fore.end()) {
                g_fore[s_n] = std::numeric_limits<double>::infinity();
            }
            if (new_cost < g_fore[s_n]) {
                g_fore[s_n] = new_cost;
                parent_fore[s_n] = s_fore;
                open_fore.push({f_value_fore(s_n), s_n});
            }
        }

        auto [__, s_back] = open_back.top();
        open_back.pop();
        if (parent_fore.find(s_back) != parent_fore.end()) {
            s_meet = s_back;
            break;
        }
        closed_back.insert(s_back);
        for (auto& s_n : get_neighbor(s_back)) {
            double new_cost = g_back[s_back] + cost(s_back, s_n);
            if (g_back.find(s_n) == g_back.end()) {
                g_back[s_n] = std::numeric_limits<double>::infinity();
            }
            if (new_cost < g_back[s_n]) {
                g_back[s_n] = new_cost;
                parent_back[s_n] = s_back;
                open_back.push({f_value_back(s_n), s_n});
            }
        }
    }

    std::vector<std::pair<int, int>> path = extract_path(s_meet);
    std::vector<std::pair<int, int>> visited_fore(closed_fore.begin(), closed_fore.end());
    std::vector<std::pair<int, int>> visited_back(closed_back.begin(), closed_back.end());
    return {path, visited_fore, visited_back};
}
