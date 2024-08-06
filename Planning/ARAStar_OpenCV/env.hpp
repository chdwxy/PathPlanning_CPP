#ifndef ENV_H
#define ENV_H

#include <set>
#include <utility>
#include <vector>

class Env {
public:
    Env();
    int x_range; // size of background
    int y_range;
    std::set<std::pair<int, int>> obs; // obstacles
    std::vector<std::pair<int, int>> motions; // Possible movements

    void update_obs(const std::set<std::pair<int, int>>& new_obs);

private:
    std::set<std::pair<int, int>> obs_map();
};

#endif // ENV_H



// #ifndef ENV_H
// #define ENV_H

// #include <vector>
// #include <set>
// #include <utility>

// class Env {
// public:
//     Env();
//     std::vector<std::pair<int, int>> motions;
//     std::set<std::pair<int, int>> obs;

// private:
//     void initialize_motions();
//     void initialize_obstacles();
// };

// #endif // ENV_H


// #ifndef ENV_HPP
// #define ENV_HPP

// #include <set>
// #include <utility>
// #include <vector>

// class Env {
// public:
//     Env();
//     std::set<std::pair<int, int>> obs;
//     std::vector<std::pair<int,int>> motions;

// private:
//     void create_obs();
// };

// #endif // ENV_HPP
