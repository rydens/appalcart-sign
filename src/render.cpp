#include "render.h"
#include "AppalcartModule.h"
#include "ColorString.h"


rgb_matrix::Color hexToRGB(const char *str){
    int r, g, b;
    sscanf(str, "%02x%02x%02x", &r, &g, &b);
    return rgb_matrix::Color(r, b, g);
}

int displayText(rgb_matrix::Canvas * canvas, rgb_matrix::Font * font, int x, int y,
                         rgb_matrix::Color color, std::string text) {
    // Draw Text returns length
    // (canvas, font, x, y, color, text, spacing=0, verticle=false)
    return rgb_matrix::DrawText(canvas, *font,
                            x, y,
                            color, text.c_str());

}

int busDisplayText(rgb_matrix::Canvas * canvas, rgb_matrix::Font * font, int x, int y,
                    std::vector<colorString_t> colorStrVec) {

    //std::string busText = AppalcartModule::parseRouteETA(routeEta);
    int length = 0;
    //for(auto colStr : colorStrVec) { // issue: bus display text
    // is calling this more than once... maybe we pass in a simple id for what it should be?
    length += displayText(canvas, font, x, y, colStr.c, colStr.s);
    //}
    return length;
}
