#include "icon.h"
#include <iostream>
#include <algorithm>
#include <cctype>
 
// sets icon rgb values and name
static void setColor(Icon_t* icon , const std::string& name,
    uint8_t r, uint8_t g, uint8_t b) {
        icon->color = name;
        icon->r = r;
        icon->g = g;
        icon->b = b;
    }

// maps the route to a color
static void routeSwitch(Icon_t* icon, const std::string& route) {
    if (route == "B")   
        setColor(icon, "Blue",0,0,255);
    else if (route == "E")
        setColor(icon, "Express",185, 202, 225);
    else if (route == "G")
        setColor(icon, "Gold",220, 219, 131);
    else if (route == "GR")   
        setColor(icon, "Green",0, 200, 0);
    else if (route == "GY")  
        setColor(icon, "Grey",89, 88, 93);
    else if (route == "T")   
        setColor(icon, "Teal",0, 200, 200);
    else if (route == "M")   
        setColor(icon, "Maroon",128,0,0);
    else if (route == "O")   
        setColor(icon, "Orange", 255, 165, 0);
    else if (route == "PK")  
        setColor(icon, "Pink", 255, 105, 180);
    else if (route == "POP") 
        setColor(icon, "Pop105", 133, 158, 68);
    else if (route == "P")   
        setColor(icon, "Purple", 128, 0, 128);
    else if (route == "R")   
        setColor(icon, "Red", 255, 0, 0);
    else if (route == "S")   
        setColor(icon, "Silver", 192, 192, 192);
    else if (route == "SF")  
        setColor(icon, "StateFarm",78, 81, 161);
    else if (route == "W")   
        setColor(icon, "Wellness", 210, 178, 207);
    else {
        setColor(icon, "White", 255, 255, 255);
        std::cout << "generateIcon: unknown route code \"" << route << "\"\n";
    }
}

// sets the color fields
void generateIcon(Icon_t* icon, const std::string& route) {
    std::transform(route.begin(), route.end(), route.begin(),
                   [](unsigned char c){ return c; });
 
    routeSwitch(icon, route);
}


// replaces every "X" with the color 
void drawIcon(Icon_t* icon, rgb_matrix::Canvas * canvas, int x, int y) {
    for (int row = 0; row < 11; row++) {
        for (int col = 0; col < 7; col++) {
            if (icon->arr[row][col] == 'X') {
                canvas->SetPixel(x + col, y + row,
                                 icon->r, icon->g, icon->b);
            }
        }
    }
}