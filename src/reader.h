//
// Created by Colin on 2023/3/10.
//

#ifndef HUAWEI_CODECRAFT_2023_READER_H
#define HUAWEI_CODECRAFT_2023_READER_H
#include <vector>
#include <string>
#include "solution.h"
using namespace std;

#define MAP_SIZE 100

class Reader {
public:
    enum CHECK_STATE {
        HEADER = 0,
        K,
        CHECK_STATION,
        CHECK_ROBOT
    };

public:
    static bool readMap();
    static bool readFps();

public:
    static vector<string> parse_line(char* text);
    static void parse_header(char* text);
    static void parse_k(char* text);
    static void parse_station(int id, char* text);
    static void parse_robot(int id, char* text);
};



#endif //HUAWEI_CODECRAFT_2023_READER_H
