#include"LPAStar.hpp"
#include<vector>
#include<random>

/**
 * @brief Script main function. Generates start and end nodes as well as grid,
 * then creates the algorithm object and calls the main algorithm function.
 * @return 0
 */
int main() {
  constexpr int n = 11;
  std::vector<std::vector<int>> grid(n, std::vector<int>(n, 0));
  MakeGrid(grid);

  std::random_device rd;   // obtain a random number from hardware
  std::mt19937 eng(rd());  // seed the generator
  std::uniform_int_distribution<int> distr(0, n - 1);  // define the range

  Node start(distr(eng), distr(eng), 0, 0, 0, 0);
  Node goal(distr(eng), distr(eng), 0, 0, 0, 0);

  start.id_ = start.x_ * n + start.y_;
  start.pid_ = start.x_ * n + start.y_;
  goal.id_ = goal.x_ * n + goal.y_;
  start.h_cost_ = abs(start.x_ - goal.x_) + abs(start.y_ - goal.y_);

  // Make sure start and goal are not obstacles and their ids are correctly
  // assigned.
  grid[start.x_][start.y_] = 0;
  grid[goal.x_][goal.y_] = 0;

  start.PrintStatus();
  goal.PrintStatus();

  PrintGrid(grid);

  const bool create_random_obstacles = false;
  const std::unordered_map<int, std::vector<Node>> time_discovered_obstacles{
      {1, {Node(1, 1)}},
      {2, {Node(2, 2)}},
      {3, {Node(5, 5)}},
      {4,
       {Node(6, 6), Node(7, 7), Node(8, 8), Node(9, 9), Node(10, 10),
        Node(7, 6)}}};

  LPAStar lpa_star(grid);
  lpa_star.SetDynamicObstacles(create_random_obstacles,
                               time_discovered_obstacles);
  const auto [found_path, path_vector] = lpa_star.Plan(start, goal);
  PrintPath(path_vector, start, goal, grid);
  return 0;
}
