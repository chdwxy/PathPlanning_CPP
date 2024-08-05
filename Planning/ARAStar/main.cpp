#include "arastar.hpp"
#include "../utils/plotting.hpp"

int main() {
    std::pair<int, int> s_start(5, 5);
    std::pair<int, int> s_goal(45, 45);

    AraStar arastar(s_start, s_goal, 2.5, "euclidean");
    Plotting plot(s_start, s_goal);

    // auto [path, visited] = arastar.searching();
    auto path = arastar.searching();
    auto visited = arastar.ImprovePath ();
    // auto result = arastar.searching();
    // auto& path = result.first;
    // auto& visited = result.second;
    

    plot.animation_ara_star(path, visited,  "Anytime Repairing A* (ARA*)");

    return 0;
}
