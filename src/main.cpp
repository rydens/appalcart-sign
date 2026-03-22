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
#include "icon.h"

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

    AppalcartModule routeMod = AppalcartModule(37);
    routeMod.execute();

    //load font
    const char *bdfFontFile = "fonts/HaxorMedium-10.bdf";

    rgb_matrix::Font mainFont;
    if (!mainFont.LoadFont(bdfFontFile)) {
        std::cout << "couldn't load font file\n";
        return -1;
    }

  
    //AppalcartModule * mods[] = { &routeMod };

    rgb_matrix::RGBMatrix * canvas = rgb_matrix::RGBMatrix::CreateFromFlags(&argc, &argv, &matrixOptions);
    if(canvas == NULL) return 1;

    // canvas so we can swap
    rgb_matrix::FrameCanvas * swapCanvas = canvas->CreateFrameCanvas();

    // signal handler to recieve signals to exit
    signal(SIGTERM, InterruptHandler);
    signal(SIGINT, InterruptHandler);

    // speed
    int speed = 10;
    int delayUsec = 1000000 / speed / mainFont.CharacterWidth('W');
    
    // x and y positions
    int pos1 = 10;
    int writeHeight = canvas->height()/3;
    int writeWidth = 32;

    Icon_t icon;
    generateIcon(&icon, "B");
    
    std::cout << "about to render\n";
    while(!interruptRecieved)   // stall till interrupt recieved
    {
        swapCanvas->Fill(0, 0, 0);
        //for(int i = 0; i < 1; i++) {
            //AppalcartModule * routeMod = mods[i];
            if(routeMod.render(swapCanvas, pos1 + (0 * 50), pos1 + (0 * 10), writeHeight, writeWidth)) {
                std::cout << "error render error";
                return -1;
            }

            drawIcon(&icon, swapCanvas, pos1, pos1);

        //}
        swapCanvas = canvas->SwapOnVSync(swapCanvas);
        usleep(delayUsec);
    }
    

    canvas->Clear();
    delete canvas;

    return 0;
}
