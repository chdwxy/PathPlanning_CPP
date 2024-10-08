#include "arastar.hpp"
#include <algorithm>
#include <limits>
#include <string>

AraStar::AraStar(std::pair<int, int> s_start, std::pair<int, int> s_goal, double e, std::string heuristic_type)
    : s_start(s_start), s_goal(s_goal), e(e), heuristic_type(heuristic_type), env() {
    u_set = env.motions;
    obs = env.obs;
}

void AraStar::init() {
    g[s_start] = 0.0;
    g[s_goal] = std::numeric_limits<double>::infinity();
    OPEN[s_start] = f_value(s_start);
    PARENT[s_start] = s_start;
}

std::vector<std::vector<std::pair<int, int>>> AraStar::searching() {
// std::pair<std::vector<std::vector<std::pair<int, int>>>, std::vector<std::pair<int, int>>> AraStar::searching() {
    init();
    ImprovePath();
    path.push_back(extract_path());

    while (update_e() > 1) {
        e -= 0.4;
        OPEN.insert(INCONS.begin(), INCONS.end());
        for (auto &s : OPEN) {
            s.second = f_value(s.first);
        }

        INCONS.clear();
        CLOSED.clear();
        ImprovePath();
        path.push_back(extract_path());
    }

    return path;
}

std::vector<std::vector<std::pair<int, int>>>  AraStar::ImprovePath() {
    std::vector<std::pair<int, int>> visited_each;

    while (true) {
        auto s_f_pair = calc_smallest_f();
        auto s = s_f_pair.first;
        double f_small = s_f_pair.second;

        if (f_value(s_goal) <= f_small) {
            break;
        }

        OPEN.erase(s);
        CLOSED.insert(s);

        for (auto s_n : get_neighbor(s)) {
            if (obs.count(s_n)) continue;

            double new_cost = g[s] + cost(s, s_n);

            if (!g.count(s_n) || new_cost < g[s_n]) {
                g[s_n] = new_cost;
                PARENT[s_n] = s;
                visited_each.push_back(s_n);

                if (!CLOSED.count(s_n)) {
                    OPEN[s_n] = f_value(s_n);
                } else {
                    INCONS[s_n] = 0.0;
                }
            }
        }
    }

    visited.push_back(visited_each);
    return visited;
}

std::pair<std::pair<int, int>, double> AraStar::calc_smallest_f() {
    auto it = std::min_element(OPEN.begin(), OPEN.end(),
        [](const auto &a, const auto &b) { return a.second < b.second; });
    return *it;
}

std::set<std::pair<int, int>> AraStar::get_neighbor(std::pair<int, int> s) {
    std::set<std::pair<int, int>> neighbors;
    for (auto u : u_set) {
        neighbors.insert({s.first + u.first, s.second + u.second});
    }
    return neighbors;
}

double AraStar::update_e() {
    double v = std::numeric_limits<double>::infinity();

    if (!OPEN.empty()) {
        v = std::min(v, std::min_element(OPEN.begin(), OPEN.end(),
            [&](const auto &a, const auto &b) {
                return g[a.first] + h(a.first) < g[b.first] + h(b.first);
            })->second);
    }

    if (!INCONS.empty()) {
        v = std::min(v, std::min_element(INCONS.begin(), INCONS.end(),
            [&](const auto &a, const auto &b) {
                return g[a.first] + h(a.first) < g[b.first] + h(b.first);
            })->second);
    }

    return std::min(e, g[s_goal] / v);
}

double AraStar::f_value(std::pair<int, int> x) {
    return g[x] + e * h(x);
}

std::vector<std::pair<int, int>> AraStar::extract_path() {
    std::vector<std::pair<int, int>> path;
    path.push_back(s_goal);
    auto s = s_goal;

    while (s != s_start) {
        s = PARENT[s];
        path.push_back(s);
    }

    return path;
}

double AraStar::h(std::pair<int, int> s) {
    if (heuristic_type == "manhattan") {
        return std::abs(s_goal.first - s.first) + std::abs(s_goal.second - s.second);
    } else {
        return std::hypot(s_goal.first - s.first, s_goal.second - s.second);
    }
}

double AraStar::cost(std::pair<int, int> s_start, std::pair<int, int> s_goal) {
    if (is_collision(s_start, s_goal)) {
        return std::numeric_limits<double>::infinity();
    }
    return std::hypot(s_goal.first - s_start.first, s_goal.second - s_start.second);
}

bool AraStar::is_collision(std::pair<int, int> s_start, std::pair<int, int> s_end) {
    if (obs.count(s_start) || obs.count(s_end)) {
        return true;
    }

    if (s_start.first != s_end.first && s_start.second != s_end.second) {
        std::pair<int, int> s1, s2;
        if (s_end.first - s_start.first == s_start.second - s_end.second) {
            s1 = {std::min(s_start.first, s_end.first), std::min(s_start.second, s_end.second)};
            s2 = {std::max(s_start.first, s_end.first), std::max(s_start.second, s_end.second)};
        } else {
            s1 = {std::min(s_start.first, s_end.first), std::max(s_start.second, s_end.second)};
            s2 = {std::max(s_start.first, s_end.first), std::min(s_start.second, s_end.second)};
        }

        if (obs.count(s1) || obs.count(s2)) {
            return true;
        }
    }

    return false;
}
