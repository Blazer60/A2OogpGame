/**
 * @file BaseProjectile.cpp.cc
 * @brief The base projectile class that all projectiles inherit from.
 * Additionally provides basic functionality for a projectile.
 * Project: A2OOPGame
 * @author Ryan Purse
 * @version 1.0.0
 * Initial Version: 18/04/2021
 */


#include "BaseProjectile.h"
#include "QuadTreeHelpers.h"

BaseProjectile::BaseProjectile(const glm::vec2 &position, const glm::vec2 &velocity, std::string imageRef) :
        Entity(position, { 16, 16 }, { 8, 8 },quad::layers::Projectile, std::move(imageRef))
{
    mVelocity = velocity;  // Assigning here rather than creating a new Entity Constructor.
    mAngularVelocity = 20.0;
}

void BaseProjectile::update()
{
    mTransform.position += mVelocity;
    mTransform.rotation += mAngularVelocity;
}

void BaseProjectile::onCollision(const std::shared_ptr<Entity> &other)
{
    mIsDead = true;
}


