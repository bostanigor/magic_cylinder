#include "my_structures.h"
#include "State.h"
#include "methods.h"
#include <iostream>

#include <chrono>

using namespace std::chrono;

int main() {
  /*  **********************************
      YOU CAN CHANGE STARTING STATE HERE
      **********************************
  */
//  int matrix[6][5] = {
//      { -1, -1,  1, -1, -1},
//      {  1,  2,  1,  2,  1},
//      {  2,  2,  2,  1,  3},
//      {  3,  3,  3,  3,  4},
//      {  4,  4,  4,  4,  0},
//      {  5,  5,  5,  5,  5},
//  };

  int matrix[6][5] = {
      { -1, -1, -1, -1,  1},
      {  1,  2,  1,  2,  1},
      {  2,  1,  3,  2,  2},
      {  3,  3,  3,  4,  3},
      {  4,  0,  4,  4,  4},
      {  5,  5,  5,  5,  5}
  };
  auto start = State(matrix, nullptr, nullptr);

  if (!check_resolution(start)) {
    std::cout << "No solutions";
    return 0;
  }

  std::vector<StateOperation> operations;

  operations.emplace_back(" UP ",    10, [](State * state) { state->move_zero_up(); });
  operations.emplace_back(" DOWN ", -10, [](State * state) { state->move_zero_down(); });
  for (int i = 0; i < 6; i++) {
    operations.emplace_back(" LEFT " + std::to_string(i), -(i + 1), [i](State * state) { state->move_ring_left(i); });
    operations.emplace_back(" RIGHT " + std::to_string(i),  i + 1,  [i](State * state) { state->move_ring_right(i); });
  }

  auto start_time = high_resolution_clock::now();

  /*  *********************************
      YOU CAN CHANGE SEARCH METHOD HERE
      *********************************
  */
//  auto result = resolve_dfs(start, finish, zero_pos, operations);
//  auto result = resolve_idfs(start, operations);
  auto result = resolve_astar(start, operations);

  auto finish_time = high_resolution_clock::now();

  int count = 0;
  auto node = result;
  while(node != nullptr) {
    draw_state(node);
    if (node->_operation == nullptr)
      std::cout << " START " << std::endl;
    else
      std::cout << node->_operation->_desc << std::endl;
    std::cout << "f=" << node->_f << " g=" << node->_g << " h=" << node->_h << std::endl;
    count++;
    node = node->_parent;
  }

  std::cout << std::dec << count - 1 << " steps" << std::endl;
  std::cout << "It took " << duration_cast<duration<double>>(finish_time - start_time).count() << " seconds" << std::endl;
}