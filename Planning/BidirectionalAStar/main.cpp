#include <iostream>
#include "B_AStar.hpp"
#include "../utils/plotting.hpp"

int main() {
    std::pair<int, int> x_start = {5, 5};
    std::pair<int, int> x_goal = {450, 250};
    Plotting plot(x_start, x_goal);

    // BidirectionalAStar bastar(x_start, x_goal, "euclidean");
    // auto path = bastar.searching();

    // Plotting plot(x_start, x_goal);
    // plot.animationBiAStar(path, {}, {}, "Bidirectional A*");
    
    BidirectionalAStar bAStar(x_start, x_goal, "manhattan");
    bAStar.setPlotting(&plot);

    auto path = bAStar.searching();
    // auto visited = bAStar.getNeighbor();
    // plot.plot_path(path,)
    // plot.animationBiAStar()

    return 0;
}
