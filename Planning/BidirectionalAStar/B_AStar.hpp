#ifndef B_ASTAR_HPP
#define B_ASTAR_HPP

#include <vector>
#include <unordered_map>
#include <queue>
#include <utility>
#include <string>
#include <utility>
#include "../utils/env.hpp"
#include "../utils/plotting.hpp"

// 自定义哈希函数
struct pair_hash {
    template <class T1, class T2>
    std::size_t operator()(const std::pair<T1, T2>& p) const {
        auto hash1 = std::hash<T1>{}(p.first);
        auto hash2 = std::hash<T2>{}(p.second);
        return hash1 ^ hash2; // 简单地将两个哈希值异或
    }
};

class BidirectionalAStar {
public:
    BidirectionalAStar(std::pair<int, int> start, std::pair<int, int> goal, const std::string& heuristicType);
    std::vector<std::pair<int, int>> searching();
    void setPlotting(Plotting* plot) { plotting = plot; }
    std::vector<std::pair<int, int>> getNeighbor(const std::pair<int, int>& s);

private:
    std::pair<int, int> s_start;
    std::pair<int, int> s_goal;
    std::string heuristic_type;
    Env env;
    Plotting* plotting;

    std::priority_queue<std::pair<double, std::pair<int, int>>, 
        std::vector<std::pair<double, std::pair<int, int>>>, 
        std::greater<std::pair<double, std::pair<int, int>>>> OPEN_fore, OPEN_back;

    std::vector<std::pair<int, int>> CLOSED_fore, CLOSED_back;

    std::unordered_map<std::pair<int, int>, double, pair_hash> g_fore;
    std::unordered_map<std::pair<int, int>, double, pair_hash> g_back;
    std::unordered_map<std::pair<int, int>, std::pair<int, int>, pair_hash> PARENT_fore;
    std::unordered_map<std::pair<int, int>, std::pair<int, int>, pair_hash> PARENT_back;
    // std::priority_queue<std::pair<double, std::pair<int, int>>> OPEN_fore;
    // std::priority_queue<std::pair<double, std::pair<int, int>>> OPEN_back;

    
    std::vector<std::pair<int, int>> extractPath(const std::pair<int, int>& s_meet);
    double fValueFore(const std::pair<int, int>& s);
    double fValueBack(const std::pair<int, int>& s);
    double heuristic(const std::pair<int, int>& s, const std::pair<int, int>& goal);
    double cost(const std::pair<int, int>& s_start, const std::pair<int, int>& s_goal);

};

#endif  // B_ASTAR_HPP
