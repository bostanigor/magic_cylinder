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
  int matrix[6][5] = {
      { -1, -1,  1, -1, -1},
      {  1,  1,  1,  2,  1},
      {  2,  2,  2,  3,  2},
      {  3,  3,  4,  3,  3},
      {  4,  4,  0,  4,  4},
      {  5,  5,  5,  5,  5},
  };
  auto start = State(matrix, nullptr, nullptr);

  // TODO: Check solution existence

  std::vector<StateOperation> operations;

  operations.push_back(StateOperation(" UP ",   10, [](State * state) { state->move_zero_up(); }));
  operations.push_back(StateOperation(" DOWN ",-10, [](State * state) { state->move_zero_down(); }));
  for (int i = 0; i < 6; i++) {
    operations.push_back(StateOperation(
      " LEFT " + std::to_string(i), -(i + 1), [i](State * state) { state->move_ring_left(i); }));
    operations.push_back(StateOperation(
      " RIGHT " + std::to_string(i), i + 1,   [i](State * state) { state->move_ring_right(i); }));
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