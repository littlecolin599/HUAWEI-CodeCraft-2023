//
// Created by Colin on 2023/3/10.
//

#ifndef HUAWEI_CODECRAFT_2023_SOLUTION_H
#define HUAWEI_CODECRAFT_2023_SOLUTION_H
#include <unordered_map>
#include "station.h"
#include "robot.h"

typedef long long ll;


class CurrentState {
public:
    int fps;
    ll money;
    int robot_num;
    int station_num;

    CurrentState();
};

class solution {

};

extern unordered_map<int, Station*> station_map;
extern unordered_map<int, Robot*> robot_map;
extern CurrentState currentState;
#endif //HUAWEI_CODECRAFT_2023_SOLUTION_H
