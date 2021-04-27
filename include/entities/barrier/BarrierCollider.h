/**
 * @file BarrierCollider.h
 * @brief The collider element for the barriers that surround the arena.
 * This is separate so the "bouncing" projectiles can reflects in the correct direction.
 * Project: A2OOPGame
 * @author Ryan Purse
 * @version 1.0.0
 * Initial Version: 27/04/2021
 */


#ifndef A2OOPGAME_BARRIERCOLLIDER_H
#define A2OOPGAME_BARRIERCOLLIDER_H

#include "Entity.h"

#include <glm.hpp>

/**
 * The collider element for the barriers that surround the arena.
 * This is separate so the "bouncing" projectiles can reflects in the correct direction.
 * @author Ryan Purse
 * @version 1.0.0 [Initial Version: 27/04/2021]
 */
class BarrierCollider : public Entity
{
public:
    enum orientation : char { NorthFacing=0b0001, EastFacing=0b0010, SouthFacing=0b0100, WestFacing=0b1000 };

    BarrierCollider(const glm::vec2 &position, char directionFacing);
    ~BarrierCollider() override = default;

    void update() override;
    void onCollision(const std::shared_ptr<Entity> &other) override;

    const char mDirectionFacing;
};


#endif //A2OOPGAME_BARRIERCOLLIDER_H
