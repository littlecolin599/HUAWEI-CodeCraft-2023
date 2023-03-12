//
// Created by Colin on 2023/3/10.
//

#include "solution.h"
#include <cmath>
#include <string>
#include <iostream>


unordered_map<int, Station *> station_map;
unordered_map<int, Robot *> robot_map;
vector<vector<int>> destination_table(TYPE_NUM);


priority_queue<StationRequest*> station_req_queue;


CurrentState currentState;
CurrentState::CurrentState() : fps(0), money(0),
                               robot_num(0),
                               station_num(0) {

}


// 读取完成之后，处理每一帧的数据
void Solution::deal_fps() {

    for (auto *station : station_list) {
        int type = station->type;
        if (station->product == 1 && !destination_table[type].empty()) {
            station_req_queue.push(new StationRequest(station->id, station->type));
        }
    }

    while (!station_req_queue.empty() && !robot_work_queue.empty()) {
        auto req = station_req_queue.top();
        station_req_queue.pop();
        sort(robot_work_queue.begin(), robot_work_queue.end(), [&req](const Robot* r1, const Robot* r2) {
            auto station = station_map[req->id];
            return calc_dis(station->coordinate, r1->coordinate) > calc_dis(station->coordinate, r2->coordinate);
        });
        auto robot = robot_work_queue.back();
        robot_work_queue.pop_back();
        robot->destination = req->id;
        robot->status = BUY;
    }
    // 处理机器人的运动状态
    deal_work();
}

void Solution::deal_work() {
    for (auto robot : robot_list) {
        if (robot->status == DEFAULT) {
            continue;
        }
        if (robot->destination == robot->station) {
            if (robot->status == BUY) {
                cout << "buy " << robot->id << endl;
                robot->status = SELL;
                int type = robot->belong;
                if (destination_table[type].empty()) {
                    std::cerr << "destination error " << endl;
                }
                robot->destination = destination_table[type].back();
                destination_table[type].pop_back();
            } else if (robot->status == SELL) {
                cout << "sell " << robot->id << endl;
                robot->reset();
                robot_work_queue.push_back(robot);
            }
        } else {
            do_action(robot);
        }
    }
}

void Solution::do_action(Robot* robot) {
    Station* station = station_map[robot->destination];

    double rad = atan2(station->coordinate.second - robot->coordinate.second,
                                station->coordinate.first - robot->coordinate.first);
    double delta_rad = rad - robot->direction;
    cout << "rotate " << robot->id << " " << delta_rad << endl;
    int lineSpeed = 3;
    cout << "forward " << robot->id << " " << lineSpeed << endl;
}


float Solution::calc_dis(PFF p1, PFF p2) {
    float delta_x = abs(p1.first - p2.first);
    float  delta_y = abs(p1.second - p2.second);
    return delta_x * delta_x + delta_y * delta_y;
}



