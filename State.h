#pragma once
#include <iostream>

struct StateOperation;

struct State {
    int _rings[30] {}; // 6 rings, 5 columns
    int _zero_i; // zero_position
    mutable State * _parent;
    StateOperation * _operation;
    int _h = 0;
    mutable int _g = 0;
    mutable int _f = 0;

    int _rotation_counts[6];

    State(int rings[6][5],
          State * parent, StateOperation * operation);

    State(const State &);

    bool check_solution();

    void update_heuristics(int g);

    int m_distance();

    bool can_move(int oper_i);

    void move_ring_left(int ring_ind);
    void move_ring_right(int ring_ind);

    void move_zero_up();

    void move_zero_down();
};

struct StateOperation {
    std::string _desc;
    int _id;
    std::function<void(State*)> _func;

    StateOperation (const std::string & desc, int id,
                    const std::function<void(State*)> & func) {
      _desc = desc;
      _id = id;
      _func = func;
    }

    void operator()(State * state) const {
      _func(state);
    }
};
