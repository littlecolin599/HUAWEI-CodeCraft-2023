//
// Created by Colin on 2023/3/10.
//

#include "station.h"

const int stationTypeCnt = 9;

vector<Station *> station_list;
unordered_map<int, StationInfo> stationInfo;

Station::Station(int id, int type,
                 const PFF &coordinate,
                 int remainTime,
                 int material,
                 int product) :
            id(id), type(type),
            coordinate(coordinate),
            remain_time(remainTime),
            material(material),
            product(product) {
    if (stationInfo.count(type) == 0) {
        stationInfo[type] = *new StationInfo(type);
    }
}

Station::Station(int id, int type, const PFF &coordinate) :
        id(id), type(type), coordinate(coordinate),
        remain_time(-1), material(0), product(0) {
    if (stationInfo.count(type) == 0) {
        stationInfo[type] = *new StationInfo(type);
    }
}
