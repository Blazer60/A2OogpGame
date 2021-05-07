/**
 * @file RicochetProjectile.h
 * @brief A Projectile that can bounce of the walls
 * a set amount of times before dying.
 * Project: A2OOPGame
 * @author Ryan Purse
 * @version 1.0.0
 * Initial Version: 07/05/2021
 */


#ifndef A2OOPGAME_RICOCHETPROJECTILE_H
#define A2OOPGAME_RICOCHETPROJECTILE_H

#include "BaseProjectile.h"

/**
 * A Projectile that can bounce of the walls
 * a set amount of times before dying.
 * @author Ryan Purse
 * @version 1.0.0 [Initial Version: 07/05/2021]
 */
class RicochetProjectile : public BaseProjectile
{
public:
    RicochetProjectile(const glm::vec2 &position, const glm::vec2 &velocity,
                       const size_t &collisionLayer);

    ~RicochetProjectile() override = default;

    void update() override;
    void onCollision(const std::shared_ptr<Entity> &other) override;

protected:
    int mBounces;
};


#endif //A2OOPGAME_RICOCHETPROJECTILE_H
