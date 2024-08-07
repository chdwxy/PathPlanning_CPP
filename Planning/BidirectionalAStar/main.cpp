#include <iostream>
#include "B_AStar.hpp"
#include "../utils/plotting.hpp"

int main() {
    std::pair<int, int> x_start = {5, 5};
    std::pair<int, int> x_goal = {45, 25};

    BidirectionalAStar bastar(x_start, x_goal, "euclidean");
    auto path = bastar.searching();

    Plotting plot(x_start, x_goal);
    plot.animationBiAStar(path, {}, {}, "Bidirectional A*");

    return 0;
}
