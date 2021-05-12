/**
 * @file HelperFunctions.h
 * @brief Miscellaneous functions that are used in a variety of places.
 * Project: A2OOPGame
 * @author Ryan Purse
 * @version 1.0.0
 * Initial Version: 14/04/2021
 */


#include <SDL.h>
#include <type_traits>
#include <string>
#include <glm.hpp>
#include <vector>

/**
 * Gets the time since SDL was initialised in seconds.
 * @tparam T A numeric type. E.g.: int, float, double
 * @return time in seconds.
 */
template<typename T>
T getTicks()
{
    /*
     * Only numeric types can be used to get ticks since SDL was initialised.
     * static_cast will also catch this expression but static assert gives more detail.
     */
    static_assert(std::is_arithmetic_v<T>, "getTicks() only accepts numeric values. E.g.: int, float, double");
    return static_cast<T>(SDL_GetTicks()) / 1000;
}

/**
 * Normalises a value between 0 and 1 inclusive. However, there are no bounds checks.
 * So x can be outside the range 0-1.
 * @tparam T A numeric type you want to normalise.
 * @param x The number being normalised
 * @param lB The smallest number x can be.
 * @param uB The largest number x can be.
 * @return A number between [0, 1] inclusive.
 */
template<typename T>
T normalise(const T &x, const T &lB, const T &uB)
{
    static_assert(std::is_arithmetic_v<T>, "normalise() only accepts numeric values. E.g.: int, float, double");
    return (x - lB) / (uB - lB);
}

/**
 * Throw an error to console and stop execution.
 * ONLY to be used when the program cannot continue.
 * @param hint Additional information for debugging
 */
void throwError(const std::string &hint);

/**
 * Throws a warning to console but does not stop execution.
 * E.g.: Sound files could not be loaded but the game can
 * continue.
 * @param hint Additional information for debugging
 */
void throwWarning(const std::string &hint);

/**
 * Converts an SDL window size into a glm vec2
 * @param window The window with the size
 * @return The width and height of the window.
 */
glm::ivec2 windowSizeToVec2(SDL_Window *window);

bool isIntersecting(const glm::vec2 &pos1, const glm::vec2 &size1, const glm::vec2 &pos2, const glm::vec2 &size2);

/**
 * Gets evenly spaced vectors within a unit circle.
 * @param n The number of vectors that you want.
 * @param offSet The angle off of the horizontal plane (1, 0) (in degrees)
 * @returns n amount of points in a unit circle
 */
std::vector<glm::vec2> getUnitCirclePoints(unsigned int n, const float &offSet=0);

/**
 * Gets unit vectors pointing towards a direction.
 * @param n The number of vectors that you want.
 * @param direction Where you want the centered vector to aim towards.
 * @param coneSpread How spread out you want the vectors (in degrees)
 * @returns n amount of points within the specified cone spread.
 */
std::vector<glm::vec2> getUnitConePoints(unsigned int n, const glm::vec2 &direction, float coneSpread=20.f);

