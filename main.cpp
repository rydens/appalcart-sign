/**
* This is our display code.
*
*  
*/

#include "led-matrix.h"
#include "graphics.h"
#include "matrix.h"

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
    Canvas * canvas = RGBMatrix::CreateFromFlags(&argc, &argv, &matrixOptions);

    Color fontColor = Color(255, 255, 0);
    const char *bdfFontFile = "fonts/HaxorMedium-10.bdf";
    if(canvas == NULL) return 1;

    RouteETA redRoute;
    redRoute.busID = 2;
    redRoute.ETA = 12;
    redRoute.routeColor = "Red";
    redRoute.equipmentId = "B12";
    redRoute.routeName = "Red Route";
    
    // load font
    Font mainFont;
    if (!mainFont.LoadFont(bdfFontFile)) {
        std::cout << "couldn't load font file\n";
        return -1;
    }

    int space = mainFont.baseline();
    int pos1 = 10;
    int pos2 = pos1+space;
    int pos3 = pos2+space;
    busDisplayText(canvas, &mainFont, 0, pos1, fontColor, &redRoute);
    busDisplayText(canvas, &mainFont, 0, pos2, fontColor, &redRoute);
    busDisplayText(canvas, &mainFont, 0, pos3, fontColor, &redRoute);



    // signal handler to recieve signals to exit
    signal(SIGTERM, InterruptHandler);
    signal(SIGINT, InterruptHandler);

  

    // stall till interrupt recieved
    while(!interruptRecieved);

    canvas->Clear();
    delete canvas;

    return 0;
}
