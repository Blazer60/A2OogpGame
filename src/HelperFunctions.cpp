/**
 * @file HelperFunctions.cpp.c
 * @brief Miscellaneous functions that are used in a variety of places.
 * Project: A2OOPGame
 * @author Ryan Purse
 * @version 1.0.0
 * Initial Version: 14/04/2021
 */


#include "HelperFunctions.h"
#include <iostream>

void throwError(const std::string &hint)
{
    std::cout << hint << std::endl;
    std::cout << SDL_GetError() << std::endl;
    throw std::exception();
}

glm::ivec2 windowSizeToVec2(SDL_Window *window)
{
    int x, y;
    SDL_GetWindowSize(window, &x, &y);
    return glm::ivec2(x, y);
}
