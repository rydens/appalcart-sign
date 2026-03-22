#ifndef RENDER_H
#define RENDER_H

#include "led-matrix.h"
#include "graphics.h"
#include "AppalcartModule.h"

#include <unistd.h>
#include <math.h>
#include <stdio.h>
#include <signal.h>
#include <iostream>

#include <getopt.h>
#include <string.h>
#include <format>

void displayText(rgb_matrix::Canvas * canvas, rgb_matrix::Font * font, int x, int y, rgb_matrix::Color color, std::string text);
void busDisplayText(rgb_matrix::Canvas * canvas, rgb_matrix::Font * font, int x, int y, rgb_matrix::Color color, RouteETA_t * routeEta);

#endif // MATRIX_H
