//
// Created by chd on 2024/7/26.
//

#include <cmath>
// #include <random>


#include "JPS.hpp"

Node JumpPointSearch::jump(const Node& new_point, const Node& motion,
                           const int id) {
  Node next_point = new_point + motion;
  next_point.id_ = n_ * next_point.x_ + next_point.y_;
  next_point.pid_ = id;
  next_point.h_cost_ =
      std::abs(next_point.x_ - goal_.x_) + std::abs(next_point.y_ - goal_.y_);
  if (next_point.x_ < 0 || next_point.y_ < 0 || next_point.x_ >= n_ ||
      next_point.y_ >= n_ || grid_[next_point.x_][next_point.y_] != 0) {
    // return new_point;
    return Node(-1, -1, -1, -1, -1, -1);
  }
  if (pruned.find(next_point.id_) != pruned.end()) {
    pruned.insert(next_point.id_);
  }
  if (CompareCoordinates(next_point, goal_)) {
    return next_point;
  }
  bool fn = false;
  fn = HasForcedNeighbours(new_point, next_point, motion);
  if (fn) {
    // std::cout << "Forced neighbours found"<<'\n';
    return next_point;
  }
  Node jump_node = jump(next_point, motion, id);
  // Prevent over shoot
  if (jump_node.cost_ != -1 && jump_node.cost_ + jump_node.h_cost_ <=
                                   next_point.cost_ + next_point.h_cost_) {
    return jump_node;
  }
  return next_point;
}

bool JumpPointSearch::HasForcedNeighbours(const Node& new_point,
                                          const Node& next_point,
                                          const Node& motion) const {
  int cn1x = new_point.x_ + motion.y_;
  int cn1y = new_point.y_ + motion.x_;

  int cn2x = new_point.x_ - motion.y_;
  int cn2y = new_point.y_ - motion.x_;

  int nn1x = next_point.x_ + motion.y_;
  int nn1y = next_point.y_ + motion.x_;

  int nn2x = next_point.x_ - motion.y_;
  int nn2y = next_point.y_ - motion.x_;

  bool a = !(cn1x < 0 || cn1y < 0 || cn1x >= n_ || cn1y >= n_ ||
             grid_[cn1x][cn1y] == 1);
  bool b = !(nn1x < 0 || nn1y < 0 || nn1x >= n_ || nn1y >= n_ ||
             grid_[nn1x][nn1y] == 1);
  if (a != b) {
    return true;
  }

  a = !(cn2x < 0 || cn2y < 0 || cn2x >= n_ || cn2y >= n_ ||
        grid_[cn2x][cn2y] == 1);
  b = !(nn2x < 0 || nn2y < 0 || nn2x >= n_ || nn2y >= n_ ||
        grid_[nn2x][nn2y] == 1);
  return a != b;
}

std::tuple<bool, std::vector<Node>> JumpPointSearch::Plan(const Node& start,
                                                          const Node& goal) {
  grid_ = original_grid_;
  start_ = start;
  goal_ = goal;
  // Get possible motions
  std::vector<Node> motion = GetMotion();
  open_list_.push(start_);

  // Main loop
  while (!open_list_.empty()) {
    Node current = open_list_.top();
    open_list_.pop();
    current.id_ = current.x_ * n_ + current.y_;
    if (CompareCoordinates(current, goal_)) {
      closed_list_.push_back(current);
      grid_[current.x_][current.y_] = 2;
      return {true, closed_list_};
    }
    grid_[current.x_][current.y_] = 2;  // Point opened
    for (const auto& m :
         motion) {  // auto it = motion.begin(); it!=motion.end(); ++it){
      Node new_point;
      new_point = current + m;
      new_point.id_ = n_ * new_point.x_ + new_point.y_;
      new_point.pid_ = current.id_;
      new_point.h_cost_ =
          abs(new_point.x_ - goal_.x_) + abs(new_point.y_ - goal_.y_);
      if (CompareCoordinates(new_point, goal_)) {
        open_list_.push(new_point);
        break;
      }
      if (checkOutsideBoundary(new_point, n_)) {
        continue;  // Check boundaries
      }
      if (grid_[new_point.x_][new_point.y_] != 0) {
        continue;  // obstacle or visited
      }

      Node jump_point = jump(new_point, m, current.id_);
      if (jump_point.id_ != -1) {
        open_list_.push(jump_point);
        if (CompareCoordinates(jump_point, goal_)) {
          closed_list_.push_back(current);
          closed_list_.push_back(jump_point);
          grid_[jump_point.x_][jump_point.y_] = 2;
          return {true, closed_list_};
        }
      }
      open_list_.push(new_point);
    }
    closed_list_.push_back(current);
  }
  return {false, {}};
}


