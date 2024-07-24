#include <SDL.h>
#include <iostream>
#include <set>
#include <utility>
#include "level.h"

void Level::draw_level(SDL_Renderer *renderer)
{
    std::set<std::pair<int, int>>::iterator itr;

    for (itr = this->platform_pixels().begin(); itr != this->platform_pixels().end(); itr++)
    {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_Rect platform_pixel = {itr->first, itr->second, 10, 10};
        SDL_RenderFillRect(renderer, &platform_pixel);
    }
}

bool Level::pixel_in_level(std::pair<int, int> p)
{

    if (this->platform_pixels().count(p) > 0)
    {
        return true;
    }

    return false;
}