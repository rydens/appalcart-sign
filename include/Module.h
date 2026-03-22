#include <string>
#include <vector>
#include <iostream>


#include "led-matrix.h"

#ifndef MODULE_H
#define MODULE_H

/*
* Abstract Module for different Modules
*/
class Module {
    public:
        virtual ~Module() {};
        virtual void execute() =0;
        virtual int render(rgb_matrix::Canvas * canvas, int x, int y, int height, int width) =0;
};

#endif // module_h
