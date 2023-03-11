//
// Created by Colin on 2023/3/10.
//

#ifndef HUAWEI_CODECRAFT_2023_ROBOT_H
#define HUAWEI_CODECRAFT_2023_ROBOT_H
#include "solution.h"
#include <utility>
#include <vector>
#include "station.h"
using namespace std;
typedef pair<float, float> PFF;



class Robot {
public:
    int id;             // 机器人ID
    int station;        // 所处的工作站台
    int belong;         // 携带的物品
    float time_val;     // 时间价值系数
    float crush_val;    // 碰撞价值系数
    float omega;        // 角速度
    PFF velocity;       // 线速度
    float direction;    // 朝向
    PFF coordinate;     // 坐标
    int destination;    // 目标工作台，默认0 表示没有目标，为空闲机器人
    STATUS status;

public:
    Robot(int id, int station, int belong, float timeVal, float crushVal, float omega, const PFF &velocity, float direction,
          const PFF &coordinate);
    Robot(int id, const PFF &coordinate);

    void reset();
    void do_action();

};

extern vector<Robot*> robot_list;
extern vector<Robot *> robot_work_queue;


#endif //HUAWEI_CODECRAFT_2023_ROBOT_H
