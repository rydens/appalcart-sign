#include "AppalcartModule.h"
#include "render.h"

/**
* Constructor for Route Module
*
*/
AppalcartModule::AppalcartModule(uint8_t stopID) {
    this->stopID = stopID;
    this->scrollOffset = 150;
    this->routeETAIndex = 0;
}

void AppalcartModule::execute() {
    // till we get up to date info make own struct and push into vector
    RouteETA_t redRoute;
    redRoute.ETA = 12;
    redRoute.routeColor = "#FF0000";
    redRoute.equipmentID = "B12";
    redRoute.routeName = "Red Route";

    // push into routeETAS
    this->routeETAs.push_back(redRoute);
}

int AppalcartModule::render(rgb_matrix::Canvas * canvas, int x, int y, int height, int width) {
    rgb_matrix::Color fontColor = rgb_matrix::Color(255, 255, 0);
    const char *bdfFontFile = "fonts/HaxorMedium-10.bdf";

    // load font
    rgb_matrix::Font mainFont;
    if (!mainFont.LoadFont(bdfFontFile)) {
        std::cout << "couldn't load font file\n";
        return -1;
    }

    RouteETA_t rETA = (this->routeETAs).at(routeETAIndex);    
    // we need to parse the data from the vector
    int length = busDisplayText(canvas, &mainFont, x + scrollOffset, y, fontColor, &rETA);

    //int maxLength = 300;
    //std::cout << length;
    if((this->scrollOffset-- + x) + length < 0) {
        this->routeETAIndex = (this->routeETAIndex+1) % this->routeETAs.size(); // gets next routeETA_t
        this->scrollOffset = 150 - x;
    }

    return 0;
}

std::string AppalcartModule::parseRouteETA(RouteETA_t * routeEta) {
    std::string routeEtaStr = routeEta->routeColor; // Red
    routeEtaStr += " Route: ";                       // Red Route:
    routeEtaStr += std::to_string(routeEta->ETA);   // Red Route: 12
    routeEtaStr += " Minutes";                     // Red Route: 12 Minutes
    return routeEtaStr;
}
