//
// Created by Colin on 2023/3/10.
//

#include "reader.h"
#include "robot.h"
#include "station.h"
#include <iostream>
#include <cstring>
#include <cassert>
#include "solution.h"

using namespace std;

bool Reader::readFps() {
    char line[1024];
    CHECK_STATE check_state = HEADER;
    int robot_id = 0;
    int station_id = 0;
    for (int i = 0; i < TYPE_NUM; ++i) {
        destination_table[i].clear();
        material_where_is_need[i].clear();
    }
    while (fgets(line, sizeof line, stdin)) {
        if (line[0] == 'O' && line[1] == 'K') {
            return true;
        }
        switch (check_state) {
            case HEADER:
                parse_header(line);
                check_state = K;
                break;
            case K:
                parse_k(line);
                check_state = CHECK_STATION;
                break;
            case CHECK_STATION:
                parse_station(station_id++, line);
                if (station_id == currentState.station_num) {
                    check_state = CHECK_ROBOT;
                }
                break;
            case CHECK_ROBOT:
                parse_robot(robot_id++, line);
                break;
        }
        memset(line, '\000', sizeof line);
    }
    return false;
}

bool Reader::readMap() {
    char line[1024];
    int height = 99;
    int station_id = 0;
    int robot_id = 0;
    while (fgets(line, sizeof line, stdin)) {
        if (line[0] == 'O' && line[1] == 'K') {
            currentState.station_num = station_list.size();
            currentState.robot_num = robot_list.size();
            return true;
        }
        for (int i = 0; i < MAP_SIZE; i++) {
            if (line[i] == '.') continue;
            float y = 0.5 * height + 0.25;
            float x = 0.25 * i + 0.25;
            if (line[i] >= '1' && line[i] <= '9') {
                auto* s = new Station(station_id, line[i] - '0', {x, y});
                station_map[station_id] = s;
                station_list.push_back(s);
                auto type = line[i] - '0';
                if (material_type_range.count(type)) {
                    material_station_list.push_back(s);
                } else if (product_type_range.count(type)){
                    product_station_list.push_back(s);
                } else if (consume_type_range.count(type)) {
                    consume_station_list.push_back(s);
                }
                if (stationInfo.count(type) == 0) {
                    stationInfo[type] = new StationInfo(type);
                }
                type_to_id[type].push_back(station_id++);  // 前面++导致多了一个1
                // 初始条件下，所有机器均有购买资源需求
            } else if (line[i] == 'A') {
                auto* r = new Robot(robot_id, {x, y});
                robot_map[robot_id++] = r;
                robot_list.push_back(r);
                robot_work_queue.push_back(r);      // 初始条件下，所有机器人都是空闲的
            }
        }
        sort(material_station_list.begin(), material_station_list.end(), [](Station* a, Station* b) {
            return a->type > b->type;
        });
        height--;
    }
    return false;
}

void Reader::parse_header(char *text) {
    vector<string> item = parse_line(text);
    assert(item.size() == 1);
    currentState.money = stoll(item[0]);
}

void Reader::parse_k(char *text) {
    vector<string> item = parse_line(text);
    assert(item.size() == 1 && currentState.station_num == stoi(item[0]));
}

int count_1(int num)
{
    int count = 0;
    while(num)
    {
        count += num&1;
        num >>= 1;
    }
    return count;
}


void Reader::parse_station(int id, char *text) {
    vector<string> item = parse_line(text);
    assert(item.size() == 6);
    Station* station = station_map[id];
    station->coordinate = {stof(item[1]), stof(item[2])};
    station->remain_time = stoi(item[3]);
    station->material = stoi(item[4]);
    station->product = stoi(item[5]);
    int type = station->type;
    int lack_material = stationInfo[type]->whichMaterial - station->curMaterial;
    station->lack_num_of_material = count_1(lack_material);
    for (int i = 1; i < TYPE_NUM; ++i) {
        if (lack_material >> i & 1) {
            material_where_is_need[i].push_back(station->id);
        }
    }
}

void Reader::parse_robot(int id, char *text) {
    vector<string> item = parse_line(text);
    assert(item.size() == 10);
    Robot* robot = robot_map[id];
    robot->station = stoi(item[0]);
    robot->belong = stoi(item[1]);
    robot->time_val = stof(item[2]);
    robot->crush_val = stof(item[3]);
    robot->omega = stof(item[4]);
    robot->velocity = {stof(item[5]), stof(item[6])};
    robot->direction = stof(item[7]);
    robot->coordinate = {stof(item[8]), stof(item[9])};
}

vector<string> Reader::parse_line(char* text) {
    vector<string> item;
    char* s = new char[1024];
    strcpy(s, text);
    char* p = strtok(s, " ");
    while (p) {
        item.emplace_back(p);
        p = strtok(nullptr, " ");
    }
    return item;
}


