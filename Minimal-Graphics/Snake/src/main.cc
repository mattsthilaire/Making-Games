// #include <SDL.h>
#include <SDL.h>
#include <iostream>
#include <string.h>

#include "snake.cc"
#include "map.cc"
#include "direction.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int REC_WIDTH = 10;
const int REC_HEIGHT = 10;
const int FRAME_DELAY = 50; // Delay in milliseconds (e.g., 100ms for 10 frames per second)

enum directions
{
    right,
    left,
    up,
    down
};

int main()
{
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

    int x = SCREEN_WIDTH / 2;
    int y = SCREEN_HEIGHT / 2;

    Snake snake(10, 10, x, y);
    Map map(SCREEN_WIDTH, SCREEN_HEIGHT, 10, 10);
    map.generate_food_pixel(&snake);

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
                // Change direction of lead pixel
                switch (e.key.keysym.sym)
                {
                case SDLK_UP:
                    if (snake.get_pixel(0).d != dir::up)
                    {
                        snake.set_pixel_direction(dir::up, 0);
                    }
                    break;
                case SDLK_DOWN:
                    if (snake.get_pixel(0).d != dir::down)
                    {
                        snake.set_pixel_direction(dir::down, 0);
                    }
                    break;
                case SDLK_LEFT:
                    if (snake.get_pixel(0).d != dir::left)
                    {
                        snake.set_pixel_direction(dir::left, 0);
                    }
                    break;
                case SDLK_RIGHT:
                    if (snake.get_pixel(0).d != dir::right)
                    {
                        snake.set_pixel_direction(dir::right, 0);
                    }
                    break;
                }
            }
        }

        // Change locations of pixels
        for (int i = 0, size = snake.get_pixel_count(); i < size; i++)
        {
            switch (snake.get_pixel(i).d)
            {
            case dir::right:
                snake.set_pixel_location(10, 0, i);
                break;
            case dir::left:
                snake.set_pixel_location(-10, 0, i);
                break;
            case dir::up:
                snake.set_pixel_location(0, -10, i);
                break;
            case dir::down:
                snake.set_pixel_location(0, 10, i);
                break;
            }
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        for (int i = 0, size = snake.get_pixel_count(); i < size; i++)
        {
            SDL_Rect pixel = {snake.get_pixel(i).x, snake.get_pixel(i).y, REC_WIDTH, REC_HEIGHT};
            SDL_RenderFillRect(renderer, &pixel);
        }

        if (snake.get_pixel(0).x == map.get_food_x() && snake.get_pixel(0).y == map.get_food_y())
        {
            map.generate_food_pixel(&snake);
            snake.add_pixel();
        }

        map.print_food(renderer);

        // Change direction of all pixels to the prceeding pixel's direction
        for (int size = snake.get_pixel_count() - 1, i = size; i > 0; i--)
        {
            dir::direction new_d = snake.get_pixel(i - 1).d;
            snake.set_pixel_direction(new_d, i);
        }

        // terminate conditions

        // Condition 1: If player goes out of bound, they lose
        if (snake.get_pixel(0).x < 0 || snake.get_pixel(0).x > SCREEN_WIDTH || snake.get_pixel(0).y < 0 || snake.get_pixel(0).y > SCREEN_HEIGHT)
        {
            quit = true;
        }

        // Condition 2: if player's lead pixel crosses paths with another part of the snake, end game
        for (int i = 1, size = snake.get_pixel_count(); i < size; i++)
        {
            if (snake.get_pixel(i).x == snake.get_pixel(0).x && snake.get_pixel(i).y == snake.get_pixel(0).y)
            {
                quit = true;
            }
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(FRAME_DELAY);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 1;
}