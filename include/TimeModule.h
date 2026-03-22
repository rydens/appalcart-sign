#ifndef TIME_MODULE_H
#define TIME_MODULE_H

#include <string>
#include <ctime>
#include <iostream>
#include "Module.h"

typedef struct {
    int hour;
    int minute;
    std::string formatted; // "HH:MM"
} Time_t;

class TimeModule : public Module {
private:
    Time_t currentTime;

    Time_t parseTime(const std::tm* timeinfo);

public:
    TimeModule();

    void execute() override;
    int render(rgb_matrix::Canvas* canvas, int x, int y, int height, int width) override;

    Time_t getTime() const { return currentTime; }
};

#endif