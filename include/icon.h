#ifndef ICON_H
#define ICON_H
#include <string>
#include "led-matrix.h"

typedef struct {
    std::string color;
    uint8_t r, g, b;
    char arr[11][7] = {
        {'0', '0', 'X', 'X', 'X', '0', '0'},
        {'0', 'X', 'X', 'X', 'X', 'X', '0'},
        {'0', 'X', 'X', 'X', 'X', 'X', '0'},
        {'0', 'X', 'X', 'X', 'X', 'X', '0'},
        {'0', 'X', 'X', 'X', 'X', 'X', '0'},
        {'0', 'X', 'X', 'X', 'X', 'X', '0'},
        {'0', 'X', 'X', 'X', 'X', 'X', '0'},
        {'0', 'X', 'X', 'X', 'X', 'X', '0'},
        {'0', 'X', 'X', 'X', 'X', 'X', '0'},
        {'0', 'X', 'X', 'X', 'X', 'X', '0'},
        {'0', '0', 'X', 'X', 'X', '0', '0'},
    };
} Icon_t;

void generateIcon(Icon_t* icon, const std::string& route);
void drawIcon(Icon_t* icon, rgb_matrix::Canvas* canvas, int x, int y);

#endif