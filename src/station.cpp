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
            whichMaterial = 3;  // 1 + 2
            workCycle = 500;
            whichProduct = 4;
            break;
        case 5:
            whichMaterial = 4;  // 1 + 3
            workCycle = 500;
            whichProduct = 5;
            break;
        case 6:
            whichMaterial = 5; // 2 + 3
            workCycle = 500;
            whichProduct = 6;
            break;
        case 7:
            whichMaterial = 14; // 4 + 5 + 6
            workCycle = 1000;
            whichProduct = 7;
            break;
        case 8:
            whichMaterial = 7;  // 7
            workCycle = 1;
            whichProduct = -1;
            break;
        case 9:
            whichMaterial = 28; // 1-7
            workCycle = 1;
            whichProduct = -1;
            break;
        default:
            break;
    }
}


