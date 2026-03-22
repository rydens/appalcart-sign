#include <string>
#include "led-matrix.h"


typedef struct {
    std::string color;
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
        {'0', '0', 'X', 'X', 'X', '0', '0'},
    };
} Icon_t;

void generateIcon(Icon_t * icon);
void drawIcon(Icon_t * icon, rgb_matrix::Canvas * canvas, int x, int y);

