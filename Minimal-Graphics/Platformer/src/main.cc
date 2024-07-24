#include <SDL.h>
#include <SDL.h>
#include <random>
#include <iostream>
#include "level.cc"
#include "player.cc"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char *argv[])
{

    // SDL Initialization stuff
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "SDL cound not initialize! SDL_ERROR:" << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("Platformer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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

    Player player(0, SCREEN_HEIGHT / 2);
    Level level(argv[1]);

    bool quit = false;
    SDL_Event e;

    // main game loop
    while (!quit)
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
                case SDLK_SPACE:
                    if (player.on_platform(&level))
                    {
                        player.y_velocity() = -12;
                        player.y() += player.y_velocity() - 5;
                        break;
                    }
                    break;
                }
            }
        }

        // Get the current state of the keyboard
        const Uint8 *currentKeyStates = SDL_GetKeyboardState(NULL);

        // Update player position based on key states
        if (currentKeyStates[SDL_SCANCODE_LEFT])
        {
            if (!player.hit_wall_left(&level))
            {
                player.x() -= 1;
            }
        }
        if (currentKeyStates[SDL_SCANCODE_RIGHT])
        {
            if (!player.hit_wall_right(&level))
            {
                player.x() += 1;
            }
        }

        if (!player.on_platform(&level))
        {
            player.y() += player.y_velocity();
        }

        if (player.y_velocity() < 1)
        {
            player.y_velocity() += 1;
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        player.draw_player(renderer);
        level.draw_level(renderer);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 1;
}