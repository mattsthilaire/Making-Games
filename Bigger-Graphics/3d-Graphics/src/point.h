#include <iostream>

#ifndef POINT_H
#define POINT_H

class Point
{
public:
    float x, y, z;

    Point()
    {
        this->x = 0;
        this->y = 0;
        this->z = 0;
    };

    Point(float x, float y)
    {
        this->x = x;
        this->y = y;
        this->z = 0;
    };

    Point(float x, float y, float z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    };

    bool is_visable(float height, float width);
    Point camera2p_prime();
    Point prime2normalized(float width, float height);
    Point normalized2raster(float width, float height);
};

#endif