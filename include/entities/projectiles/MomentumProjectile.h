/**
 * @file MomentumProjectile.h
 * @brief A projectile with a constant acceleration force applied.
 * Project: A2OOPGame
 * @author Ryan Purse
 * @version 1.0.0
 * Initial Version: 07/05/2021
 */


#ifndef A2OOPGAME_MOMENTUMPROJECTILE_H
#define A2OOPGAME_MOMENTUMPROJECTILE_H

#include "BaseProjectile.h"

/**
 * A projectile with a constant acceleration force applied.
 * @author Ryan Purse
 * @version 1.0.0 [Initial Version: 07/05/2021]
 */
class MomentumProjectile : public BaseProjectile
{
public:
    MomentumProjectile(const glm::vec2 &position, const glm::vec2 &acceleration, const size_t &collisionLayer);
    ~MomentumProjectile() override = default;

    void update() override;
    void onCollision(const std::shared_ptr<Entity> &other) override;

protected:
    float mMaxVelocity;
    glm::vec2 mAcceleration;
};


#endif //A2OOPGAME_MOMENTUMPROJECTILE_H
