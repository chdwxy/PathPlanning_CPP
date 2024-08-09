// env.h
#ifndef ENV_H
#define ENV_H

#include <vector>
#include <utility>

class Env {
public:
    std::vector<std::pair<int, int>> obs_map();

    std::vector<std::pair<int, int>> get_motions();

private:
    std::vector<std::pair<int, int>> obstacles = {{20, 20}, {20, 21}, {20, 22}, {20, 23}, {20, 24},
                                                  {21, 20}, {22, 20}, {23, 20}, {24, 20}};
    std::vector<std::pair<int, int>> motions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1},
                                                {1, 1}, {-1, -1}, {1, -1}, {-1, 1}};
};

#endif // ENV_H
