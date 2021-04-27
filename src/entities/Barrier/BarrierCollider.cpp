/**
 * @file BarrierCollider.cpp.cc
 * @brief The collider element for the barriers that surround the arena.
 * This is separate so the "bouncing" projectiles can reflects in the correct direction.
 * Project: A2OOPGame
 * @author Ryan Purse
 * @version 1.0.0
 * Initial Version: 27/04/2021
 */


#include <iostream>
#include "BarrierCollider.h"
#include "QuadTreeHelpers.h"

BarrierCollider::BarrierCollider(const glm::vec2 &position, char directionFacing) :
        Entity(position, glm::vec2(1.f, 1.f), quad::layers::Boundary),
        mDirectionFacing(directionFacing)
{
    const float thickness = 128;
    if ((mDirectionFacing & (EastFacing | WestFacing)) > 0)
    {
        mHitBoxSize = glm::vec2(thickness, 4096);
    }
    else
    {
        mHitBoxSize = glm::vec2(4096 - 2 * thickness, thickness);
    }
}

void BarrierCollider::update()
{}

void BarrierCollider::onCollision(const std::shared_ptr<Entity> &other)
{}
