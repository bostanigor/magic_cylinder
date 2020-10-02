#pragma once
#include <string>
#include <iostream>
#include "State.h"

bool check_resolution(State & start) {
  auto inv = 0;
  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 5; j++) {
      auto val1 = start._rings[i * 5 + j];
      if (val1 == -1) continue;
//      if (val1 == 0) inv += i;

      for (int i1 = 0; i1 <= i; i1++) {
        for (int j1 = 0; j1 < 5; j1++) {
          auto val2 = start._rings[j];
          if (val2 > val1)
            inv++;
        }
      }
    }
  }
  return inv % 2 == 0;
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
    size_t temp = state._rings[0] + 1;
    for (int i = 2; i < 30; i+=2) {
      temp = (temp << 2) | (state._rings[i] + 1);
    }

    return temp;
  };
};

struct MyPriorityFunc {
    size_t operator()(const State * left, const State * right) {
      return left->_f > right->_f;
    };
};
