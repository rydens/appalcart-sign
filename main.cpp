/**
* This is our display code.
*
*  
*/

#include "led-matrix.h"
#include "graphics.h"
#include "render.h"
#include "module.h"
#include "routeETA.h"


#include <unistd.h>
#include <math.h>
#include <stdio.h>
#include <signal.h>
#include <iostream>

#include <getopt.h>
#include <string.h>
#include <format>

using rgb_matrix::RGBMatrix;
using rgb_matrix::Canvas;
using namespace rgb_matrix;

volatile bool interruptRecieved = false; // for interupt handler
static void InterruptHandler(int signo) {
    interruptRecieved = true;
}

int main(int argc, char *argv[]) {
    RGBMatrix::Options matrixOptions;
    matrixOptions.hardware_mapping = "regular";
    matrixOptions.cols = 128;
    matrixOptions.rows = 32;
    matrixOptions.chain_length = 1;
    matrixOptions.parallel = 1;
    matrixOptions.show_refresh_rate = true;

    // till we get up to date info make own struct and push into vector
    RouteETA redRoute;
    redRoute.busID = 2;
    redRoute.ETA = 12;
    redRoute.routeColor = "Red";
    redRoute.equipmentId = "B12";
    redRoute.routeName = "Red Route";

    // push into routeETAS
    std::vector<RouteETA> v;
    v.push_back(redRoute);

    RouteModule routeMod = RouteModule(3, v);

    Canvas * canvas = RGBMatrix::CreateFromFlags(&argc, &argv, &matrixOptions);
    if(canvas == NULL) return 1;

    // int space = mainFont.baseline();
    int pos1 = 10;
    int writeHeight = canvas->height()/3;
    int writeWidth = 32;

    if(routeMod.render(canvas, 0, pos1, writeHeight, writeWidth)) {
        std::cout << "error render error";
        return -1;
    }

    // signal handler to recieve signals to exit
    signal(SIGTERM, InterruptHandler);
    signal(SIGINT, InterruptHandler);

    // stall till interrupt recieved
    while(!interruptRecieved);

    canvas->Clear();
    delete canvas;

    return 0;
}
