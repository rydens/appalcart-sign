#include "render.h"
#include "module.h"


void displayText(Canvas * canvas, Font * font, int x, int y,
                         Color color, std::string text) {
    // Draw Text returns length
    // (canvas, font, x, y, color, text, spacing=0, verticle=false)
    rgb_matrix::DrawText(canvas, *font,
                            x, y,
                            color, text.c_str());

}

void busDisplayText(Canvas * canvas, Font * font, int x, int y,
                    Color color, RouteETA * routeEta) {

    std::string busText = parseRouteETA(routeEta);
    displayText(canvas, font, x, y, color, busText);
}
