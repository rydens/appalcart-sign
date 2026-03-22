#include "WeatherModule.h"
#include "render.h"
#include <string>

//WeatherModule::WeatherModule() : currentForecast{} {}

/**
* Constructor for Route Module
*
*/

WeatherModule::WeatherModule() {

}

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

    time_t timestamp = time(&timestamp);
    struct tm datetime = *localtime(&timestamp);   

    //result.hour = std::time.hours()(nullptr); //tm_hour;
    //result.minute = std::time(nullptr); //->tm_min;
    //char buffer[6];
    //strftime(buffer, sizeof(buffer), "%H:%M", timeinfo);
    result.formatted = datetime.tm_hour;

    return result;
}

void WeatherModule::execute(){
    cpr::Response res = cpr::Get(cpr::Url{FORECAST_URL});
    currentForecast = parseForecast(res);
}

int WeatherModule::render(rgb_matrix::Canvas * canvas, int x, int y, int height, int width){
    rgb_matrix::Color fontColor = rgb_matrix::Color(255, 255, 0);
    const char *bdfFontFile = "fonts/HaxorMedium-10.bdf";

    // load font
    rgb_matrix::Font mainFont;
    if (!mainFont.LoadFont(bdfFontFile)) {
        std::cout << "couldn't load font file\n";
        return -1;
    }

    std::string totalStr = "";

    // temperature
    std::string temp = std::to_string(currentForecast.temperature); // get temperature
    temp += currentForecast.temperatureUnit;
    totalStr += temp;

    // precip
    std::string precip = std::to_string(currentForecast.preciptaionPercetage);

    displayText(canvas, &mainFont, x, y, fontColor, totalStr); // temperature

    displayText(canvas, &mainFont, x + 5, y, fontColor, precip); // preciptitation

    displayText(canvas, &mainFont, x+20, y, fontColor, currentForecast.formatted); // time


    return 0;
    // render function needs the hand of blaez
}