#ifndef ENV_HPP
#define ENV_HPP

#include <vector>
#include <set>
#include <utility>

class Env {
public:
    std::vector<std::pair<int, int>> motions;
    std::set<std::pair<int, int>> obs;
    int x_range; // size of background
    int y_range;
    void update_obs(const std::set<std::pair<int, int>>& new_obs);
    Env();

private:
    std::set<std::pair<int, int>> obs_map();

};

#endif // ENV_HPP
