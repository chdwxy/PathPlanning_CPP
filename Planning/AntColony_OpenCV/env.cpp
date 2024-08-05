#include "env.hpp"

Env::Env() {
    x_range = 51;
    y_range = 31;
    obs = obs_map();
    // motions = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}, {1, 1}, {-1, -1}, {1, -1}, {-1, 1}}; // 8 directions
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
        obs.insert({i, 15});
    }
    for (int i = 0; i < 15; ++i) {
        obs.insert({20, i});
    }

    for (int i = 15; i < 30; ++i) {
        obs.insert({30, i});
    }
    for (int i = 0; i < 16; ++i) {
        obs.insert({40, i});
    }

    return obs;
}
