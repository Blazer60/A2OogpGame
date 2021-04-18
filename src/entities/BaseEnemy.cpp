/**
 * @file BaseEnemy.cpp.cc
 * @brief The base entity class for all enemies.
 * Project: A2OOPGame
 * @author Ryan Purse
 * @version 1.0.0
 * Initial Version: 15/04/2021
 */


#include "BaseEnemy.h"

BaseEnemy::BaseEnemy(const glm::vec2 &position, const glm::vec2 &hitBoxSize, const size_t &collisionLayer) :
        Entity(position, hitBoxSize, collisionLayer)
{}

void BaseEnemy::update()
{
    mHitBoxColour = { 0, 0, 255, 255 };
}

void BaseEnemy::onCollision(const std::shared_ptr<Entity> &other)
{
    mHitBoxColour = { 255, 0, 0, 255 };
}
