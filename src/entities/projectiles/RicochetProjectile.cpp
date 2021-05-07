/**
 * @file RicochetProjectile.cpp.cc
 * @brief A Projectile that can bounce of the walls
 * a set amount of times before dying.
 * Project: A2OOPGame
 * @author Ryan Purse
 * @version 1.0.0
 * Initial Version: 07/05/2021
 */


#include "RicochetProjectile.h"
#include "QuadTreeHelpers.h"
#include "Player.h"
#include "BarrierCollider.h"

RicochetProjectile::RicochetProjectile(const glm::vec2 &position, const glm::vec2 &velocity,
                                       const size_t &collisionLayer) :
            BaseProjectile(position, velocity, collisionLayer, "../tmp/RicochetProjectile-0001.png"),
            mBounces(3)
{
    mAngularVelocity = 0;
}

void RicochetProjectile::update()
{
    BaseProjectile::update();
}

void RicochetProjectile::onCollision(const std::shared_ptr<Entity> &other)
{
    if (typeid(*other).hash_code() == typeid(Player).hash_code())
    {
        auto player = std::dynamic_pointer_cast<Player>(other);
        if (player->isInvulnerable()) { return; }
        mIsDead = true;
    }
    else if (typeid(*other).hash_code() == typeid(BarrierCollider).hash_code())
    {
        auto barrier = std::dynamic_pointer_cast<BarrierCollider>(other);
        switch (barrier->mDirectionFacing)
        {
            case BarrierCollider::SouthFacing:
            case BarrierCollider::NorthFacing:
                mVelocity.y *= -1;
                break;
            case BarrierCollider::EastFacing:
            case BarrierCollider::WestFacing:
                mVelocity.x *= -1;
                break;
        }
        mBounces -= 1;
        if (mBounces <= 0) { mIsDead = true; }
    }
}
