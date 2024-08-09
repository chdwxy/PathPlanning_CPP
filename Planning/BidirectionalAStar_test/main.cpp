// main.cpp
#include "bidirectional_a_star.hpp"
// #include "plotting.hpp"
#include "../utils/plotting.hpp"

int main() {
    std::pair<int, int> x_start = {10, 5};
    std::pair<int, int> x_goal = {90, 90};

    BidirectionalAStar bastar(x_start, x_goal, "euclidean");
    Plotting plot(x_start, x_goal);

    auto [path, visited_fore, visited_back] = bastar.searching();
    // plot.animation(path, visited_fore, "Bidirectional A* Search");                       // #include "plotting.hpp"
    // plot.animationBiAStarTest(path, visited_fore, visited_back, "Bidirectional A* Search");                       // #include "../utils/plotting.hpp"
    plot.plot_path(path, visited_fore, "Bidirectional A* Search");                       // #include "../utils/plotting.hpp"

    return 0;
}
