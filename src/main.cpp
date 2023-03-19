#include <iostream>
#include <unistd.h>
#include "reader.h"
#include "solution.h"

using namespace std;


int main() {
    Reader::readMap();
    puts("OK");
    fflush(stdout);

    while (scanf("%d", &frameID) != EOF) {
        currentState.fps = frameID;
        printf("%d\n", frameID);
//        if (frameID == 2) {
//            sleep(100);
//        }
        Reader::readFps();
        Solution::deal_fps();
/*      printf("%d\n", frameID);
        int lineSpeed = 3;
        double angleSpeed = 1.5;
        for(int robotId = 0; robotId < 4; robotId++){
            printf("forward %d %d\n", robotId, lineSpeed);
            printf("rotate %d %f\n", robotId, angleSpeed);
        }
        */

        printf("OK\n");
        fflush(stdout);
    }
    return 0;
}
