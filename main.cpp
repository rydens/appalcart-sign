/**
* This is our display code.
*
*  
*/


#include "led-matrix.h"
#include <unistd.h>
#include <math.h>
#include <stdio.h>
#include <signal.h>
#include <iostream>

using rgb_matrix::RGBMatrix;
using rgb_matrix::Canvas;

volatile bool interruptRecieved = false;
static void InterruptHandler(int signo) {
    interruptRecieved = true;
}

static void drawLine(Canvas * canvas, float incY) {
    //int centerX = canvas->width()
    //int centerY = canvas->height();

    //std::cout << centerX;

    for(int incX = 0; incX < canvas->width(); incX++) {
        canvas->SetPixel(incX, incY, 255, 0, 0);
        usleep(10000);

    }

}

int main(int argc, char *argv[]) {
    RGBMatrix::Options matrixOptions;
    matrixOptions.hardware_mapping = "regular";
    matrixOptions.rows = 32;
    matrixOptions.chain_length = 1;
    matrixOptions.parallel = 1;
    matrixOptions.show_refresh_rate = true;
    Canvas * canvas = RGBMatrix::CreateFromFlags(&argc, &argv, &matrixOptions);
    if(canvas == NULL) return 1;
    
    // signal handler to recieve signals to exit
    signal(SIGTERM, InterruptHandler);
    signal(SIGINT, InterruptHandler);

    for(int incY = 0; incY < canvas->height(); incY++) {
        drawLine(canvas, incY);
    }

    canvas->Clear();
    delete canvas;

    return 0;
}
