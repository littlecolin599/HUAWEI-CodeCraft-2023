//
// Created by Colin on 2023/3/10.
//

#ifndef HUAWEI_CODECRAFT_2023_SOLUTION_H
#define HUAWEI_CODECRAFT_2023_SOLUTION_H
#include <unordered_map>
#include <queue>
#include <list>
#include <algorithm>
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
class Station_Request {
public:
    int id;                                 // 请求工作台的id
    int type;                               // 请求资源的种类
    STATUS status;                             // 请求 买/卖 资源
    Station_Request(int id, int type, STATUS status);
    bool operator < (const Station_Request& s) const;
};

class Solution {
public:
    static void deal_fps();
    static float calc_dis(PFF p1, PFF p2);
    static void deal_work();
};

extern unordered_map<int, Station*> station_map;
extern unordered_map<int, Robot*> robot_map;
extern CurrentState currentState;
extern priority_queue<Station_Request*> request_ready_queue;
extern list<Station_Request*> request_block_queue;

#endif //HUAWEI_CODECRAFT_2023_SOLUTION_H
