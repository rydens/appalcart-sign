#include "module.h"
#include "render.h"
using namespace std;

/**
* Constructor for Route Module
*
*/
RouteModule::RouteModule(int stopID, vector<RouteETA> v) {
    this->stopID = stopID;
    this->routeETAs = v;
}

int RouteModule::render(Canvas * canvas, int x, int y, int height, int width) {
        Color fontColor = Color(255, 255, 0);
    const char *bdfFontFile = "fonts/HaxorMedium-10.bdf";

    // load font
    Font mainFont;
    if (!mainFont.LoadFont(bdfFontFile)) {
        std::cout << "couldn't load font file\n";
        return -1;
    }

    RouteETA redRoute;
    redRoute.busID = 2;
    redRoute.ETA = 12;
    redRoute.routeColor = "Red";
    redRoute.equipmentId = "B12";
    redRoute.routeName = "Red Route";


    // we need to parse the data from the vector
    busDisplayText(canvas, &mainFont, 0, 10, fontColor, &redRoute);

    return 0;
}