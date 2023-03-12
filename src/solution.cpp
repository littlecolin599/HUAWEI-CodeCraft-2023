//
// Created by Colin on 2023/3/10.
//

#include "solution.h"
#include <cmath>
#include <string>
#include <iostream>
#include <unistd.h>
#include <unordered_set>
#include <set>

unordered_set<int> request_id;
unordered_map<int, Station *> station_map;
unordered_map<int, Robot *> robot_map;
vector<vector<int>> destination_table(TYPE_NUM);
unordered_map<int, vector<int>> hasProduct_map;

CurrentState currentState;
CurrentState::CurrentState() : fps(0), money(0),
                               robot_num(0),
                               station_num(0) {

}


// 读取完成之后，处理每一帧的数据
void Solution::deal_fps() {

    for (auto material_station : material_station_list) {
        if (material_station->remain_time == 1) {
            material_station->hasProduct_to_sell = true;
            hasProduct_map[material_station->type].push_back(material_station->id);
            set<int> s(hasProduct_map[material_station->type].begin(), hasProduct_map[material_station->type].end());
            hasProduct_map[material_station->type].assign(s.begin(), s.end());
            //std::cerr << "hasProduct size " << hasProduct_map[material_station->type].size() << endl;
        }
    }

    for (auto product_station : product_station_list) {

        // 原料齐了并且没有在生产了
        if (product_station->curMaterial == stationInfo[product_station->type]->whichMaterial &&
            product_station->remain_time < 0) {
            product_station->curMaterial = 0;
        }

        if (product_station->remain_time == 1) {
            product_station->hasProduct_to_sell = true;
            hasProduct_map[product_station->type].push_back(product_station->id);
            set<int> s(hasProduct_map[product_station->type].begin(), hasProduct_map[product_station->type].end());
            hasProduct_map[product_station->type].assign(s.begin(), s.end());
            if (material_where_is_need[product_station->type].empty()) continue;  // 生产好了，但是不需要它
            for (auto robot : robot_list) {
                if (robot->status == DEFAULT) {
                    int sell_station_type = material_where_to_sell[product_station->type][0];
                    robot->destination = type_to_id[sell_station_type].back();
                    robot->status = READY_TO_SELL;
                    break;
                }
            }
        }
    }


    sort(product_station_list.begin(), product_station_list.end(), [](Station* a, Station* b) {
        if (a->type != b->type) return a->type < b->type;
        else {
            if (a->lack_num_of_material == 0 && b->lack_num_of_material != 0) return true;
            else if (a->lack_num_of_material != 0 && b->lack_num_of_material == 0) return false;
            else return a->lack_num_of_material > b->lack_num_of_material;
        }
    });

    for (auto it = product_station_list.rbegin(); it != product_station_list.rend(); ++it) {
        auto cur_station = *it;
        if (cur_station->lack_num_of_material == 0) continue;
        int lack_material = stationInfo[cur_station->type]->whichMaterial - cur_station->curMaterial;
        for (int i = TYPE_NUM; i > 1; --i) {
            if (lack_material >> i & 1) {
                int cur_lack_material_type = i;
                for (auto robot : robot_list) {
                    if (robot->status == DEFAULT) {
                        //std::cerr << "there are default robot " << '\n';
                        int buy_station_type = cur_lack_material_type;
                        sort(hasProduct_map[buy_station_type].begin(),
                             hasProduct_map[buy_station_type].end(), [&cur_station](int a, int b) {
                           return calc_dis(cur_station->coordinate, station_map[a]->coordinate) >
                                    calc_dis(cur_station->coordinate, station_map[b]->coordinate);
                        });
//                        std::cerr << "buy_station_type " << buy_station_type << " map " <<  hasProduct_map.size() << endl;
                        if (hasProduct_map[buy_station_type].empty()) continue;
                        int buy_station_id = hasProduct_map[buy_station_type].back();
                        robot->destination = buy_station_id;
                        std::cerr << "-------------" << '\n' <<
                                  "station " << cur_station->id << " type " << cur_station->type << '\n' <<
                                  "this station lack material " << cur_lack_material_type << '\n' <<
                                  "this station is getting a robot " << robot->id << '\n';
                        std::cerr << "robot's destination is " << robot->destination << endl;
                        std::cerr << "robot is going to buy " << station_map[robot->destination]->type << '\n';
                        std::cerr << " --------------------------------------------------------------" << '\n';

                        robot->ret_destination = cur_station->id;
                        robot->status = READY_TO_BUY;
                        cur_station->curMaterial |= (1 << station_map[buy_station_id]->type);
                        break;
                    }
                }
            }
        }
    }

    deal_work();
}

void Solution::deal_work() {
    for (auto robot : robot_list) {
        if (robot->status == DEFAULT) continue;
        if (robot->destination == robot->station) {
            if (robot->status == READY_TO_BUY) {
                if (station_map[robot->destination]->product == 1) {
                    robot->status = BUY;
                    cout << "buy " << robot->id << endl;
                    robot->destination = robot->ret_destination;
                    robot->status = READY_TO_SELL;
//                    std::cerr << "buy " << robot->id << endl;
//                    std::cerr << "----root_state------" << '\n' <<
//                              "robot id: " << robot->id << '\n' <<
//                              "robot state: " << robot->status << '\n' <<
//                              "robot destination: " << robot->destination << '\n' <<
//                              "robot belong: " << robot->belong << '\n' <<
//                              "-------------------------------------------" << '\n';
                }
            } else if (robot->status == READY_TO_SELL) {
                if ((station_map[robot->destination]->material >> robot->belong & 1) == 0 || true) {
                    robot->status = SELL;
                    //station_map[robot->destination]->curMaterial |= (1 << robot->belong);
                    cout << "sell " << robot->id << endl;
//                    std::cerr << "sell " << robot->id << " type " << robot->belong << endl;
//                    std::cerr << "----root_state------" << '\n' <<
//                              "robot id: " << robot->id << '\n' <<
//                              "robot state: " << robot->status << '\n' <<
//                              "robot destination: " << robot->destination << '\n' <<
//                              "robot belong: " << robot->belong << '\n' <<
//                              "-------------------------------------------" << '\n';
                    robot->destination = 0;
                    robot->status = DEFAULT;
                }
            }
        }
        if (robot->status == READY_TO_BUY || robot->status == READY_TO_SELL) do_action(robot);
    }
}

void Solution::do_action(Robot* robot) {
    Station* station = station_map[robot->destination];

    double rad = atan2(station->coordinate.second - robot->coordinate.second,
                                station->coordinate.first - robot->coordinate.first);

    double delta_rad = rad - robot->direction;
    if (delta_rad < 0) delta_rad =  3.1415926 - delta_rad;

    int lineSpeed = 4;

    if (calc_dis(station_map[robot->destination]->coordinate, robot->coordinate) < 3) {
        lineSpeed = 1;
    }
    if (delta_rad < -3.1415926) delta_rad = -3.1415926;
    if (delta_rad > 3.1415026) delta_rad = 3.1415926;
    cout << "rotate " << robot->id << " " << delta_rad << endl;
    cout << "forward " << robot->id << " " << lineSpeed << endl;
}


float Solution::calc_dis(PFF p1, PFF p2) {
    float delta_x = abs(p1.first - p2.first);
    float  delta_y = abs(p1.second - p2.second);
    return delta_x * delta_x + delta_y * delta_y;
}



