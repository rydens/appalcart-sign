#include "AppalcartModule.h"
#include "render.h"
#include "ColorString.h"

/**
* Constructor for Route Module
*
*/
AppalcartModule::AppalcartModule(uint8_t stopID) {
    this->stopID = stopID;
    this->scrollOffset = 150;
    this->routeETAIndex = 0;
    this->routeETAs = std::vector<RouteETA_t>();
}

void AppalcartModule::execute() {
    fetchStopData(this->stopID);
    std::cout << this->routeETAs.size() << std::endl;
}

int AppalcartModule::render(rgb_matrix::Canvas * canvas, int x, int y, int height, int width) {
    const char *bdfFontFile = "fonts/HaxorMedium-10.bdf";

    // load font
    rgb_matrix::Font mainFont;
    rgb_matrix::Color fontColor;

    std::vector<colorString_t> colorStrVec;

    if (!mainFont.LoadFont(bdfFontFile)) {
        std::cout << "couldn't load font file\n";
        return -1;
    }


    int i = 0;
    for(auto routeEta : this->routeETAs) {
        std::string displayStr = "";

        colorString_t colorStr;
        // we are limited with color as its one big string. unfortunately.
        // the draw function only takes 1 color arg, and we have one
        // big string

        // solution: new vector

        fontColor = hexToRGB((routeEta.routeColor).c_str());
        displayStr += AppalcartModule::parseRouteETA(&routeEta);
        displayStr += "   ";
        colorStr.c = fontColor;
        colorStr.s = displayStr;
        colorStr.i = i;

        // add to vector
        colorStrVec.push_back(colorStr);
        i++;
    }

    int length = busDisplayText(canvas, &mainFont, x + scrollOffset, y, colorStrVec);
    colorStrVec.clear();

    if((this->scrollOffset-- + x) + length < 0) {
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


// Fetch route info for a single routeID
json AppalcartModule::fetchRouteInfo(int routeID, int stopID) {
    cpr::Response res = cpr::Get(cpr::Url{"https://appalcart.etaspot.net/service.php"}, cpr::Parameters{
        {"service", "get_routes"},
        {"routeID", std::to_string(routeID)},
        {"stopID",  std::to_string(stopID)},
        {"token",   "TESTING"}
    });

    if (res.status_code != 200) {
        std::cerr << "get_routes failed for routeID " << routeID << "\n";
        return {};
    }

    json data = json::parse(res.text);

    if (data.contains("get_routes") && !data["get_routes"].empty()) {
        for (const auto& route : data["get_routes"]) {
            if (route.value("id", 0) == routeID) {
                return route;
            }
        }
    }

    return {};
}

void AppalcartModule::fetchStopData(int stopID) {
    // --- Call 1: get_stop_etas ---
    cpr::Response etaRes = cpr::Get(cpr::Url{"https://appalcart.etaspot.net/service.php"}, cpr::Parameters{
        {"service",    "get_stop_etas"},
        {"statusData", "1"},
        {"stopID",     std::to_string(stopID)},
        {"token",      "TESTING"}
    });

    if (etaRes.status_code != 200) {
        std::cerr << "get_stop_etas request failed\n";
        return;
    }

    json etaData = json::parse(etaRes.text);

    if (etaData["get_stop_etas"].empty() || etaData["get_stop_etas"][0]["enRoute"].empty()) {
        std::cout << "No buses en route\n";
        return;
    }

    // --- Call 2: get_routes for each unique routeID ---
    std::map<int, json> routeCache;

    for (const auto& eta : etaData["get_stop_etas"][0]["enRoute"]) {
        int routeID = eta.value("routeID", 0);
        if (routeCache.count(routeID) == 0) {
            routeCache[routeID] = fetchRouteInfo(routeID, stopID);
        }
    }

    // --- Merge ---
    for (const auto& eta : etaData["get_stop_etas"][0]["enRoute"]) {
        RouteETA_t bus;

        // From get_stop_etas
        bus.ETA         = eta.value("minutes", 0);
        bus.time        = eta.value("time", "");
        bus.status      = eta.value("status", "");
        bus.equipmentID = eta.value("equipmentID", "");
        bus.routeID     = eta.value("routeID", 0);

        // From get_routes, matched by routeID
        if (routeCache.count(bus.routeID) && !routeCache[bus.routeID].empty()) {
            const json& route = routeCache[bus.routeID];
            bus.routeName  = route.value("name", "");
            bus.abbr       = route.value("abbr", "");
            bus.routeColor = route.value("color", "");
        }

        this->routeETAs.push_back(bus);
    }
}

// void AppalcartModule::loadColors() {
//         for(auto routeEta : this->routeETAs) {
//             std::string displayStr = "";
//             colorString_t colorStr;
//             // we are limited with color as its one big string. unfortunately.
//             // the draw function only takes 1 color arg, and we have one
//             // big string

//             // solution: new vector

//             fontColor = hexToRGB((routeEta.routeColor).c_str());
//             displayStr += AppalcartModule::parseRouteETA(&routeEta);
//             displayStr += "   ";
//             colorStr.c = fontColor;
//             colorStr.s = displayStr;

//             // add to vector
//             this->colorStrVec.push_back(colorStr);
//         }
// }
