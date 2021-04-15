/**
 * @file HelperFunctions.h
 * @brief Miscellaneous functions that are used in a variety of places.
 * Project: A2OOPGame
 * @author Ryan Purse
 * @version 1.0.0
 * Initial Version: 14/04/2021
 */

// include guards are potentially not needed.
//#ifndef A2OOPGAME_HELPERFUNCTIONS_H
//#define A2OOPGAME_HELPERFUNCTIONS_H



#include <SDL.h>
#include <type_traits>

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

//#endif //A2OOPGAME_HELPERFUNCTIONS_H
