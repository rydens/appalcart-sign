#ifndef RENDER_H
#define RENDER_H

#include "led-matrix.h"
#include "graphics.h"

#include "routeETA.h"

#include <unistd.h>
#include <math.h>
#include <stdio.h>
#include <signal.h>
#include <iostream>

#include <getopt.h>
#include <string.h>
#include <format>

using rgb_matrix::RGBMatrix;
using rgb_matrix::Canvas;
using namespace rgb_matrix;


std::string parseRouteETA(RouteETA * routeEta);
void displayText(Canvas * canvas, Font * font, int x, int y, Color color, std::string text);
void busDisplayText(Canvas * canvas, Font * font, int x, int y, Color color, RouteETA * routeEta);

#endif // MATRIX_H