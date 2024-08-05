// #include "arastar.hpp"
// #include <iostream>

// int main() {
//     std::pair<int, int> s_start = {5, 5};
//     std::pair<int, int> s_goal = {45, 45};
//     double epsilon = 2.5;
//     std::string heuristic_type = "euclidean";

//     AraStar arastar(s_start, s_goal, epsilon, heuristic_type);
//     auto paths = arastar.searching();

//     for (const auto& path : paths) {
//         std::cout << "Path: ";
//         for (const auto& p : path) {
//             std::cout << "(" << p.first << ", " << p.second << ") ";
//         }
//         std::cout << std::endl;
//     }

//     return 0;
// }


#include "arastar.hpp"
#include <iostream>

int main() {
    std::pair<int, int> s_start = {5, 5};
    std::pair<int, int> s_goal = {45, 25};
    double epsilon = 2.5;
    std::string heuristic_type = "euclidean";

    AraStar arastar(s_start, s_goal, epsilon, heuristic_type);
    auto paths = arastar.searching();

    for (const auto& path : paths) {
        std::cout << "Path: ";
        for (const auto& p : path) {
            std::cout << "(" << p.first << ", " << p.second << ") ";
        }
        std::cout << std::endl;
    }

    return 0;
}
