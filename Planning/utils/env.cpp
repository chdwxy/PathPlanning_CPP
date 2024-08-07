#include "../utils/env.hpp"
#include <algorithm>

// Env::Env() {
//     motions = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}, {1, 1}, {-1, -1}, {1, -1}, {-1, 1}};
//     obs = {{20, 20}, {21, 20}, {22, 20}, {23, 20}, {24, 20}};
// }


Env::Env() {
    x_range = 55;
    y_range = 55;
    obs = obs_map();
    motions = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}, {1, 1}, {-1, -1}, {1, -1}, {-1, 1}}; // 8 directions
}

std::vector<std::pair<int, int>> Env::getMotions() const {
    return motions;
}

std::vector<std::pair<int, int>> Env::getObstacles() const {
    return obs_;
}

bool Env::isObstacle(int x, int y) const {
    return std::find(obs.begin(), obs.end(), std::make_pair(x, y)) != obs.end();
}

void Env::update_obs(const std::set<std::pair<int, int>>& new_obs) {
    obs = new_obs;
}

std::set<std::pair<int, int>> Env::obs_map() {
    std::set<std::pair<int, int>> obs;

    for (int i = 0; i < x_range; ++i) {
        obs.insert({i, 0});
        obs.insert({i, y_range - 1});
    }

    for (int i = 0; i < y_range; ++i) {
        obs.insert({0, i});
        obs.insert({x_range - 1, i});
    }

    for (int i = 10; i < 21; ++i) {
        obs.insert({i, 35});
    }
    for (int i = 0; i < 15; ++i) {
        obs.insert({40, i});
    }

    for (int i = 15; i < 30; ++i) {
        obs.insert({30, i});
    }
    for (int i = 0; i < 16; ++i) {
        obs.insert({50, i});
    }

    return obs;
}