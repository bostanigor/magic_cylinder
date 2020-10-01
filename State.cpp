#pragma once
#include "State.h"

bool State::check_solution() {
  auto ind = 5;
  for (int i = 1; i < 6; i++)
    for (int j = 0; j < 5; j++)
      if (_rings[ind++] != i)
        return false;
  return true;
}

void State::update_heuristics(int g) {
  _g = g;
  _h = m_distance();
  _f = g + _h;
}

int State::m_distance() {
  auto ind = 0;
  auto result = 0;
  for (int i = 0; i < 6; i++)
    for (int j = 0; j < 5; j++) {
      auto val = _rings[ind++];
      if (val > 0)
        result += abs(val - i);
    }
  return result;
}

bool State::can_move(int oper_i) {
  if (_operation != nullptr && _operation->_id == -oper_i)
    return false;
  if (oper_i == 10 && (_zero_i < 5 || _rings[_zero_i - 5] == -1)) // MOVE UP
    return false;
  if (oper_i == -10 && _zero_i > 24) // MOVE DOWN
    return false;
//  if (_rotation_counts[abs(oper_i) - 1] > 1)
//    return false;
  return true;
}

void State::move_ring_left(int ring_ind) {
  auto ring_start = ring_ind * 5;
  auto ring_end = ring_start + 4;
  auto t = _rings[ring_start];
  for (int i = ring_start; i < ring_end; i++)
    _rings[i] = _rings[i + 1];
  _rings[ring_end] = t;
  if (_zero_i > ring_start && _zero_i < ring_end)
    _zero_i = _zero_i % 5 == 0 ? _zero_i + 4 : _zero_i - 1;
  _rotation_counts[ring_ind]++;
}

void State::move_ring_right(int ring_ind) {
  auto ring_start = ring_ind * 5;
  auto ring_end = ring_start + 4;
  auto t = _rings[ring_end];
  for (int i = ring_end; i > ring_start; i--)
    _rings[i] = _rings[i - 1];
  _rings[ring_start] = t;
  if (_zero_i > ring_start && _zero_i < ring_end)
    _zero_i = _zero_i % 5 == 4 ? _zero_i - 4 : _zero_i + 1;
  _rotation_counts[ring_ind]++;
}

void State::move_zero_up() {
  auto ring1_i = _zero_i / 5;
  auto ring2_i = ring1_i - 1;
  std::swap(_rings[_zero_i],_rings[_zero_i - 5]);
  _zero_i -= 5;
  _rotation_counts[ring1_i] = 0;
  _rotation_counts[ring2_i] = 0;
}

void State::move_zero_down() {
  auto ring1_i = _zero_i / 5;
  auto ring2_i = ring1_i + 1;
  std::swap(_rings[_zero_i],_rings[_zero_i + 5]);
  _zero_i += 5;
  _rotation_counts[ring1_i] = 0;
  _rotation_counts[ring2_i] = 0;
}

State::State(int (*rings)[5], State *parent, StateOperation *operation) {
  for (int i = 0; i < 6; i++) {
    _rotation_counts[i] = 0;
    for (int j = 0; j < 5; j++) {
      _rings[i * 5 + j] = rings[i][j];
      if (rings[i][j] == 0)
        _zero_i = i * 5 + j;
    }
  }
  _parent = parent;
  _operation = operation;
}

State::State(const State &other) {
  for (int i = 0; i < 30; i++)
    _rings[i] = other._rings[i];
  for (int i = 0; i < 6; i++)
    _rotation_counts[i] = other._rotation_counts[i];
  _zero_i = other._zero_i;
  _parent = other._parent;
  _operation = other._operation;
  _h = other._h;
  _g = other._g;
  _f = other._f;
}
