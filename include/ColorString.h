#ifndef COLOR_STRING_H
#define COLOR_STRING_H

#include <string>
#include "led-matrix.h"

typedef struct {
    int i;
    rgb_matrix::Color c;
    std::string s;
    
} colorString_t;

#endif