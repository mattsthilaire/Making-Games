#include <SDL.h>
#include <iostream>
#include <random>
#include "pixel.h"
#include "snake.h"

#ifndef MAP_H
#define MAP_H

class Map
{
private:
    int map_width;
    int map_height;
    int food_x;
    int food_y;
    std::mt19937 gen;

public:
    void generate_food_pixel(Snake *snake);
    void print_food(SDL_Renderer *renderer);
    int get_food_x();
    int get_food_y();

    Map(int map_width, int map_height, int food_width, int food_height) : gen(std::random_device{}())
    {
        this->map_width = map_width;
        this->map_height = map_height;
        this->food_x = food_width;
        this->food_y = food_height;
    }
};

#endif