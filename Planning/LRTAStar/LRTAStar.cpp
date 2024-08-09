#include "LRTAStar.hpp"
#include <queue>
#include <algorithm>
#include <cmath>
#include <limits>
#include <iostream>

LrtAStarN::LrtAStarN(std::pair<int, int> s_start, std::pair<int, int> s_goal, int N, const std::string& heuristic_type)
    : s_start_(s_start), s_goal_(s_goal), N_(N), heuristic_type_(heuristic_type) {
    env_.initialize();
}

void LrtAStarN::init() {
    for (int i = 0; i < env_.x_range; ++i) {
        for (int j = 0; j < env_.y_range; ++j) {
            h_table_[{i, j}] = h({i, j});
        }
    }
}

// std::pair<int, int> LrtAStarN::extract_path_in_CLOSE(std::pair<int, int> s_start, const std::unordered_map<std::pair<int, int>, double, pair_hash>& h_value) {
//     std::vector<std::pair<int, int>> path;
//     path.push_back(s_start);

//     while (true) {
//         std::unordered_map<std::pair<int, int>, double, pair_hash> h_list;
//         for (const auto& s_n : get_neighbor(s_start)) {
//             h_list[s_n] = (h_value.find(s_n) != h_value.end()) ? h_value.at(s_n) : h_table_.at(s_n);
//         }

//         auto s_key = std::min_element(h_list.begin(), h_list.end(), [](const auto& a, const auto& b) {
//             return a.second < b.second;
//         })->first;

//         path.push_back(s_key);
//         s_start = s_key;

//         if (h_value.find(s_key) == h_value.end()) {
//             return {s_key, path};
//         }
//     }
// }
// std::pair<std::pair<int, int>, std::vector<std::pair<int, int>>> LrtAStarN::extract_path_in_CLOSE(
//     std::pair<int, int> s_start, 
//     const std::unordered_map<std::pair<int, int>, double, pair_hash>& h_value) {
    
//     std::vector<std::pair<int, int>> path;
//     path.push_back(s_start);

//     while (true) {
//         std::unordered_map<std::pair<int, int>, double, pair_hash> h_list;
//         for (const auto& s_n : get_neighbor(s_start)) {
//             h_list[s_n] = (h_value.find(s_n) != h_value.end()) ? h_value.at(s_n) : h_table_.at(s_n);
//         }

//         auto s_key = std::min_element(h_list.begin(), h_list.end(), [](const auto& a, const auto& b) {
//             return a.second < b.second;
//         })->first;

//         path.push_back(s_key);
//         s_start = s_key;

//         if (h_value.find(s_key) == h_value.end()) {
//             return {s_key, path};  // 返回最终点和路径
//         }
//     }
// }

std::vector<std::pair<int, int>> LrtAStarN::extract_path_in_CLOSE(
    std::pair<int, int> s_start, 
    const std::unordered_map<std::pair<int, int>, double, pair_hash>& h_value) {
    
    std::vector<std::pair<int, int>> path;
    path.push_back(s_start);

    while (true) {
        std::unordered_map<std::pair<int, int>, double, pair_hash> h_list;
        for (const auto& s_n : get_neighbor(s_start)) {
            h_list[s_n] = (h_value.find(s_n) != h_value.end()) ? h_value.at(s_n) : h_table_.at(s_n);
        }

        auto s_key = std::min_element(h_list.begin(), h_list.end(), [](const auto& a, const auto& b) {
            return a.second < b.second;
        })->first;

        path.push_back(s_key);
        s_start = s_key;

        // 当找到路径的终点时，返回路径
        if (h_value.find(s_key) == h_value.end()) {
            return path;
        }
    }
}



std::unordered_map<std::pair<int, int>, double, LrtAStarN::pair_hash> LrtAStarN::iteration(const std::vector<std::pair<int, int>>& CLOSED) {
    std::unordered_map<std::pair<int, int>, double, pair_hash> h_value;

    for (const auto& s : CLOSED) {
        h_value[s] = std::numeric_limits<double>::infinity();
    }

    while (true) {
        auto h_value_rec = h_value;
        for (const auto& s : CLOSED) {
            std::vector<double> h_list;
            for (const auto& s_n : get_neighbor(s)) {
                if (std::find(CLOSED.begin(), CLOSED.end(), s_n) == CLOSED.end()) {
                    h_list.push_back(cost(s, s_n) + h_table_.at(s_n));
                } else {
                    h_list.push_back(cost(s, s_n) + h_value.at(s_n));
                }
            }
            h_value[s] = *std::min_element(h_list.begin(), h_list.end());
        }

        if (h_value == h_value_rec) {
            return h_value;
        }
    }
}

// std::pair<std::queue<std::pair<int, int>>, std::vector<std::pair<int, int>>> LrtAStarN::AStar(std::pair<int, int> x_start, int N) {
//     std::priority_queue<std::pair<double, std::pair<int, int>>, std::vector<std::pair<double, std::pair<int, int>>>, std::greater<>> OPEN;
//     OPEN.push({h(x_start), x_start});
//     std::vector<std::pair<int, int>> CLOSED;
//     std::unordered_map<std::pair<int, int>, double, pair_hash> g_table;
//     g_table[x_start] = 0;
//     g_table[s_goal_] = std::numeric_limits<double>::infinity();
//     std::unordered_map<std::pair<int, int>, std::pair<int, int>, pair_hash> PARENT;
//     PARENT[x_start] = x_start;

//     int count = 0;
//     while (!OPEN.empty()) {
//         ++count;
//         auto s = OPEN.top().second;
//         OPEN.pop();
//         CLOSED.push_back(s);

//         if (s == s_goal_) {
//             visited_.push_back(CLOSED);
//             return {OPEN, CLOSED};
//         }

//         for (const auto& s_n : get_neighbor(s)) {
//             if (std::find(CLOSED.begin(), CLOSED.end(), s_n) == CLOSED.end()) {
//                 double new_cost = g_table[s] + cost(s, s_n);
//                 if (g_table.find(s_n) == g_table.end()) {
//                     g_table[s_n] = std::numeric_limits<double>::infinity();
//                 }
//                 if (new_cost < g_table[s_n]) {
//                     g_table[s_n] = new_cost;
//                     PARENT[s_n] = s;
//                     OPEN.push({g_table[s_n] + h_table_.at(s_n), s_n});
//                 }
//             }
//         }

//         if (count == N) {
//             break;
//         }
//     }

//     visited_.push_back(CLOSED);
//     return {OPEN, CLOSED};
// }

std::pair<std::queue<std::pair<int, int>>, std::vector<std::pair<int, int>>>
LrtAStarN::AStar(std::pair<int, int> x_start, int N) {
    std::priority_queue<std::pair<double, std::pair<int, int>>,
        std::vector<std::pair<double, std::pair<int, int>>>,
        std::greater<>> OPEN;
    OPEN.push({h(x_start), x_start});
    std::vector<std::pair<int, int>> CLOSED;
    std::unordered_map<std::pair<int, int>, double, pair_hash> g_table;
    g_table[x_start] = 0;
    g_table[s_goal_] = std::numeric_limits<double>::infinity();
    std::unordered_map<std::pair<int, int>, std::pair<int, int>, pair_hash> PARENT;
    PARENT[x_start] = x_start;

    int count = 0;
    while (!OPEN.empty()) {
        ++count;
        auto s = OPEN.top().second;
        OPEN.pop();
        CLOSED.push_back(s);

        if (s == s_goal_) {
            visited_.push_back(CLOSED);
            return {std::queue<std::pair<int, int>>(), CLOSED};
        }

        for (const auto& s_n : get_neighbor(s)) {
            if (std::find(CLOSED.begin(), CLOSED.end(), s_n) == CLOSED.end()) {
                double new_cost = g_table[s] + cost(s, s_n);
                if (g_table.find(s_n) == g_table.end()) {
                    g_table[s_n] = std::numeric_limits<double>::infinity();
                }
                if (new_cost < g_table[s_n]) {
                    g_table[s_n] = new_cost;
                    PARENT[s_n] = s;
                    OPEN.push({g_table[s_n] + h_table_.at(s_n), s_n});
                }
            }
        }

        if (count == N) {
            break;
        }
    }

    visited_.push_back(CLOSED);

    // Convert OPEN priority queue to a standard queue
    std::queue<std::pair<int, int>> open_queue;
    while (!OPEN.empty()) {
        open_queue.push(OPEN.top().second);
        OPEN.pop();
    }

    return {open_queue, CLOSED};
}

std::vector<std::pair<int, int>> LrtAStarN::get_neighbor(const std::pair<int, int>& s) const {
    std::vector<std::pair<int, int>> s_list;
    for (const auto& u : env_.motions) {
        std::pair<int, int> s_next = {s.first + u.first, s.second + u.second};
        if (std::find(env_.obs.begin(), env_.obs.end(), s_next) == env_.obs.end()) {
            s_list.push_back(s_next);
        }
    }
    return s_list;
}

std::vector<std::pair<int, int>> LrtAStarN::extract_path(std::pair<int, int> x_start, const std::unordered_map<std::pair<int, int>, std::pair<int, int>, pair_hash>& parent) const {
    std::vector<std::pair<int, int>> path;
    std::pair<int, int> x_current = s_goal_;
    while (x_current != x_start) {
        path.push_back(x_current);
        x_current = parent.at(x_current);
    }
    path.push_back(x_start);
    std::reverse(path.begin(), path.end());
    return path;
}

double LrtAStarN::h(const std::pair<int, int>& s) const {
    if (heuristic_type_ == "manhattan") {
        return std::abs(s_goal_.first - s.first) + std::abs(s_goal_.second - s.second);
    } else {
        return std::hypot(s_goal_.first - s.first, s_goal_.second - s.second);
    }
}

double LrtAStarN::cost(const std::pair<int, int>& s_start, const std::pair<int, int>& s_goal) const {
    if (is_collision(s_start, s_goal)) {
        return std::numeric_limits<double>::infinity();
    }
    return std::hypot(s_goal.first - s_start.first, s_goal.second - s_start.second);
}

bool LrtAStarN::is_collision(const std::pair<int, int>& s_start, const std::pair<int, int>& s_end) const {
    if (std::find(env_.obs.begin(), env_.obs.end(), s_start) != env_.obs.end() ||
        std::find(env_.obs.begin(), env_.obs.end(), s_end) != env_.obs.end()) {
        return true;
    }
    if (s_start.first != s_end.first && s_start.second != s_end.second) {
        if (s_end.first - s_start.first == s_start.second - s_end.second) {
            std::pair<int, int> s1 = {std::min(s_start.first, s_end.first), std::min(s_start.second, s_end.second)};
            std::pair<int, int> s2 = {std::max(s_start.first, s_end.first), std::max(s_start.second, s_end.second)};
            return (std::find(env_.obs.begin(), env_.obs.end(), s1) != env_.obs.end()) ||
                   (std::find(env_.obs.begin(), env_.obs.end(), s2) != env_.obs.end());
        }
    }
    return false;
}

const std::vector<std::vector<std::pair<int, int>>>& LrtAStarN::getPath() const {
    return path_;
}

const std::vector<std::vector<std::pair<int, int>>>& LrtAStarN::getVisited() const {
    return visited_;
}
