#ifndef APPALCART_MODULE_H
#define APPALCART_MODULE_H

#include <vector>
#include <nlohmann/json.hpp>
#include <cpr/cpr.h>

#include "Module.h"

using json = nlohmann::json;

typedef struct {
    int ETA;                // minutes
    int routeID;            // route ID
    std::string abbr;           // route name abbreviation
    std::string status;         // "On Time" or ETA or "-"
    std::string time;           // xx:xx pm
    std::string routeColor;     // Route color in hex
    std::string equipmentID;    // Bus id "Bxx"
    std::string routeName;      // color of route
    std::string stopName;       // Bus stop name
} RouteETA_t;

class AppalcartModule : public Module {
    private:
        std::vector<RouteETA_t> routeETAs;
        uint8_t stopID;
        std::string stopName;
        int scrollOffset;
        uint8_t routeETAIndex;
        rgb_matrix::Color hexStringToColor(const char * s);
    	rgb_matrix::Font mainFont;

    public:
	    AppalcartModule(uint8_t stopID, const char * bdfFontFile);
        void execute();
        int render(rgb_matrix::Canvas * canvas, int x, int y, int height, int width);
	    static std::string parseRouteETA(RouteETA_t * routeEta);
        static json fetchRouteInfo(int routeID, int stopID);
        void fetchStopData(int stopID);
        rgb_matrix::Font getFont();

};

#endif
