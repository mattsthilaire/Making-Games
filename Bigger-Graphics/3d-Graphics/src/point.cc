#include "point.h"
#include <cmath>

bool Point::is_visable(float height, float width)
{
    return fabs(this->x) <= width / 2 && fabs(this->y) <= height / 2;
}

Point Point::camera2p_prime()
{
    Point p_prime(this->x / (-this->z), this->y / (-this->z));
    return p_prime;
}

Point Point::prime2normalized(float width, float height)
{
    Point p_normalized((this->x + (2 / 2)) / 2, (this->y + (2 / 2)) / 2);
    return p_normalized;
}

Point Point::normalized2raster(float width, float height)
{
    Point p_raster((this->x * width), ((1 - this->y) * height));
    return p_raster;
}