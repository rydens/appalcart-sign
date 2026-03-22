#include <vector>

#include "Module.h"

#ifndef APPALCART_MODULE_H
#define APPALCART_MODULE_H

typedef struct {
    uint8_t ETA;
    std::string color;
    std::string equipmentID;
    std::string routeName;
} routeETA_t;

class AppalcartModule : public Module {
    private:
        std::vector<routeETA_t> routeETAs;
        uint8_t stopID;

    public:
        AppalcartModule(uint8_t stopID);
        void execute();
        int render();
};

#endif
