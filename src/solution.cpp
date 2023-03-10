//
// Created by Colin on 2023/3/10.
//

#include "solution.h"


unordered_map<int, Station *> station_map;
unordered_map<int, Robot *> robot_map;
CurrentState currentState;
CurrentState::CurrentState() : fps(0), money(0),
                               robot_num(0),
                               station_num(0) {}
