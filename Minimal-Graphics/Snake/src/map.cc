#include <SDL.h>
#include <iostream>
#include <random>
#include "map.h"
#include "snake.h"

void Map::generate_food_pixel(Snake *snake)
{
    std::uniform_int_distribution<> width_distribution(0, this->map_width / 10 - 1);
    std::uniform_int_distribution<> height_distribution(0, this->map_height / 10 - 1);

    int food_x = width_distribution(gen);
    int food_y = height_distribution(gen);

    // Make sure you don't generate food that's within the snake itself
    while (snake->pixel_in_snake(snake, food_x, food_y))
    {
        int food_x = width_distribution(gen);
        int food_y = height_distribution(gen);
        std::cout << food_x << " " << food_y << " " << snake->pixel_in_snake(snake, food_x, food_y) << std::endl;
    }

    this->food_x = food_x * 10;
    this->food_y = food_y * 10;
}

void Map::print_food(SDL_Renderer *renderer)
{

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_Rect food_pixel = {this->food_x, this->food_y, 10, 10};
    SDL_RenderFillRect(renderer, &food_pixel);
}

int Map::get_food_x()
{
    return this->food_x;
}

int Map::get_food_y()
{
    return this->food_y;
}