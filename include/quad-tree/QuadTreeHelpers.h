/**
 * @file QuadTreeHelpers.h
 * @brief Some helper classes and functions that the quad tree needs to operate.
 * Project: A2OOPGame
 * @author Ryan Purse
 * @version 1.0.0
 * Initial Version: 16/04/2021
 */


#ifndef A2OOPGAME_QUADTREEHELPERS_H
#define A2OOPGAME_QUADTREEHELPERS_H

#include <glm.hpp>

namespace quad
{
    struct rect
    {
        float x, y, w, h;

        rect() = default;

        rect(float x, float y, float w, float h) : x(x), y(y), w(w), h(h) {}
        rect(const glm::vec2 &pos, const glm::vec2 &size) : x(pos.x), y(pos.y), w(size.x), h(size.y) {}
    };

    enum regions : int { NorthWest, SouthWest, SouthEast, NorthEast };

    enum layers : size_t
    {
        Player              = 0b00001,
        Enemy               = 0b00010,
        EnemyProjectile     = 0b00100,
        PlayerProjectile    = 0b01000,
        Projectile          = 0b01100,
        Boundary            = 0b10000,
        Any                 = 0b11111
    };

    template<typename dataType>
    struct data
    {
        rect bounds;
        dataType value;
        size_t layer;
    };

    bool isIntersecting(const rect &rec1, const rect &rec2);
}



#endif //A2OOPGAME_QUADTREEHELPERS_H
