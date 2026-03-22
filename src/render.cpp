#include "render.h"
#include "AppalcartModule.h"


void displayText(rgb_matrix::Canvas * canvas, rgb_matrix::Font * font, int x, int y,
                         rgb_matrix::Color color, std::string text) {
    // Draw Text returns length
    // (canvas, font, x, y, color, text, spacing=0, verticle=false)
    rgb_matrix::DrawText(canvas, *font,
                            x, y,
                            color, text.c_str());

}

void busDisplayText(rgb_matrix::Canvas * canvas, rgb_matrix::Font * font, int x, int y,
                    rgb_matrix::Color color, RouteETA_t * routeEta) {

    std::string busText = AppalcartModule::parseRouteETA(routeEta);
    displayText(canvas, font, x, y, color, busText);
}
