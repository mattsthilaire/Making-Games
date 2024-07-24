// #include <SDL.h>
#include <SDL.h>
#include <iostream>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int REC_WIDTH = 10;
const int REC_HEIGHT = 10;

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
                case SDLK_UP:
                    if (y == 0)
                    {
                        continue;
                    }
                    y -= 5;
                    break;

                case SDLK_DOWN:
                    if (y == SCREEN_HEIGHT - REC_HEIGHT)
                    {
                        continue;
                    }

                    y += 5;
                    break;
                case SDLK_LEFT:
                    if (x == 0)
                    {
                        continue;
                    }
                    x -= 5;
                    break;
                case SDLK_RIGHT:
                    if (y == SCREEN_WIDTH - REC_WIDTH)
                    {
                        continue;
                    }

                    x += 5;
                    break;
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_Rect pixel = {x, y, REC_WIDTH, REC_HEIGHT};
        SDL_RenderFillRect(renderer, &pixel);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 1;
}