//
// Created by Colin on 2023/3/10.
//

#include "station.h"

const int stationTypeCnt = 9;

unordered_set<int> material_type_range({1, 2, 3});
unordered_set<int> product_type_range({4, 5, 6, 7});
unordered_set<int> consume_type_range({8, 9});

vector<Station *> station_list;
vector<Station *> material_station_list;
vector<Station *> product_station_list;
vector<Station *> consume_station_list;
unordered_map<int, vector<int>> material_where_to_sell;
unordered_map<int, vector<int>> type_to_id;
unordered_map<int, StationInfo *> stationInfo;
unordered_map<int, vector<int>> material_where_is_need;

Station::Station(int id, int type, const PFF &coordinate, int remainTime, int material, int product) :
        id(id), type(type), coordinate(coordinate), remain_time(remainTime), material(material), product(product) {
    curMaterial = 0;
}

Station::Station(int id, int type, const PFF &coordinate) :
        id(id), type(type), coordinate(coordinate),
        remain_time(-1), material(0), product(0) {
    curMaterial = 0;
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
            material_where_to_sell[1].push_back(4);
            material_where_to_sell[2].push_back(4);
            break;
        case 5:
            whichMaterial = 10;  // 1010
            workCycle = 500;
            whichProduct = 5;
            material_where_to_sell[1].push_back(5);
            material_where_to_sell[3].push_back(5);
            break;
        case 6:
            whichMaterial = 12; // 1100
            workCycle = 500;
            whichProduct = 6;
            material_where_to_sell[2].push_back(6);
            material_where_to_sell[3].push_back(6);
            break;
        case 7:
            whichMaterial = 112; // 1110000
            workCycle = 1000;
            whichProduct = 7;
            material_where_to_sell[4].push_back(7);
            material_where_to_sell[5].push_back(7);
            material_where_to_sell[6].push_back(7);
            break;
        case 8:
            whichMaterial = 128;  // 10000000
            workCycle = 1;
            whichProduct = -1;
            material_where_to_sell[7].push_back(8);
            break;
        case 9:
            whichMaterial = 254; // 11111110
            workCycle = 1;
            whichProduct = -1;
            for (int i = 1; i < 9; i++) {
                if (whichMaterial >> i & 1) {
                    material_where_to_sell[i].push_back(9);
                }
            }
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
