//
// Created by Colin on 2023/3/10.
//

#ifndef HUAWEI_CODECRAFT_2023_STATION_H
#define HUAWEI_CODECRAFT_2023_STATION_H
#include <utility>
#include <vector>
using namespace std;
typedef pair<float, float> PFF;

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

extern vector<Station*> station_list;




#endif //HUAWEI_CODECRAFT_2023_STATION_H
