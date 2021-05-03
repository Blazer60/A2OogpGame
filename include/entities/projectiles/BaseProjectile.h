/**
 * @file BaseProjectile.h
 * @brief The base projectile class that all projectiles inherit from.
 * Additionally provides basic functionality for a projectile.
 * Project: A2OOPGame
 * @author Ryan Purse
 * @version 1.0.0
 * Initial Version: 18/04/2021
 */


#ifndef A2OOPGAME_BASEPROJECTILE_H
#define A2OOPGAME_BASEPROJECTILE_H

#include "Entity.h"

class SoundFx;

/**
 * The base projectile class that all projectiles inherit from.
 * Additionally provides basic functionality for a projectile.
 * @author Ryan Purse
 * @version 1.0.0 [Initial Version: 18/04/2021]
 */
class BaseProjectile : public Entity
{
public:
    BaseProjectile(const glm::vec2 &position, const glm::vec2 &velocity, const size_t &collisionLayer,
                   std::string imageRef = "../tmp/BaseProjectile-0001.png");

    void update() override;
    void onCollision(const std::shared_ptr<Entity> &other) override;

protected:
    std::unique_ptr<SoundFx> mSpawnSound;
};


#endif //A2OOPGAME_BASEPROJECTILE_H
