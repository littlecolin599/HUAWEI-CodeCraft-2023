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
    static int fps;
    static ll money;
    static int robot_num;
    static int station_num;
};

class solution {

};

extern unordered_map<int, Station*> station_map;
extern unordered_map<int, Robot*> robot_map;

#endif //HUAWEI_CODECRAFT_2023_SOLUTION_H
