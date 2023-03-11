//
// Created by Colin on 2023/3/10.
//

#include "robot.h"

vector<Robot *> robot_list;
vector<Robot *> robot_work_queue;

Robot::Robot(int id, int station, int belong, float timeVal, float crushVal, float omega, const PFF &velocity, float direction,
             const PFF &coordinate) : id(id), station(station), belong(belong), time_val(timeVal), crush_val(crushVal),
                                      omega(omega), velocity(velocity), direction(direction), coordinate(coordinate),
                                      destination(0), status(DEFAULT){}

Robot::Robot(int id, const PFF &coordinate) : id(id), station(-1), belong(0), time_val(0), crush_val(0), omega(0), velocity({0, 0}),
                                      direction(0), coordinate(coordinate), destination(0), status(DEFAULT){}

void Robot::reset() {
    this->destination = 0;
    this->status = DEFAULT;
}

void Robot::do_action() {

}
