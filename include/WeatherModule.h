#ifndef WEATHER_MODULE_H
#define WEATHER_MODULE_H

#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include <iostream>
#include <string>
#include "Module.h"

using json = nlohmann::json;

const std::string FORECAST_URL = "https://api.weather.gov/gridpoints/RNK/17,16/forecast/hourly";

typedef struct {
    int temperature;
    std::string temperatureUnit;
    std::string windSpeed;
    std::string windDirection;
    std::string forcast;
    int preciptaionPercetage;
    int humidityPercentage;
} Forcast_t;

class WeatherModule : public Module {
    private:
        Forcast_t currentForecast;
    public:
        void execute();
        int render(rgb_matrix::Canvas * canvas, int x, int y, int height, int width);
        Forcast_t parseForecast(const cpr::Response& res);
        // to get currnet forcast form outside
        Forcast_t getForcast();
};  

#endif
