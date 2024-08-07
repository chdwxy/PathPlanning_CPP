#include "B_AStar.hpp"
#include <cmath>
#include <limits>
#include <utility>
#include <algorithm>
using namespace std;

BidirectionalAStar::BidirectionalAStar(std::pair<int, int> start, std::pair<int, int> goal, const std::string& heuristicType)
    : s_start(start), s_goal(goal), heuristic_type(heuristicType) {
    g_fore[s_start] = 0.0;
    g_fore[s_goal] = std::numeric_limits<double>::infinity();
    g_back[s_goal] = 0.0;
    g_back[s_start] = std::numeric_limits<double>::infinity();
    PARENT_fore[s_start] = s_start;
    PARENT_back[s_goal] = s_goal;
    OPEN_fore.push({fValueFore(s_start), s_start});
    OPEN_back.push({fValueBack(s_goal), s_goal});
}

std::vector<std::pair<int, int>> BidirectionalAStar::searching() {
    std::pair<int, int> s_meet = s_start;

    while (!OPEN_fore.empty() && !OPEN_back.empty()) {
        auto [_, s_fore] = OPEN_fore.top(); OPEN_fore.pop();

        if (PARENT_back.find(s_fore) != PARENT_back.end()) {
            s_meet = s_fore;
            break;
        }

        CLOSED_fore.push_back(s_fore);

        for (const auto& s_n : getNeighbor(s_fore)) {
            double new_cost = g_fore[s_fore] + cost(s_fore, s_n);

            if (g_fore.find(s_n) == g_fore.end()) {
                g_fore[s_n] = std::numeric_limits<double>::infinity();
            }

            if (new_cost < g_fore[s_n]) {
                g_fore[s_n] = new_cost;
                PARENT_fore[s_n] = s_fore;
                OPEN_fore.push({fValueFore(s_n), s_n});
            }
        }

        auto [__, s_back] = OPEN_back.top(); OPEN_back.pop();

        if (PARENT_fore.find(s_back) != PARENT_fore.end()) {
            s_meet = s_back;
            break;
        }

        CLOSED_back.push_back(s_back);

        for (const auto& s_n : getNeighbor(s_back)) {
            double new_cost = g_back[s_back] + cost(s_back, s_n);

            if (g_back.find(s_n) == g_back.end()) {
                g_back[s_n] = std::numeric_limits<double>::infinity();
            }

            if (new_cost < g_back[s_n]) {
                g_back[s_n] = new_cost;
                PARENT_back[s_n] = s_back;
                OPEN_back.push({fValueBack(s_n), s_n});
            }
        }
    }

    return extractPath(s_meet);
}

std::vector<std::pair<int, int>> BidirectionalAStar::getNeighbor(const std::pair<int, int>& s) {
    std::vector<std::pair<int, int>> neighbors;
    for (const auto& u : env.getMotions()) {
        std::pair<int, int> neighbor = {s.first + u.first, s.second + u.second};
        if (!env.isObstacle(neighbor.first, neighbor.second)) {
            neighbors.push_back(neighbor);
        }
    }
    return neighbors;
}

std::vector<std::pair<int, int>> BidirectionalAStar::extractPath(const std::pair<int, int>& s_meet) {
    std::vector<std::pair<int, int>> path_fore, path_back, path;
    path_fore.push_back(s_meet);
    path_back.push_back(s_meet);

    auto s = s_meet;
    while (s != s_start) {
        s = PARENT_fore[s];
        path_fore.push_back(s);
    }
    std::reverse(path_fore.begin(), path_fore.end());

    s = s_meet;
    while (s != s_goal) {
        s = PARENT_back[s];
        path_back.push_back(s);
    }

    path.insert(path.end(), path_fore.begin(), path_fore.end());
    path.insert(path.end(), path_back.begin() + 1, path_back.end());

    return path;
}

double BidirectionalAStar::fValueFore(const std::pair<int, int>& s) {
    return g_fore[s] + heuristic(s, s_goal);
}

double BidirectionalAStar::fValueBack(const std::pair<int, int>& s) {
    return g_back[s] + heuristic(s, s_start);
}

double BidirectionalAStar::heuristic(const std::pair<int, int>& s, const std::pair<int, int>& goal) {
    if (heuristic_type == "manhattan") {
        return std::abs(goal.first - s.first) + std::abs(goal.second - s.second);
    } else {
        return std::hypot(goal.first - s.first, goal.second - s.second);
    }
}

double BidirectionalAStar::cost(const std::pair<int, int>& s_start, const std::pair<int, int>& s_goal) {
    if (env.isObstacle(s_start.first, s_start.second) || env.isObstacle(s_goal.first, s_goal.second)) {
        return std::numeric_limits<double>::infinity();
    }
    return std::hypot(s_goal.first - s_start.first, s_goal.second - s_start.second);
}
