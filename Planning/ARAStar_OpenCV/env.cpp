#include "env.hpp"

Env::Env() {
    x_range = 55;
    y_range = 55;
    obs = obs_map();
    motions = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}, {1, 1}, {-1, -1}, {1, -1}, {-1, 1}}; // 8 directions
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


// #include "env.hpp"

// Env::Env() {
//     initialize_motions();
//     initialize_obstacles();
// }

// void Env::initialize_motions() {
//     motions = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
// }

// void Env::initialize_obstacles() {
//     obs = {{10, 10}, {11, 10}, {12, 10}, {13, 10}, {14, 10}, {15, 10}, {16, 10}, {17, 10}, {18, 10}, {19, 10}};
// }



// #include "env.hpp"

// Env::Env() {
//     motions = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
//     create_obs();
// }

// void Env::create_obs() {
//     for (int x = 0; x < 50; ++x) {
//         obs.insert({x, 0});
//         obs.insert({x, 49});
//     }

//     for (int y = 0; y < 50; ++y) {
//         obs.insert({0, y});
//         obs.insert({49, y});
//     }

//     for (int x = 10; x < 40; ++x) {
//         obs.insert({x, 25});
//     }
// }
