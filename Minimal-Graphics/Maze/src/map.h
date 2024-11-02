#include <SDL.h>
#include <iostream>
#include <random>
#include <set>
#include <tuple>

#ifndef MAP_H
#define MAP_H

class Map
{
    int map_width, map_height;
    int goal_width, goal_height;
    bool show_path;
    float fill_percent;
    std::tuple<int, int> goal;
    std::set<std::tuple<int, int>> walls;
    std::uniform_real_distribution<double> distribution{0.0, 1.0};
    std::mt19937 gen;

public:
    void fill_map(SDL_Renderer *render);
    bool is_wall(std::tuple<int, int>);
    void print_winner(SDL_Renderer *renderer);
    int get_goal_width();
    int get_goal_height();
    bool get_show_path();
    void swap_show_path();
    void print_fastest_path(SDL_Renderer *renderer, Player *player);
    std::vector<std::tuple<int, int>> bfs(Player *player);

    Map(int map_width, int map_height, int pixel_width, int pixel_height, float fill_percent, bool show_path) : gen(std::random_device{}()), map_width(map_width), map_height(map_height), fill_percent(fill_percent), show_path(show_path)
    {

        std::uniform_int_distribution<> width_distribution(0, this->map_width / 10 - 1);
        std::uniform_int_distribution<> height_distribution(10, this->map_height / 10 - 1);

        int goal_width = width_distribution(gen);
        int goal_height = height_distribution(gen);
        this->goal_width = goal_width * 10;
        this->goal_height = goal_height * 10;

        for (int w = 0; w < map_width; w += 10)
        {
            this->walls.insert(std::make_tuple(w, 100));
        }

        for (int w = 0; w < map_width; w += 10)
        {
            for (int h = 0; h < map_height; h += 10)
            {
                if (this->distribution(gen) < fill_percent && (w != map_width / 2 && h != map_height / 2) && (w != this->goal_width && h != this->goal_height))
                {
                    this->walls.insert(std::make_tuple(w, h));
                }
            }
        }
    }
};

#endif