#include <iostream>
#include "SDL.h"
#include "glm.hpp"

int main(int argc, char *argv[])
{
    std::cout << "Hello, World!" << std::endl;
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) { return -3; }
    glm::ivec2 screenSize{ 640, 480 };
    SDL_Window *window = SDL_CreateWindow("e", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenSize.x, screenSize.y, SDL_WINDOW_SHOWN);

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    bool isRunning = true;
    while (isRunning)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                isRunning = false;
            }
        }

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_RenderPresent(renderer);
    }
    return 0;
}
