/**
* This is our display code.
*
*
*/

#include "led-matrix.h"
#include "graphics.h"
#include "render.h"
#include "AppalcartModule.h"

#include <unistd.h>
#include <math.h>
#include <stdio.h>
#include <signal.h>
#include <iostream>

#include <getopt.h>
#include <string.h>
#include <format>

volatile bool interruptRecieved = false; // for interupt handler
static void InterruptHandler(int signo) {
    interruptRecieved = true;
}

int main(int argc, char *argv[]) {
    rgb_matrix::RGBMatrix::Options matrixOptions;
    matrixOptions.hardware_mapping = "regular";
    matrixOptions.cols = 128;
    matrixOptions.rows = 32;
    matrixOptions.chain_length = 1;
    matrixOptions.parallel = 1;
    matrixOptions.show_refresh_rate = true;

    AppalcartModule routeMod = AppalcartModule(3);
    routeMod.execute();

    rgb_matrix::Canvas * canvas = rgb_matrix::RGBMatrix::CreateFromFlags(&argc, &argv, &matrixOptions);
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
