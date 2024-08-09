#include "LRTAStar.hpp"
#include "../utils/plotting.hpp"

int main() {
    std::pair<int, int> s_start = {10, 5};
    std::pair<int, int> s_goal = {45, 25};

    LrtAStarN lrta(s_start, s_goal, 250, "euclidean");
    Plotting plot(s_start, s_goal);

    // lrta.searching();
    lrta.searching();
    plot.animation_lrta(lrta.getPath(), lrta.getVisited(), "Learning Real-time A* (LRTA*)");

    return 0;
}
