#include "render.h"
#include "AppalcartModule.h"


int displayText(rgb_matrix::Canvas * canvas, rgb_matrix::Font * font, int x, int y,
                         rgb_matrix::Color color, std::string text) {
    // Draw Text returns length
    // (canvas, font, x, y, color, text, spacing=0, verticle=false)
    return rgb_matrix::DrawText(canvas, *font,
                            x, y,
                            color, text.c_str());

}

int busDisplayText(rgb_matrix::Canvas * canvas, rgb_matrix::Font * font, int x, int y,
                    rgb_matrix::Color color, std::string busText) {

    //std::string busText = AppalcartModule::parseRouteETA(routeEta);
    return displayText(canvas, font, x, y, color, busText);
}
