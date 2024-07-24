#include <iostream>
#include <utility>
#include "pixel.h"
#include "snake.h"

void Snake::add_pixel()
{
    // Get last pixel value so we can add on a new pixel to the snake
    Pixel last_pixel = this->pixels.back();

    // add in new pixel. It is the same as the last pixel except moved over in the opposite direction
    // from where the previous pixel was moving
    Pixel new_pixel;
    switch (last_pixel.d)
    {
    case (dir::right):
        new_pixel.x = last_pixel.x - this->pixel_width;
        new_pixel.y = last_pixel.y;
        new_pixel.d = dir::right;
        break;
    case (dir::left):
        new_pixel.x = last_pixel.x + this->pixel_width;
        new_pixel.y = last_pixel.y;
        new_pixel.d = dir::left;
        break;
    case (dir::up):
        new_pixel.x = last_pixel.x;
        new_pixel.y = last_pixel.y + this->pixel_height;
        new_pixel.d = dir::up;
        break;
    case (dir::down):
        new_pixel.x = last_pixel.x;
        new_pixel.y = last_pixel.y - this->pixel_height;
        new_pixel.d = dir::down;
        break;
    }

    // add pixel to vector
    this->pixels.push_back(new_pixel);
}

int Snake::get_pixel_count()
{
    return this->pixels.size();
}

// Send index get a pixel value back
Pixel Snake::get_pixel(int idx)
{
    return this->pixels[idx];
}

// Send index get a pixel value back
void Snake::set_pixel_direction(dir::direction new_d, int idx)
{
    this->pixels[idx].d = new_d;
}

// Send index get a pixel value back
void Snake::set_pixel_location(int x_offset, int y_offset, int idx)
{
    this->pixels[idx].x += x_offset;
    this->pixels[idx].y += y_offset;
}

bool Snake::pixel_in_snake(Snake *snake, int x, int y)
{

    for (int i = 0, size = snake->get_pixel_count(); i < size; i++)
    {
        if (x == snake->get_pixel(i).x || y == snake->get_pixel(i).y)
        {
            return true;
        }
    }

    return false;
}