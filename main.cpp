#include "include/routeParser.h"

const int STOP_ID = 37;

int main(int argc, char *argv[]) {
    std::vector<RouteETA> buses = fetchStopData(STOP_ID);

    if (buses.empty()) {
        std::cout << "No data available\n";
        return 0;
    }

    for (const auto& bus : buses) {
        std::cout << "Route:     " << bus.routeName  << " (" << bus.abbr << ")\n";
        std::cout << "Color:     " << bus.routeColor << "\n";
        std::cout << "Bus:       " << bus.equipmentId << "\n";
        std::cout << "ETA:       " << bus.ETA << " min  (" << bus.time << ")\n";
        std::cout << "Status:    " << bus.status << "\n";
        std::cout << "------------------------------\n";
    }

    return 0;
}