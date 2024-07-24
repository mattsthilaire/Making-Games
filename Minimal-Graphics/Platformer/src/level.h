#include <SDL.h>
#include <iostream>
#include <set>
#include <utility>
#include "utils.h"

class Level
{
private:
    int number;
    int width_, height_;
    std::set<std::pair<int, int>> platform_pixels_;

public:
    int &width() { return width_; };
    const int &width() const { return width_; };
    int &height() { return height_; };
    const int &height() const { return height_; };

    std::set<std::pair<int, int>> &platform_pixels() { return platform_pixels_; };
    const std::set<std::pair<int, int>> &platform_pixels() const { return platform_pixels_; };

    void draw_level(SDL_Renderer *renderer);
    bool pixel_in_level(std::pair<int, int> p);

    Level(std::string filename) : width_(10), height_(10), number(1)
    {
        platform_pixels() = read_level_file(filename);
    };

    Level(int num) : width_(10), height_(10)
    {
        this->number = num;
    };
};