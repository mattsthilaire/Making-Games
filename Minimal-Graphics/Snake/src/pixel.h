#include "direction.h"

#ifndef PIXEL_H
#define PIXEL_H

typedef struct Pixel
{
    int x;
    int y;
    dir::direction d;
} Pixel;

#endif