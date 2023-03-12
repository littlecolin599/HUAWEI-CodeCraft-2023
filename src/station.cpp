//
// Created by Colin on 2023/3/10.
//

#include "station.h"

const int stationTypeCnt = 9;

vector<Station *> station_list;
unordered_map<int, StationInfo *> stationInfo;

Station::Station(int id, int type, const PFF &coordinate, int remainTime, int material, int product) :
        id(id), type(type), coordinate(coordinate), remain_time(remainTime), material(material), product(product) {
    if (stationInfo.count(type) == 0) {
        stationInfo[type] = new StationInfo(type);
    }
}

Station::Station(int id, int type, const PFF &coordinate) :
        id(id), type(type), coordinate(coordinate),
        remain_time(-1), material(0), product(0) {
    if (stationInfo.count(type) == 0) {
        stationInfo[type] = new StationInfo(type);
    }
}

StationInfo::StationInfo(int type): type(type) {
    switch (type) {
        case 1:
            workCycle = 50;
            whichProduct = 1;
            whichMaterial = 0;
            break;
        case 2:
            workCycle = 50;
            whichProduct = 2;
            whichMaterial = 0;
            break;
        case 3:
            workCycle = 50;
            whichProduct = 3;
            whichMaterial = 0;
            break;
        case 4:
            whichMaterial = 6;  // 110
            workCycle = 500;
            whichProduct = 4;
            break;
        case 5:
            whichMaterial = 10;  // 1010
            workCycle = 500;
            whichProduct = 5;
            break;
        case 6:
            whichMaterial = 12; // 1100
            workCycle = 500;
            whichProduct = 6;
            break;
        case 7:
            whichMaterial = 112; // 1110000
            workCycle = 1000;
            whichProduct = 7;
            break;
        case 8:
            whichMaterial = 128;  // 10000000
            workCycle = 1;
            whichProduct = -1;
            break;
        case 9:
            whichMaterial = 254; // 11111110
            workCycle = 1;
            whichProduct = -1;
            break;
        default:
            break;
    }
}


StationRequest::StationRequest(int id, int type) : id(id), type(type) {}

bool StationRequest::operator<(const StationRequest &rhs) const {
    if (this->type == rhs.type) return this->id < rhs.id;
    return this->type > rhs.type;
}
