#pragma once
#include <string>
#include <iostream>
#include "State.h"

bool check_resolution(State & start) {
  return true;
}

void draw_state(const State * state) {
  for (int i = 0; i < 6; i++) {
    std::cout << "|";
    for (int j = 0; j < 5; j++) {
      auto val = state->_rings[i * 5 + j];
      switch (val) {
        case -1: std::cout << "-"; break;
        case 0:  std::cout << " "; break;
        default: std::cout << val; break;
      }
      std::cout << "|";
    }
    std::cout << "  " << state->_rotation_counts[i] << std::endl;
  }
}

bool operator==(const State & left, const State & right) {
  for (int i = 0; i < 30; i++)
    if (left._rings[i] != right._rings[i])
      return false;
  return true;
}

struct MyHashFunc {
  size_t operator()(const State & state) {
//    auto temp = (size_t)(state.value);
//    return temp;
    return (size_t)(state._rings);
  };
};

struct MyPriorityFunc {
    size_t operator()(const State * left, const State * right) {
      return left->_f > right->_f;
    };
};
