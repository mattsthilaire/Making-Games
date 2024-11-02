// #include <SDL.h>
#include <SDL.h>
#include <random>
#include <iostream>

#include "player.cc"
#include "map.cc"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int REC_WIDTH = 10;
const int REC_HEIGHT = 10;

int main()
{

    // SDL Initialization stuff
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "SDL cound not initialize! SDL_ERROR:" << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("Move the Dot", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr)
    {
        std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr)
    {
        std::cout << "Renderer could not be created! SDL_Error" << SDL_GetError() << std::endl;
        return 1;
    }

    // Actual gameplay stuff
    int x = SCREEN_WIDTH / 2;
    int y = SCREEN_HEIGHT / 2;

    Player player(x, y);
    Map map(SCREEN_WIDTH, SCREEN_HEIGHT, REC_WIDTH, REC_HEIGHT, 0.4, false);

    bool quit = false;
    SDL_Event e;

    // RNG Part to help generate parts of the maze
    std::default_random_engine gen;
    std::uniform_real_distribution<double> distribution(0.0, 1.0);

    // main game loop
    // TODO: Remove if statement for out of bounds conditions and move it to the player set_x and set_y methods
    while (!quit)
    {
        if (player.get_x() == map.get_goal_width() && player.get_y() == map.get_goal_height())
        {
            while (SDL_PollEvent(&e) != 0)
            {
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                SDL_RenderClear(renderer);
                map.print_winner(renderer);
                SDL_RenderPresent(renderer);
                if (e.type == SDL_QUIT)
                {
                    quit = true;
                }
            }
        }

        else
        {

            while (SDL_PollEvent(&e) != 0)
            {

                if (e.type == SDL_QUIT)
                {
                    quit = true;
                }
                else if (e.type == SDL_KEYDOWN)
                {
                    switch (e.key.keysym.sym)
                    {

                    case SDLK_UP:
                        if (player.get_y() == 0 || map.is_wall(std::make_tuple(player.get_x(), player.get_y() - 10)))
                        {
                            continue;
                        }
                        player.set_y(-10);
                        break;

                    case SDLK_DOWN:
                        if (player.get_y() == SCREEN_HEIGHT - REC_HEIGHT || map.is_wall(std::make_tuple(player.get_x(), player.get_y() + 10)))
                        {
                            continue;
                        }
                        player.set_y(10);
                        break;

                    case SDLK_LEFT:
                        if (player.get_x() == 0 || map.is_wall(std::make_tuple(player.get_x() - 10, player.get_y())))
                        {
                            continue;
                        }
                        player.set_x(-10);
                        break;

                    case SDLK_RIGHT:
                        if (player.get_x() == SCREEN_WIDTH - REC_WIDTH || map.is_wall(std::make_tuple(player.get_x() + 10, player.get_y())))
                        {
                            continue;
                        }
                        player.set_x(10);
                        break;
                    }
                }
                else
                {
                    if (e.type == SDL_MOUSEBUTTONDOWN)
                    {
                        map.swap_show_path();
                        std::cout << map.get_show_path() << std::endl;
                    }
                }
            }

            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderClear(renderer);

            map.fill_map(renderer);
            if (map.get_show_path())
            {
                map.print_fastest_path(renderer, &player);
            }
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            SDL_Rect pixel = {player.get_x(), player.get_y(), REC_WIDTH, REC_HEIGHT};
            SDL_RenderFillRect(renderer, &pixel);

            SDL_RenderPresent(renderer);
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 1;
}