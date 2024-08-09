// env.cpp
#include "env.hpp"

std::vector<std::pair<int, int>> Env::obs_map() {
    return obstacles;
}

std::vector<std::pair<int, int>> Env::get_motions() {
    return motions;
}
