#ifndef ROUTEPARSER_H
#define ROUTEPARSER_H

#include "cpr/cpr.h"
#include <nlohmann/json.hpp>
#include <iostream>
#include <vector>
#include <map>


using json = nlohmann::json;

typedef struct RouteETA {
    int ETA;                    //minutes
    int routeID;                //id of route
    std::string abbr;           //abbrevation of Bus name
    std::string status;         //"On Time"
    std::string time;           //xx:xx pm
    std::string routeColor;     //Given in hex
    std::string equipmentId;    //Bxx
    std::string routeName;      //color of route
    std::string stopName;       //Bus stop name
} RouteETA;


// void from_json(const json& j, RouteETA& r);

cpr::Response makeRequest(const std::string& url, const std::map<std::string, std::string>& params);
std::vector<RouteETA> fetchStopData(int stopID);

#endif