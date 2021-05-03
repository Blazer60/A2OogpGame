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
#include "Player.h"

#include "Sfx.h"

BaseProjectile::BaseProjectile(const glm::vec2 &position, const glm::vec2 &velocity, const size_t &collisionLayer,
                               std::string imageRef) :
        Entity(position, { 16, 16 }, { 8, 8 }, collisionLayer, std::move(imageRef)),
        mSpawnSound(std::make_unique<Sfx>("../sfx/shurikenThrow.mp3"))
{
    mVelocity = velocity;  // Assigning here rather than creating a new Entity Constructor.
    mQueryLayers = quad::layers::Boundary | quad::layers::Player;
    mSpawnSound->play();
}

void BaseProjectile::update()
{
    mTransform.position += mVelocity;
}

void BaseProjectile::onCollision(const std::shared_ptr<Entity> &other)
{
    if (typeid(*other).hash_code() == typeid(Player).hash_code())
    {
        auto player = std::dynamic_pointer_cast<Player>(other);
        if (player->isInvulnerable())
        {
            return;  // Ignore the collision.
        }
    }
    mIsDead = true;
}


