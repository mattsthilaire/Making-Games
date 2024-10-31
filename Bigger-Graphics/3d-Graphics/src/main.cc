#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <SDL.h>

#include "matrix.cc"
#include "point.cc"

std::vector<std::string> tokenizeLine(const std::string &line)
{
    std::vector<std::string> tokens;
    std::istringstream iss(line);
    std::string token;

    while (iss >> token)
    {
        tokens.push_back(token);
    }

    return tokens;
}

std::vector<Point> get_vertices(std::string filename)
{
    std::vector<Point> points;
    std::string line;
    std::ifstream file(filename);
    while (getline(file, line))
    {
        std::vector<std::string> tokens = tokenizeLine(line);
        if (tokens[0] == "v")
        {
            Point p(std::stof(tokens[1]), std::stof(tokens[2]), std::stof(tokens[3]));
            points.push_back(p);
        }
    }

    return points;
}

void get_obj_data(std::string filename, std::vector<Point> *vertices, std::vector<Point> *faces)
{
    std::vector<Point> points;
    std::string line;
    std::ifstream file(filename);
    while (getline(file, line))
    {
        std::vector<std::string> tokens = tokenizeLine(line);
        if (tokens[0] == "v")
        {
            Point p(std::stof(tokens[1]), std::stof(tokens[2]), std::stof(tokens[3]));
            vertices->push_back(p);
        }
        else if (tokens[0] == "f")
        {
            Point p(std::stof(tokens[1]), std::stof(tokens[2]), std::stof(tokens[3]));
            faces->push_back(p);
        }
    }
}

// std::vector<Point> create_raster_points(std::vector<Point> points)
//{
// }

int main(int argc, char *argv[])
{

    std::cout << argv[1] << std::endl;

    //"src/xtree.obj"

    int HEIGHT = 512;
    int WIDTH = 512;

    Point p_local(-0.5, 0.5, -0.5);
    Matrix M(std::vector<float>{0.871214, 0, -0.490904, 0},
             std::vector<float>{-0.192902, 0.919559, -0.342346, 0},
             std::vector<float>{0.451415, 0.392953, 0.801132, 0},
             std::vector<float>{14.777467, 29.361945, 27.993464, 1});

    Matrix M_inverse = M.inverse();

    // std::string filename = std::string(argv[0]);

    std::string filename = "src/xtree.obj";
    std::vector<Point> vertices;
    std::vector<Point> faces;
    get_obj_data(argv[1], &vertices, &faces);

    std::vector<Point> raster_points;

    for (Point p : vertices)
    {
        Point camera = M_inverse.vec_mul_mat(p);
        Point p_prime = camera.camera2p_prime();
        if (!p_prime.is_visable(WIDTH, HEIGHT))
        {
            // continue;
        }
        Point p_normalized = p_prime.prime2normalized(WIDTH, HEIGHT);
        Point p_raster = p_normalized.normalized2raster(WIDTH, HEIGHT);

        raster_points.push_back(p_raster);
    }

    for (Point face : faces)
    {
        std::cout << face.x << " " << face.y << " " << face.z << std::endl;
    }

    // SDL Stuff
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "SDL cound not initialize! SDL_ERROR:" << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("Move the Dot", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
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
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        for (Point face : faces)
        // for (Point p : raster_points)
        {
            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 0);
            SDL_RenderDrawLine(renderer, (int)raster_points[face.x - 1].x, (int)raster_points[face.x - 1].y, (int)raster_points[face.y - 1].x, (int)raster_points[face.y - 1].y);
            SDL_RenderDrawLine(renderer, (int)raster_points[face.y - 1].x, (int)raster_points[face.y - 1].y, (int)raster_points[face.z - 1].x, (int)raster_points[face.z - 1].y);
            SDL_RenderDrawLine(renderer, (int)raster_points[face.z - 1].x, (int)raster_points[face.z - 1].y, (int)raster_points[face.x - 1].x, (int)raster_points[face.x - 1].y);
        }

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}