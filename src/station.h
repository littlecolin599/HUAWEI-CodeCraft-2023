//
// Created by Colin on 2023/3/10.
//

#ifndef HUAWEI_CODECRAFT_2023_STATION_H
#define HUAWEI_CODECRAFT_2023_STATION_H

#include <unordered_map>
#include <utility>
#include <vector>
#include <unordered_map>


using namespace std;
typedef pair<float, float> PFF;
typedef pair<int, int> PII;



class StationInfo {
public:
    StationInfo(int type);
public:
    int type;
    int whichMaterial;
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
    int curMaterial;
    int product;        // 产品格
    bool hasRequest;
    Station(int id, int type, const PFF &coordinate, int remainTime, int material, int product);
    Station(int id, int type, const PFF &coordinate);

};

class StationRequest {
public:
    int id;
    int type;
    PII src_dst;

    bool operator<(const StationRequest &rhs) const;

public:
    StationRequest(int id, int type);
};

extern unordered_map<int, StationInfo*> stationInfo;
extern vector<Station*> station_list;


#endif //HUAWEI_CODECRAFT_2023_STATION_H
