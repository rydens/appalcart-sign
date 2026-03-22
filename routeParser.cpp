#include "./include/routeParser.h"

cpr::Response makeRequest(const std::string& url, const std::map<std::string, std::string>& params) {
    cpr::Parameters cprParams{};
    for (const auto& [key, value] : params) {
        cprParams.Add({key, value});
    }
    return cpr::Get(cpr::Url{url}, cprParams);
}

// Fetch route info for a single routeID
static json fetchRouteInfo(int routeID, int stopID) {
    cpr::Response res = makeRequest("https://appalcart.etaspot.net/service.php", {
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

std::vector<RouteETA> fetchStopData(int stopID) {
    std::vector<RouteETA> results;

    // --- Call 1: get_stop_etas ---
    cpr::Response etaRes = makeRequest("https://appalcart.etaspot.net/service.php", {
        {"service",    "get_stop_etas"},
        {"statusData", "1"},
        {"stopID",     std::to_string(stopID)},
        {"token",      "TESTING"}
    });

    if (etaRes.status_code != 200) {
        std::cerr << "get_stop_etas request failed\n";
        return results;
    }

    json etaData = json::parse(etaRes.text);

    if (etaData["get_stop_etas"].empty() || etaData["get_stop_etas"][0]["enRoute"].empty()) {
        std::cout << "No buses en route\n";
        return results;
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
        RouteETA bus;

        // From get_stop_etas
        bus.ETA         = eta.value("minutes", 0);
        bus.time        = eta.value("time", "");
        bus.status      = eta.value("status", "");
        bus.equipmentId = eta.value("equipmentID", "");
        bus.routeID     = eta.value("routeID", 0);

        // From get_routes, matched by routeID
        if (routeCache.count(bus.routeID) && !routeCache[bus.routeID].empty()) {
            const json& route = routeCache[bus.routeID];
            bus.routeName  = route.value("name", "");
            bus.abbr       = route.value("abbr", "");
            bus.routeColor = route.value("color", "");
        }

        results.push_back(bus);
    }

    return results;
}