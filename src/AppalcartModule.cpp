#include "AppalcartModule.h"
#include "render.h"

/**
* Constructor for Route Module
*
*/
AppalcartModule::AppalcartModule(uint8_t stopID) {
    this->stopID = stopID;
}

void AppalcartModule::execute() {
    // till we get up to date info make own struct and push into vector
    RouteETA_t redRoute;
    redRoute.busID = 2;
    redRoute.ETA = 12;
    redRoute.routeColor = "#FF0000";
    redRoute.equipmentID = "B12";
    redRoute.routeName = "Red Route";

    // push into routeETAS
    std::vector<RouteETA_t> v;
    v.push_back(redRoute);
}

int AppalcartModule::render(rgb_matrix::Canvas * canvas, int x, int y, int height, int width) {
    Color fontColor = Color(255, 255, 0);
    const char *bdfFontFile = "fonts/HaxorMedium-10.bdf";

    // load font
    rgb_matrix::Font mainFont;
    if (!mainFont.LoadFont(bdfFontFile)) {
        std::cout << "couldn't load font file\n";
        return -1;
    }

    RouteETA_t redRoute;
    redRoute.ETA = 12;
    redRoute.routeColor = "#FF0000";
    redRoute.equipmentId = "B12";
    redRoute.routeName = "Red Route";


    // we need to parse the data from the vector
    busDisplayText(canvas, &mainFont, 0, 10, fontColor, &redRoute);

    return 0;
}

std::string AppalcartModule::parseRouteETA(RouteETA_t * routeEta) {
    std::string routeEtaStr = routeEta->routeColor; // Red
    routeEtaStr += " Route: ";                       // Red Route:
    routeEtaStr += std::to_string(routeEta->ETA);   // Red Route: 12
    routeEtaStr += " Minutes";                     // Red Route: 12 Minutes
    return routeEtaStr;
}
