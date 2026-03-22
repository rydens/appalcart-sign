#include "include/routeParser.h"

const int STOP_ID = 37;

void printRGB(const std::string& hex) {
    unsigned int r, g, b;
    sscanf(hex.c_str() + 1, "%02x%02x%02x", &r, &g, &b);
    std::cout << "Color:     rgb(" << r << ", " << g << ", " << b << ")\n";
}

int main(int argc, char *argv[]) {
    std::vector<RouteETA> buses = fetchStopData(STOP_ID);

    if (buses.empty()) {
        std::cout << "No data available\n";
        return 0;
    }

    for (const auto& bus : buses) {
        std::cout << "Route:     " << bus.routeName  << " (" << bus.abbr << ")\n";
        printRGB(bus.routeColor);
        std::cout << "Bus:       " << bus.equipmentId << "\n";
        std::cout << "ETA:       " << bus.ETA << " min  (" << bus.time << ")\n";
        std::cout << "Status:    " << bus.status << "\n";
        std::cout << "------------------------------\n";
    }

    return 0;
}