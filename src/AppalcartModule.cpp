#include "AppalcartModule.h"
#include "render.h"
#include "icon.h"

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
    if (!mainFont.LoadFont(bdfFontFile)) {
        std::cout << "couldn't load font file\n";
        return -1;
    }

    int xCurrent = 0;
    for (uint8_t index = 0; index < this->routeETAs.size(); index++) {
        
        RouteETA_t * currentRoute = &this->routeETAs[index];
        std::string displayStr = parseRouteETA(currentRoute) + "   ";
        std::string colorStr = currentRoute->routeColor;

        Icon_t icon;
        generateIcon(&icon, "B", hexStringToColor(colorStr.c_str()));
        xCurrent += drawIcon(&icon, canvas, x + scrollOffset + xCurrent - 2, y - 7); // 7 is height
        xCurrent += rgb_matrix::DrawText(canvas, mainFont, x + scrollOffset + xCurrent, y, hexStringToColor(colorStr.c_str()), displayStr.c_str());      

    }

    if (this->scrollOffset-- + xCurrent == 0) {
        scrollOffset = 150;
    }

    return 0;
}

std::string AppalcartModule::parseRouteETA(RouteETA_t * routeEta) {
    std::string routeEtaStr = routeEta->abbr;       // R
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

rgb_matrix::Color AppalcartModule::hexStringToColor(const char * s) {
    uint8_t r, g, b;
    sscanf(s, "#%02hhx%02hhx%02hhx", &r, &g, &b);
    return rgb_matrix::Color(r, b, g);
}
