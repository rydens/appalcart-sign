#include "timeModule.h"

TimeModule::TimeModule() : currentTime{} {}

Time_t TimeModule::parseTime(const std::tm* timeinfo) {
    Time_t result{};

    result.hour   = timeinfo->tm_hour;
    result.minute = timeinfo->tm_min;

    // Format as "HH:MM"
    char buffer[6];
    strftime(buffer, sizeof(buffer), "%H:%M", timeinfo);
    result.formatted = std::string(buffer);

    return result;
}

void TimeModule::execute() {
    std::time_t now = std::time(nullptr);
    std::tm* timeinfo = std::localtime(&now);
    currentTime = parseTime(timeinfo);
}

int TimeModule::render(rgb_matrix::Canvas* canvas, int x, int y, int height, int width) {
    draw currentTime.formatted to canvas
    return 0;
}