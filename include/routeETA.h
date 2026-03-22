#ifndef ROUTE_ETA_H
#define ROUTE_ETA_H


// temp until we have literal obj
typedef struct RouteETA {
    int busID;
    int ETA;
    std::string routeColor;
    std::string equipmentId;
    std::string routeName;
} RouteETA;

#endif // routeETA