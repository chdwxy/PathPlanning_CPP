#ifndef ENV_HPP
#define ENV_HPP

#include <vector>
#include <set>

class Env {
public:
    std::vector<std::pair<int, int>> motions;
    std::set<std::pair<int, int>> obs;

    Env();
};

#endif // ENV_HPP
