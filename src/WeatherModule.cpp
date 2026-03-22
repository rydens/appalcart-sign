#include "WeatherModule.h"

//WeatherModule::WeatherModule() : currentForecast{} {}

Forcast_t WeatherModule::parseForecast(const cpr::Response& res) {
    Forcast_t result{};

    if(res.status_code != 200) {
        std::cerr << "Request Failed: " << res.status_code << "\n";
        return result;
    }

    json data = json::parse(res.text);

    // get into the location of most values
    if(!data.contains("properties") ||
        !data["properties"].contains("periods") ||
        data["properties"]["periods"].empty()) {
            std::cerr << "No Forcast data found\n";
            return result;
        }

    const json& period = data["properties"]["periods"][0];

    result.temperature = period.value("temperature", 0);
    result.temperatureUnit = period.value("temperatureUnit", "");
    result.windSpeed = period.value("windSpeed", "");
    result.windDirection = period.value("windDirection", "");
    result.forcast = period.value("shortForcast", "");

    if(!data.contains("probabilityOfPrecipitation") ||
        !data["probabilityOfPrecipitation"]["value"].is_null()){
            result.preciptaionPercetage = period["probabilityOfPrecipitation"].value("value",0);
    }

    if(!data.contains("relativeHumidity") ||
        !data["relativeHumidity"]["value"].is_null()){
            result.humidityPercentage = period["relativeHumidity"].value("value",0);
    }

    return result;
}

void WeatherModule::execute(){
    cpr::Response res = cpr::Get(cpr::Url{FORECAST_URL});
    currentForecast = parseForecast(res);
}

int WeatherModule::render(rgb_matrix::Canvas * canvas, int x, int y, int height, int width){
    return 0;
    // render function needs the hand of blaez
}