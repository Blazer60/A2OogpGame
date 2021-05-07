/**
 * @file MomentumProjectile.cpp.cc
 * @brief A projectile with a constant acceleration force applied.
 * Project: A2OOPGame
 * @author Ryan Purse
 * @version 1.0.0
 * Initial Version: 07/05/2021
 */


#include "MomentumProjectile.h"

MomentumProjectile::MomentumProjectile(const glm::vec2 &position, const glm::vec2 &acceleration,
                                       const size_t &collisionLayer) : BaseProjectile(
        position, glm::vec2(0.f), collisionLayer, "../tmp/MomentumProjectile-0001.png"),
        mMaxVelocity(25), mAcceleration(acceleration)
{

}

void MomentumProjectile::update()
{
    mVelocity += mAcceleration;
    if (mVelocity.x > mMaxVelocity)         { mVelocity.x = mMaxVelocity; }
    else if (mVelocity.x < -mMaxVelocity)   { mVelocity.x = -mMaxVelocity; }
    if (mVelocity.y > mMaxVelocity)         { mVelocity.y = mMaxVelocity; }
    else if (mVelocity.y < -mMaxVelocity)   { mVelocity.y = -mMaxVelocity; }
    BaseProjectile::update();
}

void MomentumProjectile::onCollision(const std::shared_ptr<Entity> &other)
{
    BaseProjectile::onCollision(other);
}
