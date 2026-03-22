#ifndef MODULE_H
#define MODULE_H

#include <string>
#include <vector>
#include "routeETA.h"
#include "led-matrix.h"
#include <iostream>



using namespace std;
using rgb_matrix::RGBMatrix;
using rgb_matrix::Canvas;
using namespace rgb_matrix;
/*
* Abstract Module for different Modules
*/
class Module {
    public:
        int stopID = -1;
        vector<RouteETA> routeETAs;
        void execute();
        int render(Canvas * canvas, int x, int y, int height, int width);
};

/**
* Our Route Module for Managing information about 
* Buses :3
*/
class RouteModule: public Module {
    public:
        RouteModule(int stopID, vector<RouteETA> routeETAs);
        int render(Canvas * canvas, int x, int y, int height, int width);

};

#endif // module_h