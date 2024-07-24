#include <iostream>
#include <set>
#include <vector>
#include <utility>
#include "pixel.h"
#include "direction.h"

#ifndef SNAKE_H
#define SNAKE_H

class Snake
{
private:
    int pixel_width;
    int pixel_height;
    int lead_pixel_x;
    int lead_pixel_y;
    std::vector<Pixel> pixels;
    std::set<std::pair<int, int>> pixel_set;

public:
    void add_pixel();
    std::vector<Pixel> get_pixels();
    int get_pixel_count();
    Pixel get_pixel(int idx);
    void set_pixel_direction(dir::direction new_d, int idx);
    void set_pixel_location(int x_offset, int y_offset, int idx);
    bool pixel_in_snake(Snake *snake, int x, int y);

    Snake(int lead_pixel_width, int lead_pixel_height, int lead_pixel_x, int lead_pixel_y)
        : pixel_width(lead_pixel_width), pixel_height(lead_pixel_height), lead_pixel_x(lead_pixel_x), lead_pixel_y(lead_pixel_y)
    {
        // append lead pixel to list of pixels
        Pixel lead_pixel = {
            lead_pixel_x,
            lead_pixel_y,
            dir::right};
        this->pixels.push_back(lead_pixel);
    };
};

#endif