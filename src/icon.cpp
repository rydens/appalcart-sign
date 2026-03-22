#include "icon.h"
#include <iostream>

static void routeSwitch(Icon_t * icon, std::string chars) {
    if(chars == "B"){

    }
    else if(chars == "E"){

    }
    else if(chars == "G"){

    }
    else if(chars == "GR"){

    }
    else if(chars == "T"){

    }
    else if(chars == "M"){

    }
    else if(chars == "M"){

    }
    else if(chars == "O"){

    }
    else if(chars == "PK"){

    }
    else if(chars == "POP"){

    }
    else if(chars == "P"){

    }
    else if(chars == "R"){

    }
    else if(chars == "S"){

    }
    else if(chars == "SF"){

    }
    else if(chars == "W"){

    }
    else std::cout << "not a bus\n";
}

void generateIcon(Icon_t * icon) {
    icon->color = "blue";
    routeSwitch(icon, "b");    
}

void drawIcon(Icon_t * icon, rgb_matrix::Canvas * canvas, int x, int y) {
    for(int y = 0; y < 11; y++) {
        for(int x = 0; x < 7; x++) {
            if(icon->arr[y][x] == 'X') canvas->SetPixel(x, y, 255, 0, 0);
        }
    }
}