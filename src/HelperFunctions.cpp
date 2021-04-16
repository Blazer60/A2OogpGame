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

bool isIntersecting(const glm::vec2 &pos1, const glm::vec2 &size1, const glm::vec2 &pos2, const glm::vec2 &size2)
{
    if (pos1.x + size1.x >= pos2.x && pos1.x <= pos2.x + size2.x)
    {
        // We have hit on the x-axis.
        if (pos1.y + size1.y >= pos2.y && pos1.y <= pos2.y + size2.y)
        {
            return true;  // We have also hit on the y-axis.
        }
    }
    return false;
}
