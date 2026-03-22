#include <vector>

#include "Module.h"

#ifndef APPALCART_MODULE_H
#define APPALCART_MODULE_H

typedef struct {
    uint8_t ETA;
    std::string equipmentID;
    std::string routeColor;
    std::string routeName;
} RouteETA_t;

class AppalcartModule : public Module {
    private:
        std::vector<RouteETA_t> routeETAs;
        uint8_t stopID;

    public:
        AppalcartModule(uint8_t stopID);
        void execute();
        int render(rgb_matrix::Canvas * canvas, int x, int y, int height, int width);
	static std::string parseRouteETA(RouteETA_t * routeEta);
};

#endif
