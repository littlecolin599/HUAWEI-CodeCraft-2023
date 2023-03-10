//
// Created by Colin on 2023/3/10.
//

#ifndef HUAWEI_CODECRAFT_2023_STATION_H
#define HUAWEI_CODECRAFT_2023_STATION_H
#include <utility>
#include <vector>
#include <unordered_map>

using namespace std;
typedef pair<float, float> PFF;

class StationInfo {
public:
    StationInfo() {

    }

    StationInfo(int type) {
        switch(type) {
            case 1:
                workCycle = 50;
                whichProduct = 1;
                break;
            case 2:
                workCycle = 50;
                whichProduct = 2;
                break;
            case 3:
                workCycle = 50;
                whichProduct = 3;
                break;
            case 4:
                whichMaterial.push_back(1);
                whichMaterial.push_back(2);
                workCycle = 500;
                whichProduct = 4;
                break;
            case 5:
                whichMaterial.push_back(1);
                whichMaterial.push_back(3);
                workCycle = 500;
                whichProduct = 5;
                break;
            case 6:
                whichMaterial.push_back(2);
                whichMaterial.push_back(3);
                workCycle = 500;
                whichProduct = 6;
                break;
            case 7:
                whichMaterial.push_back(4);
                whichMaterial.push_back(5);
                whichMaterial.push_back(6);
                workCycle = 1000;
                whichProduct = 7;
                break;
            case 8:
                whichMaterial.push_back(7);
                workCycle = 1;
                whichProduct = -1;
                break;
            case 9:
                for (int i = 1; i <= 7; ++i) whichMaterial.push_back(i);
                workCycle = 1;
                whichProduct = -1;
                break;
            default:
                break;
        }
    }
public:
    vector<int> whichMaterial;
    int workCycle;
    int whichProduct;
};

class Station {
public:
    int id;             // 工作台ID
    int type;           // 类型
    PFF coordinate;     // 坐标
    int remain_time;    // 剩余生产时间
    int material;       // 材料格
    int product;        // 产品格
    Station(int id, int type, const PFF &coordinate, int remainTime, int material, int product);
    Station(int id, int type, const PFF &coordinate);

};

extern unordered_map<int, StationInfo> stationInfo;

extern vector<Station*> station_list;




#endif //HUAWEI_CODECRAFT_2023_STATION_H
