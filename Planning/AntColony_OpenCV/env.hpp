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
    // std::vector<std::pair<int, int>> motions; // Possible movements

    void update_obs(const std::set<std::pair<int, int>>& new_obs);

private:
    std::set<std::pair<int, int>> obs_map();
};

#endif // ENV_H
