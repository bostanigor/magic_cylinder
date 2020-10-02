#pragma once
#include "my_structures.h"
#include <unordered_set>
#include <stack>
#include <queue>
#include <vector>
#include <iostream>

State * dfs_recursive(State * current, int depth,
                      std::vector<StateOperation> & operations) {
  if (current->check_solution())
    return current;

  if (depth == 0)
    return nullptr;

  for (auto& op : operations) {
    if (!current->can_move(op._id))
      continue;

    auto new_state = new State(*current);
    new_state->_parent = current;
    op(new_state); new_state->_operation = &op;

    if (*new_state == *current) {
      delete new_state;
      continue;
    }

    auto result = dfs_recursive(new_state, depth - 1, operations);
    if (result != nullptr) {
      return result;
    }
    delete new_state;
  }

  return nullptr;
}

State * resolve_dfs(State * start,
                    std::vector<StateOperation> & operations,
                    int limit=80) {
  return dfs_recursive(start, limit, operations);
}

State * resolve_idfs(State & start,
                     std::vector<StateOperation> & operations) {
  for (int limit = 1; limit < 81; limit++) {
    std::cout << "Limit is : " << limit << std::endl;
    auto copy = new State(start);
    auto result = resolve_dfs(copy, operations, limit);
    if (result != nullptr) {
      return result;
    }
  }
  return nullptr;
}

State * resolve_astar(State & start,
                      std::vector<StateOperation> & operations) {
  std::unordered_set<State, MyHashFunc> state_set;
  std::priority_queue<State*, std::vector<State*>, MyPriorityFunc> state_queue;

  start.update_heuristics(0);
  state_queue.push(&start);

  while(true) {
    auto state = state_queue.top();
    state_queue.pop();

    if (state->check_solution())
      return state;

    auto iter = state_set.find(*state);
    if (iter == state_set.end())
      state_set.insert(*state);
    else {
      int val = iter->_f;
      if (state->_f >= val) {
        (*iter)._g = state->_g;
        (*iter)._f = state->_f;
        (*iter)._parent = state->_parent;
      }
      else
        continue;
    }

    for (auto &op : operations) {
      if (!state->can_move(op._id))
        continue;

      auto new_state = new State(*state);
      new_state->_parent = state;
      op(new_state); new_state->_operation = &op;
      new_state->update_heuristics(state->_g + 1);

      state_queue.push(new_state);
    }
  }
}