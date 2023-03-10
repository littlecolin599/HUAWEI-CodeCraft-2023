//
// Created by Colin on 2023/3/10.
//

#include "station.h"

vector<Station *> station_list;

Station::Station(int id, int type, const PFF &coordinate, int remainTime, int material, int product) :
        id(id), type(type), coordinate(coordinate), remain_time(remainTime), material(material), product(product) {}

Station::Station(int id, int type, const PFF &coordinate) :
        id(id), type(type), coordinate(coordinate), remain_time(-1), material(0), product(0) {}
