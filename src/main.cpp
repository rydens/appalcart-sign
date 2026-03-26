/**
* This is our display code.
*
*
*/

#include "led-matrix.h"
#include "graphics.h"
#include "render.h"
#include "AppalcartModule.h"
#include "WeatherModule.h"

#include <unistd.h>
#include <math.h>
#include <stdio.h>
#include <signal.h>
#include <iostream>
#include "icon.h"

#include <getopt.h>
#include <string.h>
#include <format>
#include <thread>
#include <chrono>

volatile bool interruptRecieved = false; // for interupt handler
static void InterruptHandler(int signo) {
    interruptRecieved = true;
}

uint8_t endModules = 0;
std::vector<Module*> mods;

void moduleExecuteTask() {	
    while(!endModules) {
    	for (Module* m : mods) {
       		m->execute();
    	}
    
    std::this_thread::sleep_for(std::chrono::seconds(5));
    }
}

int main(int argc, char *argv[]) {
    
	
    const char *bdfFontFile = "fonts/HaxorMedium-10.bdf";

    // load font
    
    rgb_matrix::RGBMatrix::Options matrixOptions;
    matrixOptions.hardware_mapping = "regular";
    matrixOptions.cols = 128;
    matrixOptions.rows = 32;
    matrixOptions.chain_length = 1;
    matrixOptions.parallel = 1;
    matrixOptions.show_refresh_rate = true;

    AppalcartModule routeMod1 = AppalcartModule(46, bdfFontFile);
    routeMod1.execute();
    AppalcartModule routeMod2 = AppalcartModule(37, bdfFontFile);
    routeMod2.execute();
    WeatherModule weatherMod = WeatherModule();
    weatherMod.execute();

    mods = {&routeMod1, &routeMod2, &weatherMod};

    // create module execute thread
    std::thread moduleExecutor(moduleExecuteTask);

    //load font

    rgb_matrix::Font mainFont;
    if (!mainFont.LoadFont(bdfFontFile)) {
        std::cout << "couldn't load font file\n";
        return -1;
    }

    rgb_matrix::RGBMatrix * canvas = rgb_matrix::RGBMatrix::CreateFromFlags(&argc, &argv, &matrixOptions);
    if(canvas == NULL) return 1;

    // canvas so we can swap
    rgb_matrix::FrameCanvas * swapCanvas = canvas->CreateFrameCanvas();

    // signal handler to recieve signals to exit
    signal(SIGTERM, InterruptHandler);
    signal(SIGINT, InterruptHandler);

    // speed
    int speed = 3;
    int delayUsec = 1000000 / speed / mainFont.CharacterWidth('W');
    
    // x and y positions
    int pos1 = 10;
    int writeHeight = canvas->height()/3;
    int writeWidth = 32;

       
    std::cout << "about to render\n";
    while(!interruptRecieved)   // stall till interrupt recieved
    {
        swapCanvas->Fill(0, 0, 0);
        for(int i = 0; i < 3; i++) {
            Module* mod = mods[i];
            if(mod->render(swapCanvas, 0, pos1 + (i * 10), writeHeight, writeWidth)) {
		canvas->Clear();
		delete canvas;
    		endModules = 1;
    		moduleExecutor.join();
                std::cout << "error render error";
                return -1;
            }


        }
        swapCanvas = canvas->SwapOnVSync(swapCanvas);
        usleep(delayUsec / 3);
    }
    

    canvas->Clear();
    delete canvas;

    endModules = 1;
    moduleExecutor.join();

    return 0;
}
