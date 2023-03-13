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

    for (auto consume_station : consume_station_list) {

    }

    for (auto product_station : product_station_list) {

        // 原料齐了并且没有在生产了
        if (product_station->curMaterial == stationInfo[product_station->type]->whichMaterial &&
            product_station->remain_time == -1) {
            product_station->curMaterial = 0;
        }

        if (product_station->remain_time == 0 && product_station->product == 1) {


            product_station->hasProduct_to_sell = true;
            hasProduct_map[product_station->type].push_back(product_station->id);
            set<int> s(hasProduct_map[product_station->type].begin(), hasProduct_map[product_station->type].end());
            hasProduct_map[product_station->type].assign(s.begin(), s.end());
            if (material_where_is_need[product_station->type].empty()) continue;  // 生产好了，但是不需要它
            for (auto robot : robot_list) {
                if (robot->status == DEFAULT) {
                    std::cerr << "I want to sell my product" << '\n';
                    int sell_station_type = material_where_to_sell[product_station->type][0];
                    robot->ret_destination = type_to_id[sell_station_type].back();
                    if (type_to_id[sell_station_type].empty()) continue;
                    type_to_id[sell_station_type].pop_back();
//                    if ((station_map[robot->ret_destination]->curMaterial >> product_station->type) & 1) {
//                        if (type_to_id[sell_station_type].empty()) continue;
//                        robot->ret_destination = type_to_id[sell_station_type].back();
//                        type_to_id[sell_station_type].pop_back();
//                    }
                    robot->status = READY_TO_BUY;
                    station_map[robot->ret_destination]->curMaterial |= (1 << product_station->type);
                    robot->destination = product_station->id;
                    std::cerr << "-------------" << '\n' <<
                              "station " << product_station->id << " type " << product_station->type << '\n' <<
                              "this station's product " << product_station->type << '\n' <<
                              "this station is getting a robot " << robot->id << '\n';
                    std::cerr << "robot's destination is " << robot->destination << endl;
                    std::cerr << "robot is going to buy " << station_map[robot->destination]->type << '\n';
                    std::cerr << "after buy product, robot's going to " << robot->ret_destination << '\n';
                    std::cerr << "the ret_destination type is " << station_map[robot->ret_destination]->type << '\n';
                    std::cerr << "sell_station_type is " << sell_station_type << '\n';
                    std::cerr << " --------------------------------------------------------------" << '\n';
                    break;
                }
            }
        }
    }


    sort(product_station_list.begin(), product_station_list.end(), [](Station* a, Station* b) {
        if (a->lack_num_of_material == 0 && b->lack_num_of_material != 0) return true;
        else if (a->lack_num_of_material != 0 && b->lack_num_of_material == 0) return false;
        else return a->lack_num_of_material > b->lack_num_of_material;

    });

    for (auto it = product_station_list.rbegin(); it != product_station_list.rend(); ++it) {
        auto cur_station = *it;
        //std::cerr << "type " << cur_station->type << " is needed by " << material_where_is_need[cur_station->type].size() << '\n';
        if (material_where_is_need[cur_station->type].empty()) {
            std::cerr << "the product " << cur_station->type << " is no need " << endl;
            continue;
        }
        if (cur_station->lack_num_of_material == 0 && cur_station->remain_time == 0) {
            std::cerr << "the cur_station " << cur_station->type << " is not lack of material" << endl;
            continue;
        }
        int lack_material = stationInfo[cur_station->type]->whichMaterial - cur_station->curMaterial;
        for (int i = 1; i <TYPE_NUM; ++i) {
            if (lack_material >> i & 1) {
                int cur_lack_material_type = i;
                if (hasProduct_map[cur_lack_material_type].empty()) {
                    //std::cerr << "cur lack_material " << cur_lack_material_type << "is lack" << endl;
                    continue;  // 缺货了
                }
                for (auto robot : robot_list) {
                    if (robot->status == DEFAULT) {
                        //std::cerr << "there are default robot " << '\n';
                        int buy_station_type = cur_lack_material_type;
                        sort(hasProduct_map[buy_station_type].begin(),
                             hasProduct_map[buy_station_type].end(), [&robot](int a, int b) {
                           return calc_dis(robot->coordinate, station_map[a]->coordinate) >
                                    calc_dis(robot->coordinate, station_map[b]->coordinate);
                        });
//                        std::cerr << "buy_station_type " << buy_station_type << " map " <<  hasProduct_map.size() << endl;
                        if (hasProduct_map[buy_station_type].empty()) continue;
                        int buy_station_id = hasProduct_map[buy_station_type].back();
                        robot->destination = buy_station_id;
                        std::cerr << "-------------" << '\n' <<
                                  "station " << cur_station->id << " type " << cur_station->type << '\n' <<
                                  "I want to product type " << cur_station->type << '\n' <<
                                  "this type need size " << material_where_is_need[cur_station->type].size() << '\n' <<
                                  "this station lack material " << cur_lack_material_type << '\n' <<
                                  "this station is getting a robot " << robot->id << '\n';
                        std::cerr << "robot's destination is " << robot->destination << endl;
                        std::cerr << "robot is going to buy " << station_map[robot->destination]->type << '\n';
                        std::cerr << " --------------------------------------------------------------" << '\n';

                        robot->ret_destination = cur_station->id;
                        robot->status = READY_TO_BUY;
                        hasProduct_map[cur_lack_material_type].pop_back();
                        cur_station->curMaterial |= (1 << station_map[buy_station_id]->type);
                        lack_material = stationInfo[cur_station->type]->whichMaterial - cur_station->curMaterial;
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
    if (delta_rad < -1) delta_rad =  3.1415926 - delta_rad;

    int lineSpeed = 4;

    if (calc_dis(station_map[robot->destination]->coordinate, robot->coordinate) < 3) {
        lineSpeed = 1;
    }
    if (delta_rad < -3.1415926) delta_rad = -3.1415926;
    if (delta_rad > 3.1415026) delta_rad = 3.1415926;
    cout << "rotate " << robot->id << " " << delta_rad * 1.2 << endl;
    cout << "forward " << robot->id << " " << lineSpeed << endl;
}


float Solution::calc_dis(PFF p1, PFF p2) {
    float delta_x = abs(p1.first - p2.first);
    float  delta_y = abs(p1.second - p2.second);
    return delta_x * delta_x + delta_y * delta_y;
}



