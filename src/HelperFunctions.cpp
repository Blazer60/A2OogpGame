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
#include <gtc/constants.hpp>
#include <gtx/vector_angle.hpp>

void throwError(const std::string &hint)
{
    std::cout << hint << std::endl;
    std::cout << SDL_GetError() << std::endl;
    throw std::exception();
}

void throwWarning(const std::string &hint)
{
    std::cout << hint << std::endl;
    std::cout << SDL_GetError() << std::endl;
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

std::vector<glm::vec2> getUnitCirclePoints(unsigned int n, const float &offSet)
{
    const float offSetRadians = glm::radians(offSet);
    std::vector<glm::vec2> points;
    points.reserve(n);
    for (int i = 0; i < n; ++i)
    {
        float theta = static_cast<float>(i) / static_cast<float>(n) * glm::two_pi<float>() + offSetRadians;
        float y = -glm::sin(theta);
        float x = glm::cos(theta);
        points.emplace_back(glm::vec2{ x, y });
    }
    return points;
}

std::vector<glm::vec2> getUnitConePoints(unsigned int n, const glm::vec2 &direction, float coneSpread)
{
    std::vector<glm::vec2> points;
    const double coneSpreadRadians = glm::radians(coneSpread);
    // Find the 'left most' vector angle.
    double angle = glm::orientedAngle(direction, glm::vec2(-1.f, 0.f)) + glm::pi<float>() - coneSpreadRadians / 2;

    const double step = coneSpreadRadians / static_cast<double>(n-1);

    // Then work toward the 'right most' vector.
    for (int i = 0; i < n; ++i)
    {
        double y = -glm::sin(angle);
        double x = glm::cos(angle);
        points.emplace_back(glm::vec2{ x, y });

        angle += step;
    }
    return points;
}
