#include <iostream>
#include <set>
#include <tuple>
#include <SDL.h>
#include "map.h"

void Map::fill_map(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    for (const auto &wall : this->walls) // TODO: Learn this iteration pattern
    {
        int x = std::get<0>(wall);
        int y = std::get<1>(wall);
        SDL_Rect wall_pixel = {x, y, 10, 10};
        SDL_RenderFillRect(renderer, &wall_pixel);
    }

    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_Rect goal_pixel = {this->goal_width, this->goal_height, 10, 10};
    SDL_RenderFillRect(renderer, &goal_pixel);
}

bool Map::is_wall(std::tuple<int, int> position)
{
    return this->walls.find(position) != walls.end();
}

// shittest printing code alive. FML
void Map::print_winner(SDL_Renderer *renderer)
{

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    // print W
    for (int i = 100; i < 200; i++)
    {
        SDL_Rect wall_pixel = {100, i, 10, 10};
        SDL_RenderFillRect(renderer, &wall_pixel);
    }

    for (int i = 100; i < 200; i++)
    {
        SDL_Rect wall_pixel = {150, i, 10, 10};
        SDL_RenderFillRect(renderer, &wall_pixel);
    }

    for (int i = 100; i < 150; i++)
    {
        SDL_Rect wall_pixel = {i, 200, 10, 10};
        SDL_RenderFillRect(renderer, &wall_pixel);
    }

    for (int i = 150; i < 200; i++)
    {
        SDL_Rect wall_pixel = {i, 200, 10, 10};
        SDL_RenderFillRect(renderer, &wall_pixel);
    }

    for (int i = 100; i < 200; i++)
    {
        SDL_Rect wall_pixel = {200, i, 10, 10};
        SDL_RenderFillRect(renderer, &wall_pixel);
    }

    // Print I
    for (int i = 100; i < 200; i++)
    {
        SDL_Rect wall_pixel = {250, i, 10, 10};
        SDL_RenderFillRect(renderer, &wall_pixel);
    }

    // print N
    for (int i = 100; i < 200; i++)
    {
        SDL_Rect wall_pixel = {300, i, 10, 10};
        SDL_RenderFillRect(renderer, &wall_pixel);
    }

    for (int i = 0; i < 100; i++)
    {
        SDL_Rect wall_pixel = {300 + i, 100 + i, 10, 10};
        SDL_RenderFillRect(renderer, &wall_pixel);
    }

    for (int i = 100; i < 200; i++)
    {
        SDL_Rect wall_pixel = {400, i, 10, 10};
        SDL_RenderFillRect(renderer, &wall_pixel);
    }
}

int Map::get_goal_width()
{
    return this->goal_width;
}

int Map::get_goal_height()
{
    return this->goal_height;
}