//
// Created by Colin on 2023/3/10.
//

#include "solution.h"


unordered_map<int, Station *> station_map;
unordered_map<int, Robot *> robot_map;
// 有请求到来时，先放入阻塞队列中，等待条件满足，再放入就绪队列
priority_queue<Station_Request*> request_ready_queue;
list<Station_Request*> request_block_queue;

CurrentState currentState;
CurrentState::CurrentState() : fps(0), money(0),
                               robot_num(0),
                               station_num(0) {}

Station_Request::Station_Request(int id, int type) : id(id), type(type) {}

bool Station_Request::operator<(const Station_Request &s) const {
    if (stationInfo[this->type] < stationInfo[s.type]) return true;
    return false;
}

// 读取完成之后，处理每一帧的数据
void Solution::deal_fps() {
    // 检查阻塞队列中的请求是否可以加入就绪队列中
    for (auto req : request_block_queue) {
        int type = req->type;       // 正在请求的资源类型
        int material = stationInfo[type]->whichMaterial;    // 资源所需要的材料
        // 如果这个资源不需要其他的材料，直接将该请求从阻塞队列迁移到就绪队列
        if (material == 0) {
            request_block_queue.remove(req);
            request_ready_queue.push(req);
            continue;
        }
        int station_id = req->id;   // 获取工作台ID
        Station* station = station_map[station_id]; //获取对应的工作台

        // TODO：如果正在生产，暂时先留在阻塞队列中，后续待改进
        if (station->remain_time != -1) continue;
        // 检查工作台所需的原材料是否就绪
        if (material == station->material) {
            request_block_queue.remove(req);
            request_ready_queue.push(req);
        }
    }
    // 有空闲机器人且有就绪请求
    // TODO: 记得每一帧读取完之后看机器人是否空闲，空闲需要将其添加进工作队列
    while (!request_ready_queue.empty() && !robot_work_queue.empty()) {
        auto req = request_ready_queue.top();
        int station_id = req->id;
        Station* station = station_map[station_id];
        request_ready_queue.pop();
        // 根据一定的规则，选择出最佳的机器人来处理这个请求  TODO:暂时按照距离最近优先
        sort(robot_work_queue.begin(), robot_work_queue.end(), [&station](const Robot* r1, const Robot* r2){
            float dis1 = calc_dis(station->coordinate, r1->coordinate);
            float dis2 = calc_dis(station->coordinate, r2->coordinate);
            return dis1 < dis2;
        });


    }
}

float Solution::calc_dis(PFF p1, PFF p2) {
    float delta_x = abs(p1.first - p2.first);
    float  delta_y = abs(p1.second - p2.second);
    return delta_x * delta_x + delta_y * delta_y;
}
