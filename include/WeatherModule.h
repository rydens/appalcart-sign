#ifndef WEATHER_MODULE_H
#define WEATHER_MODULE_H

#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include <iostream>
#include <string>
#include "Module.h"
#include <chrono>

using json = nlohmann::json;

const std::string FORECAST_URL = "https://api.weather.gov/gridpoints/RNK/17,16/forecast/hourly";

typedef struct {
    int temperature;
    std::string temperatureUnit;
    std::string windSpeed;
    std::string windDirection;
    std::string forcast;
    int precipitationPercetage;
    int humidityPercentage;

    // time stuff
    int hour;
    int minute;
    std::string formatted; // "HH:MM"
} Forecast_t;

class WeatherModule : public Module {
    private:
        Forecast_t currentForecast;
    public:
        WeatherModule(); //const

        void execute();
        int render(rgb_matrix::Canvas * canvas, int x, int y, int height, int width);
        void parseForecast(const cpr::Response res);
        // to get currnet forcast form outside
};  

#endif