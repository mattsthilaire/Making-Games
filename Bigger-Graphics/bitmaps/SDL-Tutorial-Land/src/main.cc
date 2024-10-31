#include <SDL.h>
#include <iostream>

// The window we'll be rendering to
SDL_Window *gWindow = NULL;

// The surface contained by the window
SDL_Surface *gScreenSurface = NULL;

// The image we will load and show on the screen
SDL_Surface *gHelloWorld = NULL;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

bool init()
{
    bool success = true;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "SDL did not initialize.";
        success = false;
    }
    else
    {
        gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == NULL)
        {
            std::cout << "Window could not be created: " << SDL_GetError() << std::endl;
            success = false;
        }
        else
        {
            gScreenSurface = SDL_GetWindowSurface(gWindow);
        }
    }

    return success;
}

bool load_media(std::string filename)
{
    // Loading success flag
    bool success = true;

    // Load splash image
    gHelloWorld = SDL_LoadBMP(filename.c_str()); // need C-style string for this function
    if (gHelloWorld == NULL)
    {
        printf("Unable to load images%s! SDL Error: %s\n", filename.c_str(), SDL_GetError());
        success = false;
    }

    return success;
}

void close()
{
    SDL_FreeSurface(gHelloWorld);
    gHelloWorld = NULL;

    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    SDL_Quit();
}

int main()
{
    if (!init())
    {
        std::cout << "Failed Initialization" << std::endl;
    }
    else
    {
        if (false)
        {
            std::cout << "Failed to load media" << std::endl;
        }
        else
        {
            gHelloWorld = SDL_LoadBMP("images/sample_image.bmp");
            SDL_BlitSurface(gHelloWorld, NULL, gScreenSurface, NULL);
            SDL_UpdateWindowSurface(gWindow);
            SDL_Event e;
            bool quit = false;
            while (quit == false)
            {
                while (SDL_PollEvent(&e))
                {
                    if (e.type == SDL_QUIT)
                    {
                        quit = true;
                    }

                    if (e.type == SDL_KEYDOWN)
                    {
                        switch (e.key.keysym.sym)
                        {
                        case SDLK_a:
                            SDL_FreeSurface(gHelloWorld);
                            gHelloWorld = NULL;
                            gHelloWorld = SDL_LoadBMP("images/a.bmp");
                            SDL_BlitSurface(gHelloWorld, NULL, gScreenSurface, NULL);
                            SDL_UpdateWindowSurface(gWindow);
                            break;
                        case SDLK_b:
                            SDL_FreeSurface(gHelloWorld);
                            gHelloWorld = NULL;
                            gHelloWorld = SDL_LoadBMP("images/b.bmp");
                            SDL_BlitSurface(gHelloWorld, NULL, gScreenSurface, NULL);
                            SDL_UpdateWindowSurface(gWindow);
                            break;
                        case SDLK_c:
                            SDL_FreeSurface(gHelloWorld);
                            gHelloWorld = NULL;
                            gHelloWorld = SDL_LoadBMP("images/c.bmp");
                            SDL_BlitSurface(gHelloWorld, NULL, gScreenSurface, NULL);
                            SDL_UpdateWindowSurface(gWindow);
                            break;
                        case SDLK_x:
                            SDL_FreeSurface(gHelloWorld);
                            gHelloWorld = NULL;
                            gHelloWorld = SDL_LoadBMP("images/x_event.bmp");
                            SDL_BlitSurface(gHelloWorld, NULL, gScreenSurface, NULL);
                            SDL_UpdateWindowSurface(gWindow);
                            break;
                        }
                    }
                }
            }
        }
    }

    return 1;
}