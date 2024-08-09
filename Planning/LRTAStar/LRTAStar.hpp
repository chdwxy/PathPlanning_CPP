#ifndef LRTASTAR_HPP
#define LRTASTAR_HPP

#include <vector>
#include <unordered_map>
#include <queue>
#include <cmath>
#include "../utils/env.hpp"
#include "../utils/plotting.hpp"



class LrtAStarN {
public:
    LrtAStarN(std::pair<int, int> s_start, std::pair<int, int> s_goal, int N, const std::string& heuristic_type);
    void searching();
    const std::vector<std::vector<std::pair<int, int>>>& getPath() const;
    const std::vector<std::vector<std::pair<int, int>>>& getVisited() const;
    // 自定义哈希函数
    struct pair_hash {
        template <class T1, class T2>
        std::size_t operator()(const std::pair<T1, T2>& p) const {
            auto hash1 = std::hash<T1>{}(p.first);
            auto hash2 = std::hash<T2>{}(p.second);
            return hash1 ^ hash2; // 简单地将两个哈希值异或
        }
    };

private:
    void init();
    // std::pair<int, int> extract_path_in_CLOSE(std::pair<int, int> s_start, const std::unordered_map<std::pair<int, int>, double, pair_hash>& h_value);
    // std::pair<std::pair<int, int>, std::vector<std::pair<int, int>>> extract_path_in_CLOSE(
    // std::pair<int, int> s_start, 
    // const std::unordered_map<std::pair<int, int>, double, pair_hash>& h_value);
    std::vector<std::pair<int, int>> extract_path_in_CLOSE(
    std::pair<int, int> s_start, 
    const std::unordered_map<std::pair<int, int>, double, pair_hash>& h_value);


    std::unordered_map<std::pair<int, int>, double, pair_hash> iteration(const std::vector<std::pair<int, int>>& CLOSED);
    std::pair<std::queue<std::pair<int, int>>, std::vector<std::pair<int, int>>> AStar(std::pair<int, int> x_start, int N);
    std::vector<std::pair<int, int>> get_neighbor(const std::pair<int, int>& s) const;
    std::vector<std::pair<int, int>> extract_path(std::pair<int, int> x_start, const std::unordered_map<std::pair<int, int>, std::pair<int, int>, pair_hash>& parent) const;
    double h(const std::pair<int, int>& s) const;
    double cost(const std::pair<int, int>& s_start, const std::pair<int, int>& s_goal) const;
    bool is_collision(const std::pair<int, int>& s_start, const std::pair<int, int>& s_end) const;

    std::pair<int, int> s_start_, s_goal_;
    std::string heuristic_type_;
    Env env_;
    int N_;
    std::vector<std::vector<std::pair<int, int>>> visited_;
    std::vector<std::vector<std::pair<int, int>>> path_;
    std::unordered_map<std::pair<int, int>, double, pair_hash> h_table_;

    // struct pair_hash {
    //     template <class T1, class T2>
    //     std::size_t operator () (const std::pair<T1,T2>& p) const {
    //         auto h1 = std::hash<T1>{}(p.first);
    //         auto h2 = std::hash<T2>{}(p.second);
    //         return h1 ^ h2; // or use boost::hash_combine
    //     }
    // };
};

#endif // LRTASTAR_HPP
