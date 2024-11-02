#include <iostream>
#include <deque>
#include <map>
#include <unordered_map>
#include <set>
#include <tuple>
#include <SDL.h>
#include "map.h"
#include "player.h"

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

bool Map::get_show_path()
{
    return this->show_path;
}

void Map::swap_show_path()
{
    this->show_path = !this->show_path;
}

// BFS stuff below for now
void Map::print_fastest_path(SDL_Renderer *renderer, Player *player)
{

    std::vector<std::tuple<int, int>> results = this->bfs(player);

    for (const auto &path : results)
    {
        int x = std::get<0>(path);
        int y = std::get<1>(path);
        SDL_Rect path_pixel = {x, y, 10, 10};
        SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
        SDL_RenderFillRect(renderer, &path_pixel);
    }
}

std::vector<std::tuple<int, int>> Map::bfs(Player *player)
{
    std::vector<std::tuple<int, int>> result_path;

    std::deque<std::tuple<int, int>> q;
    std::map<std::tuple<int, int>, std::tuple<int, int>> parent_paths;
    std::set<std::tuple<int, int>> visited;

    // Start position
    std::tuple<int, int> start = std::make_tuple(player->get_x(), player->get_y());
    std::tuple<int, int> goal = std::make_tuple(this->get_goal_width(), this->get_goal_height());

    q.push_back(start);
    visited.insert(start); // Mark start as visited immediately

    std::tuple<int, int> curr;
    bool found_path = false;

    // BFS search
    while (!q.empty())
    {
        curr = q.front();
        q.pop_front();

        // Check if we reached the goal
        if (std::get<0>(curr) == this->get_goal_width() && std::get<1>(curr) == this->get_goal_height())
        {
            found_path = true;
            break;
        }

        // Check all four directions
        std::vector<std::tuple<int, int>> neighbors = {
            std::make_tuple(std::get<0>(curr) - 10, std::get<1>(curr)), // left
            std::make_tuple(std::get<0>(curr) + 10, std::get<1>(curr)), // right
            std::make_tuple(std::get<0>(curr), std::get<1>(curr) - 10), // up
            std::make_tuple(std::get<0>(curr), std::get<1>(curr) + 10)  // down
        };

        for (const auto &neighbor : neighbors)
        {
            // Check if neighbor is valid and unvisited
            if (std::get<0>(neighbor) >= 0 && std::get<0>(neighbor) < map_width &&
                std::get<1>(neighbor) >= 0 && std::get<1>(neighbor) < map_height &&
                !is_wall(neighbor) && visited.find(neighbor) == visited.end())
            {
                visited.insert(neighbor);
                parent_paths[neighbor] = curr;
                q.push_back(neighbor);
            }
        }
    }

    // Reconstruct path if we found one
    if (found_path)
    {
        curr = goal;
        while (curr != start)
        {
            if (curr != goal)
            {
                result_path.push_back(curr);
            }
            curr = parent_paths[curr];
        }
        std::reverse(result_path.begin(), result_path.end());
    }

    return result_path;
}
