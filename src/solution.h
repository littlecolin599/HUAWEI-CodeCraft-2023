//
// Created by Colin on 2023/3/10.
//

#ifndef HUAWEI_CODECRAFT_2023_SOLUTION_H
#define HUAWEI_CODECRAFT_2023_SOLUTION_H
#include <unordered_map>
#include <queue>
#include <list>
#include <algorithm>
#include <bitset>
#include "station.h"
#include "robot.h"

const int K = 50;
const int TYPE_NUM = 9;
typedef long long ll;


class CurrentState {
public:
    int fps;
    ll money;
    int robot_num;
    int station_num;

    CurrentState();
};

class Solution {
public:
    static void deal_fps();
    static float calc_dis(PFF p1, PFF p2);
    static void deal_work();
    static void do_action(Robot*);
};

extern unordered_map<int, Station*> station_map;
extern unordered_map<int, Robot*> robot_map;
extern CurrentState currentState;
extern vector<vector<int>> destination_table;

#endif //HUAWEI_CODECRAFT_2023_SOLUTION_H
